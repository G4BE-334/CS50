import re
from cs50 import get_string

s = get_string("Do you Agree?\n")

if re.search("^y(es)?$", s, re.IGNORECASE):
    print("Agreed.")
elif re.search("^n(o)?$", s, re.IGNORECASE):
    print("Not Agreed.")
