from cs50 import get_int

# Get credit card number from the user
n = get_int("Number: ")

# Variables to be used
sumOther2 = 0
sumN = 0
digits = 0

# IT IS NECESSARY TO USE int(n / x) EVERY TIME I WANT TO USE
# THE / OPERATOR BECAUSE IT ALWAYS RETURN A FLOAT

# Print out INVALID for any number bellow the minimum 13 digits card
if n < 4000000000000:
    print("INVALID")

# Check for 13 digits VISA credit cards
elif 4000000000000 <= n < 5000000000000:

    # Here we use n > 4 because the first digit is 4 and it has an odd ammount of digits
    while n > 4:
        sumN = sumN + (n % 10)
        n = int(n / 10)
        digits = (n % 10) * 2
        if digits >= 10:
            digits = (digits % 10) + int((digits / 10))
        n = int(n / 10)
        sumOther2 = sumOther2 + digits

    # Check the total sum to verify the credit card brand
    totalSum = sumOther2 + sumN + 4
    if (totalSum % 10) == 0:
        print("VISA")
    else:
        print("INVALID")

# Check for 15 digits AMEX credit card
elif 340000000000000 <= n < 350000000000000:

    # Here we use n > 3 because the first digit is 3 and it has an odd ammount of digits
    while n > 3:
        sumN = sumN + (n % 10)
        n = int(n / 10)
        digits = (n % 10) * 2
        if digits >= 10:
            digits = (digits % 10) + int((digits / 10))
        n = int(n / 10)
        sumOther2 = sumOther2 + digits
    totalSum = sumOther2 + sumN + 3
    if (totalSum % 10) == 0:
        print("AMEX")
    else:
        print("INVALID")

# Check for 15 digits AMEX credit cards in another range
elif 370000000000000 <= n < 380000000000000:

    # Here we use n > 3 because the first digit is 3 and it has an odd ammount of digits
    while n > 3:
        sumN = sumN + (n % 10)
        n = int(n / 10)
        digits = (n % 10) * 2
        if digits >= 10:
            digits = (digits % 10) + int((digits / 10))
        n = int(n / 10)
        sumOther2 = sumOther2 + digits
    totalSum = sumOther2 + sumN + 3
    if (totalSum % 10) == 0:
        print("AMEX")
    else:
        print("INVALID")

# Check for 16 digits MASTERCARD credit card
elif 5100000000000000 <= n < 5600000000000000:

    # Here we use n > 50 because 51 are the least first two possible digits and n has even ammount of digits
    while n > 50:
        sumN = sumN + (n % 10)
        n = int(n / 10)
        digits = (n % 10) * 2
        if digits >= 10:
            digits = (digits % 10) + int((digits / 10))
        n = int(n / 10)
        sumOther2 = sumOther2 + digits
    totalSum = sumOther2 + sumN
    if (totalSum % 10) == 0:
        print("MASTERCARD")
    else:
        print("INVALID")

# Check for 16 digits VISA credit card
elif 4000000000000000 <= n < 5000000000000000:

    # Here we use n >= 40 because 40 are the last first two possible digits and n has an even ammount of digits
    while n >= 40:
        sumN = sumN + (n % 10)
        n = int(n / 10)
        digits = (n % 10) * 2
        if digits >= 10:
            digits = (digits % 10) + int((digits / 10))
        n = int(n / 10)
        sumOther2 = sumOther2 + digits
    totalSum = sumOther2 + sumN
    if (totalSum % 10) == 0:
        print("VISA")
    else:
        print("INVALID")

else:
    print("INVALID")