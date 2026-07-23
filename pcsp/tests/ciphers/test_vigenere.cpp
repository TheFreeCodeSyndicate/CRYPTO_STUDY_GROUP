#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "pcsp/ciphers/vigenere.hpp"

// Standalone test harness for VigenereCipher (REQ-CIP-501).
// Build in isolation, no networking/protocol code required:
//   make -C tests vigenere
// (API Doc Sec 7 item 2 -- crypto devs verify math without touching sockets.)

namespace {

int g_failures = 0;
int g_expected_failures = 0;

void check(bool condition, const std::string& test_name) {
    if (condition) {
        std::cout << "[PASS] " << test_name << std::endl;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        ++g_failures;
    }
}

// Helper to convert std::string to std::vector<uint8_t> for convenience
std::vector<uint8_t> to_bytes(const std::string& str) {
    return std::vector<uint8_t>(str.begin(), str.end());
}

} // namespace

int main() {
    VigenereCipher cipher;

    // 1. Basic Known Vector & Round Trip (standard ASCII key)
    {
        std::vector<uint8_t> plaintext = to_bytes("ATTACKATDAWN");
        std::vector<uint8_t> key       = to_bytes("LEMON");
        std::vector<uint8_t> expected  = to_bytes("LXFOPVEFRNHR");

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        std::vector<uint8_t> recovered  = cipher.decrypt(ciphertext, key);

        check(ciphertext == expected, "known_vector_encrypt_classic_lemon");
        check(recovered == plaintext, "round_trip_classic_lemon");
    }

    // 2. Case Preservation / Lowercase Support
    {
        std::vector<uint8_t> plaintext = to_bytes("attackatdawn");
        std::vector<uint8_t> key       = to_bytes("lemon");
        std::vector<uint8_t> expected  = to_bytes("lxfopvefrnhr");

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        std::vector<uint8_t> recovered  = cipher.decrypt(ciphertext, key);

        check(ciphertext == expected, "known_vector_lowercase");
        check(recovered == plaintext, "round_trip_lowercase");
    }

    // 3. Non-alphabet Characters & Key-Advancement Freeze Rule
    // Non-alphabet characters (spaces, punctuation, digits) should pass through unencrypted
    // AND must NOT advance the key index.
    {
        // "A T T A C K" -> 'A'(L=0), ' '(ignored), 'T'(E=4), ' '(ignored), 'T'(M=12), ...
        std::vector<uint8_t> plaintext = to_bytes("ATT ACK! 123");
        std::vector<uint8_t> key       = to_bytes("LEMON");
        std::vector<uint8_t> expected  = to_bytes("LXF OPV! 123");

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        std::vector<uint8_t> recovered  = cipher.decrypt(ciphertext, key);

        check(ciphertext == expected, "non_alpha_pass_through_and_key_freeze");
        check(recovered == plaintext, "round_trip_with_non_alpha");
    }

    // 4. Single-Character Key (behaves like standard Caesar shift)
    {
        std::vector<uint8_t> plaintext = to_bytes("HELLO");
        std::vector<uint8_t> key       = to_bytes("D"); // Shift by 3 ('D' - 'A' = 3)
        std::vector<uint8_t> expected  = to_bytes("KHOOR");

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        std::vector<uint8_t> recovered  = cipher.decrypt(ciphertext, key);

        check(ciphertext == expected, "single_char_key_caesar_shift");
        check(recovered == plaintext, "round_trip_single_char_key");
    }

    // 5. Long Plaintext / Repeated Key Wrapping
    {
        std::vector<uint8_t> plaintext = to_bytes("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG");
        std::vector<uint8_t> key       = to_bytes("KEY");

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        std::vector<uint8_t> recovered  = cipher.decrypt(ciphertext, key);

        check(recovered == plaintext, "round_trip_repeated_key_wrapping");
    }

    // 6. Edge Case: Empty Key (should reject and return empty vector)
    {
        std::vector<uint8_t> plaintext = to_bytes("TEST");
        std::vector<uint8_t> key; // empty

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        check(ciphertext.empty(), "encrypt_rejects_empty_key");
    }

    // 7. Edge Case: Invalid Key containing non-alphabetic characters
    {
        std::vector<uint8_t> plaintext = to_bytes("TEST");
        std::vector<uint8_t> key       = to_bytes("KEY123");

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        check(ciphertext.empty(), "encrypt_rejects_non_alpha_key");
    }

    // 8. Edge Case: Empty Plaintext
    {
        std::vector<uint8_t> plaintext;
        std::vector<uint8_t> key = to_bytes("SECRET");

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        std::vector<uint8_t> recovered  = cipher.decrypt(ciphertext, key);

        check(ciphertext.empty(), "empty_plaintext_yields_empty_ciphertext");
        check(recovered.empty(), "empty_round_trip");
    }

    std::cout << std::endl;
    std::cout << g_failures << " unexpected failure(s), "
              << g_expected_failures << " known-bug failure(s)." << std::endl;

    return g_failures == 0 ? 0 : 1;
}