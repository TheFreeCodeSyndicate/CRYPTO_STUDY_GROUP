#ifndef PCSP_CIPHERS_MONO_SUBSTITUTION_HPP
#define PCSP_CIPHERS_MONO_SUBSTITUTION_HPP

// REQ-CIP-404 -- MonoSubstitutionCipher
// Cipher ID: 0x13
// Key field format: 26 bytes -- permutation array
// Owner: Cryptographic Implementations (API Doc Sec 5.6 / Sec 7 item 2)

#include "pcsp/icipher.hpp"

class MonoSubstitutionCipher : public ICipher {
public:
    std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key) const override;

    std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key) const override;
};

#endif // PCSP_CIPHERS_MONO_SUBSTITUTION_HPP
