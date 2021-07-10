from cs50 import get_string

# Get input from the user
text = get_string("Text: ").lower()

# Letters count can be done be verifying all the alpha chars in text
letters = sum(l.isalpha() for l in text)

# Words count can be done be the function split
words = len(text.split())

# We can only count the sentences individually because not all punctuations define a sentence
# Like "," and "'"
sentences = 0
i = 0

for i in range(len(text)):

    # Look for sentences indicator to count the sentences
    if text[i] == "." or text[i] == "?" or text[i] == "!":
        sentences += 1

L = 100 * float(letters / words)
S = 100 * float(sentences / words)
index = round(0.0588 * L - 0.296 * S - 15.8)

# print(f"{letters} {words} {sentences}")

if index < 1:
    print("Before Grade 1")

elif index >= 16:
    print("Grade 16+")

else:
    print(f"Grade {index}")