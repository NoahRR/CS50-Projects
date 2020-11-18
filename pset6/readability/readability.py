text = input("Text: ")
words = 0
letter = 0

# calculate L
for i in range(len(text)):
    if text[i].isalpha() == True:                                          ##text[i].lower() >= "a" or text[i].lower() <= "z":
        letter += 1
    elif text[i] == " ":
        words += 1
L = (letter / (words + 1)) * 100

# calculate S
S = 0
for i in range(len(text)):
    if (text[i] == "." or text[i] == "!" or text[i] == "?") and (text[i - 1] != "." and text[i - 1] != "!" and text[i - 1] != "?"):
        S += 1
S = (S / (words + 1)) * 100

# Calculate the Coleman-Liau index and print rounded grade level
level = round(0.0588 * L - 0.296 * S - 15.8)
if level < 1:
    print("Before Grade 1")
    exit(0)
elif level > 16:
    print("Grade 16+")
    exit(0)
else:
    print(f"Grade {level}")