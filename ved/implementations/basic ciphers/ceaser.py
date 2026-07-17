import string

s = input("Enter your string: ")
right_shift = int(input("Enter right shift amount: "))

# shifted_lower = ''.join([chr(97 + (i + (right_shift % 26)) % 26) for i in range(26)])
# shifted_upper = ''.join([chr(65 + (i + (right_shift % 26)) % 26) for i in range(26)])

shifted_letters = ''.join([chr(
    (65 * v.isupper() + 97 * v.islower()) + (i + (right_shift % 26)) % 26) for i, v in enumerate(string.ascii_letters)
])

ceaser_table = str.maketrans(string.ascii_letters, shifted_letters)
print("Ceaser: ", s.translate(ceaser_table))