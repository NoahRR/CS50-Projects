from cs50 import get_int

# gets size "size" between 1 - 8 inclusive
while True:
    size = get_int("Height: ")
    if size > 0 and size < 9:
        break

# prints out the pyramid
n = size - 1
for i in range(1, size + 1):       #go through each row
    print(" " * n, end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i, end="")
    print(" " * n, end="")
    print()
    n -= 1