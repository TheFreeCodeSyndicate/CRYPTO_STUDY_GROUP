#include "pcsp/ciphers/caesar.hpp"

// TODO(REQ-CIP-401): implement CaesarCipher::encrypt
// Key field format: 1 byte -- shift K
std::vector<uint8_t> CaesarCipher::encrypt(
    const std::vector<uint8_t>& plaintext,
    const std::vector<uint8_t>& key) const
{
    (void)key;
    return plaintext; // placeholder identity transform -- replace with real math
}

// TODO(REQ-CIP-401): implement CaesarCipher::decrypt
std::vector<uint8_t> CaesarCipher::decrypt(
    const std::vector<uint8_t>& ciphertext,
    const std::vector<uint8_t>& key) const
{
    (void)key;
    return ciphertext; // placeholder identity transform -- replace with real math
}
