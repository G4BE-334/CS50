from cs50 import get_int

isValid = False
while isValid == False:
    n = get_int("Height: ")
    if n > 0 and n < 9:
        isValid = True

i = 0
j = 0
k = 0

for i in range(n+1):

    if i > 0:
        for j in range(n-i):
            print(" ", end="")

        for k in range(i):
            print("#", end="")

        print(" ", end="")
        print(" ", end="")

        for k in range(i):
            print("#", end="")

        print("")
