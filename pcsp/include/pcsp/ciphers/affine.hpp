#ifndef PCSP_CIPHERS_AFFINE_HPP
#define PCSP_CIPHERS_AFFINE_HPP

// REQ-CIP-402 -- AffineCipher
// Cipher ID: 0x11
// Key field format: 2 bytes -- pair (a, b)
// Owner: Cryptographic Implementations (API Doc Sec 5.6 / Sec 7 item 2)

#include "pcsp/icipher.hpp"

class AffineCipher : public ICipher {
public:
    std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key) const override;

    std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key) const override;
};

#endif // PCSP_CIPHERS_AFFINE_HPP
