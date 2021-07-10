from sys import exit

names = ["gabe", "mike", "Lucas"]

if "Lucas" in names:
    print("Found!")
    exit(0)
print("Not found")
exit(1)