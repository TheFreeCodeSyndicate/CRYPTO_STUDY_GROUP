#include <iostream>
#include <vector>
#include <cstdint>
#include "pcsp/ciphers/mono_substitution.hpp"

// Standalone test harness for MonoSubstitutionCipher (REQ-CIP-404).
// Build in isolation, no networking/protocol code required:
//   make -C tests mono_substitution
// (API Doc Sec 7 item 2 -- crypto devs verify math without touching sockets.)
int main() {
    MonoSubstitutionCipher cipher;

    std::vector<uint8_t> plaintext = { /* TODO: sample plaintext bytes */ };
    std::vector<uint8_t> key       = { /* TODO: sample key, format: 26 bytes -- permutation array */ };

    std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
    std::vector<uint8_t> recovered  = cipher.decrypt(ciphertext, key);

    std::cout << "TODO: assert recovered == plaintext for MonoSubstitutionCipher" << std::endl;
    return 0; // TODO: return 1 on mismatch once real assertions are added
}
