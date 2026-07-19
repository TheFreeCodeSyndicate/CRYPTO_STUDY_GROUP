#include "pcsp/ciphers/affine.hpp"

// TODO(REQ-CIP-402): implement AffineCipher::encrypt
// Key field format: 2 bytes -- pair (a, b)
std::vector<uint8_t> AffineCipher::encrypt(
    const std::vector<uint8_t>& plaintext,
    const std::vector<uint8_t>& key) const
{
    (void)key;
    return plaintext; // placeholder identity transform -- replace with real math
}

// TODO(REQ-CIP-402): implement AffineCipher::decrypt
std::vector<uint8_t> AffineCipher::decrypt(
    const std::vector<uint8_t>& ciphertext,
    const std::vector<uint8_t>& key) const
{
    (void)key;
    return ciphertext; // placeholder identity transform -- replace with real math
}
