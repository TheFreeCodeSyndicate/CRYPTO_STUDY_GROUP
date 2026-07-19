#include "pcsp/ciphers/hill.hpp"

// TODO(REQ-CIP-602): implement HillCipher::encrypt
// Key field format: n^2 bytes -- row-major matrix, mod 26
std::vector<uint8_t> HillCipher::encrypt(
    const std::vector<uint8_t>& plaintext,
    const std::vector<uint8_t>& key) const
{
    (void)key;
    return plaintext; // placeholder identity transform -- replace with real math
}

// TODO(REQ-CIP-602): implement HillCipher::decrypt
std::vector<uint8_t> HillCipher::decrypt(
    const std::vector<uint8_t>& ciphertext,
    const std::vector<uint8_t>& key) const
{
    (void)key;
    return ciphertext; // placeholder identity transform -- replace with real math
}
