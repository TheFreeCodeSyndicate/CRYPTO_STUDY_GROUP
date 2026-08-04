'''
Write a function that takes two equal-length buffers and produces their XOR combination.

If your function works properly, then when you feed it the string:
1c0111001f010100061a024b53535009181c

... after hex decoding, and when XOR'd against:
686974207468652062756c6c277320657965

... should produce:
746865206b696420646f6e277420706c6179
'''

s1 = "1c0111001f010100061a024b53535009181c"
s2 = "686974207468652062756c6c277320657965"

result = "746865206b696420646f6e277420706c6179"

to_bytes = lambda s: bytes([int(s[i:i+2], 16) for i in range(0, len(s), 2)])

s1_bytes = to_bytes(s1)
s2_bytes = to_bytes(s2)

s1_xor_s2 = "".join(
    hex(byte)[2:] for byte in [*map(lambda a, b: a ^ b, s1_bytes, s2_bytes)]
)

print(f"xor_out: {s1_xor_s2}\nexpected: {result}\nmatched: {s1_xor_s2 == result}")

# TODO: idiomatic python