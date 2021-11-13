import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "POST":
        db.execute("UPDATE users SET cash = cash + :amount WHERE id=:user_id", amount = request.form.get("cash"), user_id = session["user_id"])
        flash("Cash Added!")
        return redirect("/")
    else:
        return render_template("add_cash.html")

def provided(f):
    if request.form.get("f") is None:
        return apology(f"must provide {f}", 403)
        
def usr_prv():
    if not request.form.get("username"):
        return apology("Must provide username", 403)
        
def pss_prv():
    if not request.form.get("password"):
        return apology("Must provide password", 403)

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    r = db.execute("SELECT symbol, SUM(shares) as total FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING total > 0", user_id = session["user_id"])
    gttl = 0
    stands = []
    for row in r:
        stock = lookup(row["symbol"])
        stands.append({
            "symbol": stock["symbol"],
            "name": stock["name"],
            "shares": row["total"],
            "price": usd(stock["price"]),
            "ttl": usd(stock["price"] * row["total"])
        })
        gttl += stock["price"] * row["total"]
    rr = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id = session["user_id"])
    cash = rr[0]["cash"]
    gttl += cash
    return render_template("index.html", stands=stands, cash=usd(cash), gttl=usd(gttl))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Must provide symbol", 403)
        elif not request.form.get("shares").isdigit():
            return apology("Invalid number of share", 400)
            
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid company name")
        n = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        cash = n[0]["cash"]
        updated = cash - shares * stock['price']
        if updated < 0:
            return apology("Not enough fund", 403)
        db.execute("UPDATE users SET cash=:updated WHERE id=:id", updated = updated, id = session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id = session["user_id"], symbol = stock["symbol"], shares = shares, price = stock["price"])
        flash("Purchase Complete!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    trans = db.execute("SELECT symbol, shares, price, transacted FROM transactions WHERE user_id=:user_id", user_id = session["user_id"])
    for i in range (len(trans)):
        trans[i]["price"] = usd(trans[i]["price"])
    return render_template("history.html", trans = trans)
    
@app.route("/login", methods=["GET", "POST"])
def login():

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        check = usr_prv() or pss_prv()
        if check != None:
            return check

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing Symbol", 400)
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid quote", 400)
        return render_template("quoted.html", sn={'name': stock['name'], 'symbol': stock['symbol'], 'price': usd(stock['price'])})
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Must provide username", 400)
        if not request.form.get("password"):
            return apology("Must provide password", 400)
        
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Please re-check the password", 400)

        prime = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username = request.form.get("username"), hash = generate_password_hash(request.form.get("password")))
        if prime is None:
            return apology("Error while registering", 400)
        session["user_id"] = prime
        flash("Registered!")
        return redirect("/")
        
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Must provide symbol", 400)
        elif not request.form.get("shares").isdigit():
            return apology("Invalid number of share", 400)
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid company name")
            
        rows = db.execute("SELECT symbol, SUM(shares) as total FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING total > 0", user_id = session["user_id"])
        for row in rows:
            if row["symbol"] == symbol:
                if shares > row["total"]:
                    return apology("Not enough shares", 400)
                    
        n = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        cash = n[0]["cash"]
        updated = cash + shares * stock['price']
        if updated < 0:
            return apology("Not enough fund", 400)
        db.execute("UPDATE users SET cash=:updated WHERE id=:id", updated = updated, id = session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id = session["user_id"], symbol = stock["symbol"], shares = -1 * shares, price = stock["price"])
        flash("Sold!")
        return redirect("/")
    else:
        rows = db.execute("SELECT symbol FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id = session["user_id"])
        return render_template("sell.html", symbols = [row["symbol"] for row in rows])


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
