#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long cc;

    do
    {
        cc = get_long("Number: " );
    }
    while (cc <= 0);

    long wCC = cc;
    int sum = 0;
    int count = 0;
    long divisor = 10;

    // 1st case
    while (wCC > 0)
    {
        int lastDigit = wCC % 10;
        sum = sum + lastDigit;
        wCC = wCC / 100;
    }

    // 2nd case
    wCC = cc / 10;
    while (wCC > 0)
    {
        int lastDigit = wCC % 10;
        int timesTwo = lastDigit * 2;
        sum = sum + (timesTwo % 10) + (timesTwo / 10);
        wCC = wCC / 100;
    }

    // length of the number / digit count
    wCC = cc;
    while (wCC != 0)
    {
        wCC = wCC / 10;
        count++;
    }

    // divisor
    for (int i = 0; i < count - 2; i++)
    {
        divisor = divisor * 10;
    }

    int firstDigit = cc / divisor;
    int firstTwoDigits = cc / (divisor / 10);

    // final checks
    if (sum % 10 == 0)
    {
        if (firstDigit == 4 && (count == 13 || count == 16))
        {
            printf("VISA\n");
        }
        else if ((firstTwoDigits == 34 || firstTwoDigits == 37) && count == 15)
        {
            printf("AMEX\n");
        }
        else if ((50 < firstTwoDigits && firstTwoDigits < 56) && count == 16)
        {
            printf("MASTERCARD\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}