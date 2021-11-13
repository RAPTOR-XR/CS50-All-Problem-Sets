from cs50 import get_int


def main():
    while True:
        cc = get_int("Number: ")
        if cc >= 0:
            break
    if valid(cc):
        prcc(cc)
    else:
        print("INVALID")


def valid(ccnm):
    return chksum(ccnm)

    
def chksum(ccnm):
    sm = 0
    for i in range(len(str(ccnm))):
        if i % 2 == 0:
            sm += ccnm % 10
        else:
            dig = 2 * (ccnm % 10)
            sm += dig // 10 + dig % 10
        ccnm //= 10
    return sm % 10 == 0

    
def prcc(ccnm):
    if (ccnm >= 4e12 and ccnm < 5e12) or (ccnm >= 4e15 and ccnm < 5e15):
        print("VISA")
    if (ccnm >= 34e13 and ccnm < 35e13) or (ccnm >= 37e13 and ccnm < 38e13):
        print("AMEX")
    if (ccnm >= 51e14 and ccnm < 56e14):
        print("MASTERCARD")
    else:
        print("INVALID")

        
if __name__ == "__main__":
    main()
