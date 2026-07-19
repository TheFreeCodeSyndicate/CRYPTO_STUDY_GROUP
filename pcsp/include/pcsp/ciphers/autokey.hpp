#ifndef PCSP_CIPHERS_AUTOKEY_HPP
#define PCSP_CIPHERS_AUTOKEY_HPP

// REQ-CIP-503 -- AutokeyCipher
// Cipher ID: 0x22
// Key field format: Variable -- ASCII priming key
// Owner: Cryptographic Implementations (API Doc Sec 5.6 / Sec 7 item 2)

#include "pcsp/icipher.hpp"

class AutokeyCipher : public ICipher {
public:
    std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key) const override;

    std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key) const override;
};

#endif // PCSP_CIPHERS_AUTOKEY_HPP
