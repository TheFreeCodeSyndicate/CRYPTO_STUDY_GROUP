# Atbash

import string

reversed_alphabets = string.ascii_lowercase[::-1] + string.ascii_uppercase[::-1]
translation_table = str.maketrans(string.ascii_letters, reversed_alphabets)

s = input("Enter your string: ")

ciphered_s = s.translate(translation_table)

print("Atbash: ", ciphered_s)
