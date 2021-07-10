#include <stdio.h>
#include <cs50.h>

// Call the function before main because C is old
void checkCard(long n);

int main(void)
{
    long n;
    // Make sure to just use integer input values
    do
    {
        n = get_long("Number: ");
    }
    while (n < 0);
    checkCard(n);
}

void checkCard(long n)
{
    // Print out INVALID for any number bellow 13 digits
    if (n < 4000000000000)
    {
        printf("INVALID\n");
    }
    // Check for 13 digits VISA credit cards
    else if (n >= 4000000000000 && n < 5000000000000)
    {
        // Define variables to be used
        int sumOther2 = 0;
        int sum = 0;
        int digits = 0;
        // n>4 because first digit is 4 and it has an odd ammount of digits
        while (n > 4)
        {
            sum = sum + (n % 10);
            n = n / 10;
            digits = (n % 10) * 2;
            if (digits >= 10)
            {
                digits = (digits % 10) + (digits / 10); 
            }
            n = n / 10;
            sumOther2 = sumOther2 + digits;
        }
        int totalSum = sumOther2 + sum + 4;
        if (totalSum % 10 == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (n >= 340000000000000 && n < 350000000000000)
    {
        // Check for 15 digits AMEX credit card
        int sumOther2 = 0;
        int sum = 0;
        int digits = 0;
        // n>3 because first digit is 3 and it has an odd ammount of digits
        while (n > 3)
        {
            sum = sum + (n % 10);
            n = n / 10;
            digits = (n % 10) * 2;
            if (digits >= 10)
            {
                digits = (digits % 10) + (digits / 10); 
            }
            n = n / 10;
            sumOther2 = sumOther2 + digits;
        }
        int totalSum = sumOther2 + sum + 3;
        if (totalSum % 10 == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (n >= 370000000000000 && n < 380000000000000)
    {
        // Check for 15 digits AMEX credit cards again
        int sumOther2 = 0;
        int sum = 0;
        int digits = 0;
        // n>3 because 3 is the first digit and n has an odd ammount of digits
        while (n > 3)
        {
            sum = sum + (n % 10);
            n = n / 10;
            digits = (n % 10) * 2;
            if (digits >= 10)
            {
                digits = (digits % 10) + (digits / 10); 
            }
            n = n / 10;
            sumOther2 = sumOther2 + digits;
        }
        int totalSum = sumOther2 + sum + 3;
        if (totalSum % 10 == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (n >= 5100000000000000 && n < 5600000000000000)
    {
        // Check for 16 digits MASTERCARD credit card
        int sumOther2 = 0;
        int sum = 0;
        int digits = 0;
        // n>50 because 51 are the minimum first two digits and n has an even ammount of digits
        while (n > 50)
        {
            sum = sum + (n % 10);
            n = n / 10;
            digits = (n % 10) * 2;
            if (digits >= 10)
            {
                digits = (digits % 10) + (digits / 10); 
            }
            n = n / 10;
            sumOther2 = sumOther2 + digits;
        }
        int totalSum = sumOther2 + sum;
        if (totalSum % 10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (n >= 4000000000000000 && n < 5000000000000000)
    {
        // Check for 16 digits VISA credit card
        int sumOther2 = 0;
        int sum = 0;
        int digits = 0;
        // n>=40 because 40 are the minimum first two digits and n has an even ammount of digits
        while (n >= 40)
        {
            sum = sum + (n % 10);
            n = n / 10;
            digits = (n % 10) * 2;
            if (digits >= 10)
            {
                digits = (digits % 10) + (digits / 10); 
            }
            n = n / 10;
            sumOther2 = sumOther2 + digits;
        }
        int totalSum = sumOther2 + sum;
        if (totalSum % 10 == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else 
    {
        // Print out invalid for any number that does not fit any
        // brand credit card gap
        printf("INVALID\n");
    }
}