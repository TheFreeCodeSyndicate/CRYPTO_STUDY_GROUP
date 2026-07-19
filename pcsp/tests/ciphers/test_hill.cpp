#include <iostream>
#include <vector>
#include <cstdint>
#include "pcsp/ciphers/hill.hpp"

// Standalone test harness for HillCipher (REQ-CIP-602).
// Build in isolation, no networking/protocol code required:
//   make -C tests hill
// (API Doc Sec 7 item 2 -- crypto devs verify math without touching sockets.)
int main() {
    HillCipher cipher;

    std::vector<uint8_t> plaintext = { /* TODO: sample plaintext bytes */ };
    std::vector<uint8_t> key       = { /* TODO: sample key, format: n^2 bytes -- row-major matrix, mod 26 */ };

    std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
    std::vector<uint8_t> recovered  = cipher.decrypt(ciphertext, key);

    std::cout << "TODO: assert recovered == plaintext for HillCipher" << std::endl;
    return 0; // TODO: return 1 on mismatch once real assertions are added
}
