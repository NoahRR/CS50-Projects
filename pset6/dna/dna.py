import sys

# check for correct command line argument
if len(sys.argv) != 3:
    print("Usage: dna [CSV file] [TXT file]")

# open and read databse and DNA file
with open(sys.argv[1], 'r') as f:
    CSV_file = f.read()
with open(sys.argv[2], 'r') as f:
    TXT_file = f.read()

# gets number of STR variations and store the variations
STR_count = 0
STR_var = []
word = ""
with open(sys.argv[1], 'r') as f:
    while True:
        tmp = f.read(1)
        if tmp != ',' and tmp != '\n':
            word += tmp
        if tmp == ',':
            STR_count += 1
            STR_var.append(f"{word}")
            word = ''
        if tmp == '\n':
            STR_var.append(f"{word}")
            break

# finds how many times each STR comes up in the TXT DNA file
# defining variables
STR_var_values = [0] * STR_count
i = 1
STR_test = ""

# go through each STR type
for strr in range(STR_count + 1):  # 1 2 3 ...
    # go through each char in text file
    for ch in range(len(TXT_file) - (len(STR_var[strr]) - 1)):  # 0 - chars in TXT_file

        # go through length of STR type and get STR_test
        STR_test = ''
        for strleng in range(len(STR_var[strr])):  # 0 - 4 ...
            STR_test += TXT_file[ch + strleng]

        # if start of possible consecutive sequence of STR
        if STR_test == STR_var[strr]:

            # defining variables
            k = len(STR_var[strr])
            tmp_STR_var_value = 0

            # while consecutive sequence of STR is still going
            while True:
                # keeps track of how many STR's in sequence
                tmp_STR_var_value += 1

                # testing for next set of STR
                STR_forw_test = ''
                for p in range(len(STR_var[strr])):
                    if ch + k + p < len(TXT_file):  # note: when I submitted.. didn't have +p here.. so ig submit50 doesn't check that.
                        STR_forw_test += TXT_file[ch + k + p]

                # if next set of str is same, then continue loop
                if STR_test != STR_forw_test:
                    if tmp_STR_var_value > STR_var_values[strr - 1]:
                        STR_var_values[strr - 1] = tmp_STR_var_value
                    break

                # variable that keeps augmenting the STR_next for testing
                k += len(STR_var[strr])

#determining if STR variation samples matches anyone in database
values_for_database = ""
i = 0

# puts STR_var_values (data to check database) into string format
for i in range(STR_count):
    values_for_database += ','
    values_for_database += str(STR_var_values[i])

# checking database and finding match
match_name = ""
ch = CSV_file.find(values_for_database)
if ch == -1:
    print("No match")
else:
    while True:
        ch -= 1
        if CSV_file[ch] == '\n':
            while CSV_file[ch + 1] != ',':
                ch += 1
                match_name += CSV_file[ch]
            break
    print(match_name)