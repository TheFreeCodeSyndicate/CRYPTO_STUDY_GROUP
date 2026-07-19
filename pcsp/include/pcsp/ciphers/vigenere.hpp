#ifndef PCSP_CIPHERS_VIGENERE_HPP
#define PCSP_CIPHERS_VIGENERE_HPP

// REQ-CIP-501 -- VigenereCipher
// Cipher ID: 0x20
// Key field format: Variable -- ASCII string
// Owner: Cryptographic Implementations (API Doc Sec 5.6 / Sec 7 item 2)

#include "pcsp/icipher.hpp"

class VigenereCipher : public ICipher {
public:
    std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key) const override;

    std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key) const override;
};

#endif // PCSP_CIPHERS_VIGENERE_HPP
