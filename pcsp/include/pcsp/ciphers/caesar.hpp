#ifndef PCSP_CIPHERS_CAESAR_HPP
#define PCSP_CIPHERS_CAESAR_HPP

// REQ-CIP-401 -- CaesarCipher
// Cipher ID: 0x10
// Key field format: 1 byte -- shift K
// Owner: Cryptographic Implementations (API Doc Sec 5.6 / Sec 7 item 2)

#include "pcsp/icipher.hpp"

class CaesarCipher : public ICipher {
public:
    std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key) const override;

    std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key) const override;
};

#endif // PCSP_CIPHERS_CAESAR_HPP
