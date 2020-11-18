from cs50 import get_string
import re
from sys import exit

number = get_string("Number: ")

#Luhn's algorithm - if valid, i = 1
i = 1
sum = 0
while i < (len(number) + 1):
    if i < len(number):
        tmp = (2 * int(number[len(number) - i - 1]))
        for j in range(len(str(tmp))):
            sum += int(str(tmp)[j])
    sum += (int(number[len(number) - i]))
    i += 2
if sum % 10 != 0:
    print("INVALID")
    exit(0)

#check which bank, given that the checksum is valid
if len(number) == 15 and (re.search("^34?", number) or re.search("^37?", number)):
    print("AMEX")
elif len(number) == 16 and (re.search("^51?", number) or re.search("^52?", number) or re.search("^53?", number) or re.search("^54?", number) or re.search("^55?", number)):
    print("MASTERCARD")
elif (len(number) == 13 or len(number) == 16) and re.search("^4?", number):
    print("VISA")