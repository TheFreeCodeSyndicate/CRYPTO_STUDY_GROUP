def encrypt(s, a, b, m) -> str:
    enc = ""
    for letter in s:
        if s.isalpha():
            add_factor = 65 * letter.isupper() + 97 * letter.islower()
            enc += chr(add_factor + (a * (ord(letter) - add_factor) + b) % m)
        else:
            enc += letter
    return enc

def decrypt(s, a, b, m) -> str:
    def multiplicative_inverse(a, m) -> int:
        k = 1
        while (m * k + 1) % a != 0: k += 1
        return (m * k + 1) // a
    
    dec = ""
    a_inverse = multiplicative_inverse(a, m)
    print(a_inverse)
    for letter in s:
        if s.isalpha():
            add_factor = 65 * letter.isupper() + 97 * letter.islower()
            dec += chr(add_factor + ((a_inverse * ((ord(letter) - add_factor) - b)) % m))
        else:
            dec += letter
    return dec

import math
coprime = lambda a, b: math.gcd(a, b) == 1

print("NOTE: a and m must be coprimes.")
a, b, m = [int(x) for x in input("Enter a, b and m (space separated): ").split()]

if not coprime(a, m):
    print("a and m must be coprimes!!")
    exit()

s = input("Enter string: ")
opt = input("(E|e)ncrypt or (D|d)ecrypt: ")

match opt:
    case 'E' | 'e':
        print("Encrypted: ", encrypt(s, a, b, m))
    case 'D' | 'd':
        print("Decrypted: ", decrypt(s, a, b, m))
    case _:
        print("Not implemented desu!")
