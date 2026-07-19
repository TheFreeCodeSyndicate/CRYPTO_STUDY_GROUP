#ifndef PCSP_CIPHERS_ATBASH_HPP
#define PCSP_CIPHERS_ATBASH_HPP

// REQ-CIP-403 -- AtbashCipher
// Cipher ID: 0x12
// Key field format: 0 bytes -- keyless
// Owner: Cryptographic Implementations (API Doc Sec 5.6 / Sec 7 item 2)

#include "pcsp/icipher.hpp"

class AtbashCipher : public ICipher {
public:
    std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key) const override;

    std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key) const override;
};

#endif // PCSP_CIPHERS_ATBASH_HPP
