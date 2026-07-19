#ifndef PCSP_CIPHERS_HILL_HPP
#define PCSP_CIPHERS_HILL_HPP

// REQ-CIP-602 -- HillCipher
// Cipher ID: 0x31
// Key field format: n^2 bytes -- row-major matrix, mod 26
// Owner: Cryptographic Implementations (API Doc Sec 5.6 / Sec 7 item 2)

#include "pcsp/icipher.hpp"

class HillCipher : public ICipher {
public:
    std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key) const override;

    std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key) const override;
};

#endif // PCSP_CIPHERS_HILL_HPP
