import sys
import cs50

# basic check for correct command line arguments
if len(sys.argv) != 2:
    sys.exit("Usage: python import.py [house name]")

# access the database
db = cs50.SQL("sqlite:///students.db")

# get table
table = db.execute(f"SELECT first, middle, last, birth FROM students WHERE house LIKE '%{sys.argv[1]}%' ORDER BY last, first")

# printing table
for i in range(len(table)):
    mid = table[i]['middle']
    if mid == None:
        print(f"{table[i]['first']} {table[i]['last']}, born {table[i]['birth']}")
    else:
        print(f"{table[i]['first']} {mid} {table[i]['last']}, born {table[i]['birth']}")