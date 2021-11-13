from cs50 import get_string

t = get_string("text: ")

l = s = w = 0

for char in t:
    if char.isalpha():
        l += 1
    if char.isspace():
        w += 1
    if char in ["?", ".", "!"]:
        s += 1
        
w += 1
L = round(((l * 100.0) // w), 2)
S = round(((s * 100.0) // w), 2)
result = round(0.0588 * L - 0.296 * S - 15.8)
if result < 1:
    print("Before Grade 1")
elif result >= 16:
    print("Grade 16+")
else:
    print(f"Grade {result}")