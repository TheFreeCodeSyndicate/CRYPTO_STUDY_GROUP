#ifndef PCSP_CIPHERS_RAIL_FENCE_HPP
#define PCSP_CIPHERS_RAIL_FENCE_HPP

// REQ-CIP-701 -- RailFenceCipher
// Cipher ID: 0x40
// Key field format: 1 byte -- rail count
// Owner: Cryptographic Implementations (API Doc Sec 5.6 / Sec 7 item 2)

#include "pcsp/icipher.hpp"

class RailFenceCipher : public ICipher {
public:
    std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key) const override;

    std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key) const override;
};

#endif // PCSP_CIPHERS_RAIL_FENCE_HPP
