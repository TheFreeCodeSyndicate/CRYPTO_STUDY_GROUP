#include "pcsp/ciphers/mono_substitution.hpp"

// TODO(REQ-CIP-404): implement MonoSubstitutionCipher::encrypt
// Key field format: 26 bytes -- permutation array
std::vector<uint8_t> MonoSubstitutionCipher::encrypt(
    const std::vector<uint8_t>& plaintext,
    const std::vector<uint8_t>& key) const
{
    (void)key;
    return plaintext; // placeholder identity transform -- replace with real math
}

// TODO(REQ-CIP-404): implement MonoSubstitutionCipher::decrypt
std::vector<uint8_t> MonoSubstitutionCipher::decrypt(
    const std::vector<uint8_t>& ciphertext,
    const std::vector<uint8_t>& key) const
{
    (void)key;
    return ciphertext; // placeholder identity transform -- replace with real math
}
