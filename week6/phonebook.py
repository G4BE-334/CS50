from sys import exit
import csv

people = {
    "GABE": 12345678,
    "LUCAS": 23456789,
    "MIKE": 34567890,
    "EMMET": 87654321
}

if "GABE" in people:
    print(f"Found {people['GABE']}")
else:
    print("Not found")

name = input("name: ")
number = input("number: ")

with open("phonebook.csv", "a") as file:

    writer = csv.writer(file)
    writer.writerow((name, number))


