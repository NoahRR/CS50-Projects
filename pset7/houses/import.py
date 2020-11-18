import sys
import cs50
import csv

# checking for correct number of command line arguments
if len(sys.argv) != 2:
    sys.exit("Usage: python import.py [CSV roster]")

# getting access to an SQL database (from cs50)
db = cs50.SQL("sqlite:///students.db")

# taking file row by row and importing to database
with open(sys.argv[1]) as f:
    reader = csv.DictReader(f)

    for row in reader:

        # getting name=fml house and birth
        fml = row["name"].split()
        house = row["house"]
        birth = row["birth"]

        # insert data into database
        if len(fml) == 3:
            db.execute(
                f"INSERT INTO students (first, middle, last, house, birth) VALUES ('{fml[0]}', '{fml[1]}', '{fml[2]}', '{house}', '{birth}')")
        elif len(fml) == 2:
            db.execute(
                f"INSERT INTO students (first, last, house, birth) VALUES ('{fml[0]}', '{fml[len(fml) - 1]}', '{house}', '{birth}')")