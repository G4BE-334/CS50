import sys
from sys import argv, exit
import csv

if len(sys.argv) != 3:
    print("Usage: python dna.py sequence.txt")
    exit(1)

# Define variables
STRs = [  ]  # Save the STRs in memory
People = [  ] # Save each individual data in memory
Sequence = [  ] # Save the DNA Sequence in Memory
timesSTR = [  ] # Record how many times each STR shows up in the sequence

# Variable created to facilitate organization
count = 0
###
a
###
# Open database file
with open(argv[1], "r") as file:
    # Read file
    writer = csv.reader(file)

    for row in writer:
        # First row has the STRs present
        if count == 0:
            # Add each STR to the list STRs
            for i in range(len(row)):
                if i !=  0:
                    STRs.append(row[i])
            #print(STRs)
            count += 1
        # Add each individuals data to the People list
        else:
            People.append(row)
    #print(People)

# Open the sequence file
with open(argv[2], "r") as file:

    Sequence = file.read()
    # print(Sequence)

# Verify for each STR how many times it shows up in the sequence
for i in range(len(STRs)):
    # Repetition counter
    counter = 0
    maxCounter = 0
    a = 0

    # How big is the STR: AGATC = 5
    j = len(STRs[i])
    # Have to subctract j to not get out of border index error
    k = len(Sequence) - j

    while a < k:
        # Check for each substring the size of the STR
        if Sequence[a: a+j] == STRs[i]:
            counter += 1
            a = a+j

            if counter > maxCounter:
                maxCounter = counter
        else:
            counter = 0
            a += 1
    # Add to the list the number of times that each STR is present in the sequence
    timesSTR.append(maxCounter)
    #print(timesSTR)

# Look for a match in each individual
for i in range(len(People)):
    isMatch = False
    counter = 1

    for j in range(len(timesSTR)):

        if int(People[i][counter]) == int(timesSTR[j]):
            counter += 1

    if counter == (len(STRs) + 1):
        print(f"{People[i][0]}")
        isMatch = True
        exit(0)

print("No match")


