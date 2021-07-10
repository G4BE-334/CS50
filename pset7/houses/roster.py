from cs50 import SQL
from sys import argv, exit
import csv

# Checking command-line arguments
if len(argv) != 2:
    print("Usage: python roster.py house")
    exit(1)

elif argv[1] != "Slytherin" and argv[1] != "Ravenclaw" and argv[1] != "Hufflepuff" and argv[1] != "Gryffindor":
    print("Please specify a correct Hogwarts house")
    exit(1)

house = argv[1]

db = SQL("sqlite:///students.db")

roster = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)
# print(roster)
for row in roster:
    if row["middle"] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
