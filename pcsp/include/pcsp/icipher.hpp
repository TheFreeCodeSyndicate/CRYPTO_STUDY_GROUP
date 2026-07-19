#ifndef PCSP_ICIPHER_HPP
#define PCSP_ICIPHER_HPP

#include <cstdint>
#include <vector>
#include <memory>

// =============================================================================
// The Cryptographic Subsystem API (REQ-CIP, API Doc Sec 5). Owner: Crypto
// Implementations. All cipher classes inherit this single interface so the
// network/parsing layer can factory-generate + invoke them polymorphically
// without knowing any cipher's internals (Encrypt(P,K) -> C / Decrypt(C,K) -> P).
// =============================================================================
class ICipher {
public:
    virtual ~ICipher() = default;

    virtual std::vector<uint8_t> encrypt(
        const std::vector<uint8_t>& plaintext,
        const std::vector<uint8_t>& key) const = 0;

    virtual std::vector<uint8_t> decrypt(
        const std::vector<uint8_t>& ciphertext,
        const std::vector<uint8_t>& key) const = 0;
};

// Cipher ID Registry dispatch (API Doc Sec 5.2/5.3, Table 1). Returns nullptr
// to signal the unsupported-cipher condition required by REQ-NFR-802.
// Implemented in src/ciphers/cipher_factory.cpp. Owner: State Parsing.
std::unique_ptr<ICipher> create_cipher(uint8_t cipher_id);

#endif // PCSP_ICIPHER_HPP
