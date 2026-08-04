'''
Convert hex to base64

The string:
49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d

Should produce:
SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

So go ahead and make that happen. You'll need to use this code for the rest of the exercises. 
'''

# it's hex
import base64 as b64

es = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
es_bytes = bytes([int(es[i:i+2], 16) for i in range(0, len(es), 2)])
es_b64 = b64.b64encode(es_bytes)

print(f"Produced: {es_b64.decode('utf-8')}")
