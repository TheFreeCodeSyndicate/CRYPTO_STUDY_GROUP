#ifndef PCSP_CIPHERS_COLUMNAR_TRANSPOSITION_HPP
#define PCSP_CIPHERS_COLUMNAR_TRANSPOSITION_HPP

// REQ-CIP-702 -- ColumnarTranspositionCipher
// Cipher ID: 0x41
// Key field format: Variable -- keyword string
// Owner: Cryptographic Implementations (API Doc Sec 5.6 / Sec 7 item 2)

#include "pcsp/icipher.hpp"

class ColumnarTranspositionCipher : public ICipher {
public:
    std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key) const override;

    std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key) const override;
};

#endif // PCSP_CIPHERS_COLUMNAR_TRANSPOSITION_HPP
