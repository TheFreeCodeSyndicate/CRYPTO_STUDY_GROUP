#include "pcsp/ciphers/atbash.hpp"

// TODO(REQ-CIP-403): implement AtbashCipher::encrypt
// Key field format: 0 bytes -- keyless
std::vector<uint8_t> AtbashCipher::encrypt(
    const std::vector<uint8_t>& plaintext,
    const std::vector<uint8_t>& key) const
{
    (void)key;
    return plaintext; // placeholder identity transform -- replace with real math
}

// TODO(REQ-CIP-403): implement AtbashCipher::decrypt
std::vector<uint8_t> AtbashCipher::decrypt(
    const std::vector<uint8_t>& ciphertext,
    const std::vector<uint8_t>& key) const
{
    (void)key;
    return ciphertext; // placeholder identity transform -- replace with real math
}
