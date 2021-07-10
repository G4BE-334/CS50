from cs50 import SQL
import sys
import csv

# Checking command-line arguments
if len(sys.argv) != 2:
    print("Usage: python import.py file.csv")
    exit(1)

db = SQL("sqlite:///students.db")

# Open database file
with open(sys.argv[1], "r") as file:
    # Read file
    writer = csv.reader(file)

    for row in writer:
        # Split the names to make easier to identify who has middle name and who does not
        fullName = row[0].split()
        if len(fullName) == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                    fullName[0], None, fullName[1], row[1], row[2])
        elif len(fullName) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                    fullName[0], fullName[1], fullName[2], row[1], row[2])

house = db.execute("SELECT * from students")
print(house)
#db.execute("TRUNCATE TABLE students")