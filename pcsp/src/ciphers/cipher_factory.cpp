#include "pcsp/icipher.hpp"
#include "pcsp/ciphers/caesar.hpp"
#include "pcsp/ciphers/affine.hpp"
#include "pcsp/ciphers/atbash.hpp"
#include "pcsp/ciphers/mono_substitution.hpp"
#include "pcsp/ciphers/vigenere.hpp"
#include "pcsp/ciphers/beaufort.hpp"
#include "pcsp/ciphers/autokey.hpp"
#include "pcsp/ciphers/playfair.hpp"
#include "pcsp/ciphers/hill.hpp"
#include "pcsp/ciphers/rail_fence.hpp"
#include "pcsp/ciphers/columnar_transposition.hpp"

// Cipher ID Registry (API Doc Sec 5.2/5.3, Table 1). Owner: State Parsing.
// This is the ONLY function the network/parsing developer calls into the
// crypto subsystem through -- it either returns a live ICipher, or nullptr
// to signal the unsupported-cipher condition required by REQ-NFR-802.
std::unique_ptr<ICipher> create_cipher(uint8_t cipher_id) {
    switch (cipher_id) {
        case 0x10: return std::make_unique<CaesarCipher>();
        case 0x11: return std::make_unique<AffineCipher>();
        case 0x12: return std::make_unique<AtbashCipher>();
        case 0x13: return std::make_unique<MonoSubstitutionCipher>();
        case 0x20: return std::make_unique<VigenereCipher>();
        case 0x21: return std::make_unique<BeaufortCipher>();
        case 0x22: return std::make_unique<AutokeyCipher>();
        case 0x30: return std::make_unique<PlayfairCipher>();
        case 0x31: return std::make_unique<HillCipher>();
        case 0x40: return std::make_unique<RailFenceCipher>();
        case 0x41: return std::make_unique<ColumnarTranspositionCipher>();
        default:   return nullptr; // REQ-NFR-802: unsupported Cipher ID
    }
}
