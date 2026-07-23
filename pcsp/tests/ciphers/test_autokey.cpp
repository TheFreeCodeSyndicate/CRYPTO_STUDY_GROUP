#include "pcsp/ciphers/autokey.hpp"

#include <iostream>
#include <string>
#include <vector>

// Lightweight, dependency-free test harness. If your project already uses
// GoogleTest / Catch2 / doctest, swap the check() calls for that framework's
// assertions -- the test bodies below don't need to change.
namespace {

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const std::string& description) {
    ++g_checks;
    if (!condition) {
        ++g_failures;
        std::cout << "  [FAIL] " << description << "\n";
    } else {
        std::cout << "  [ OK ] " << description << "\n";
    }
}

// Helpers to work in plain A-Z text instead of raw 0-25 codes.
std::vector<uint8_t> to_codes(const std::string& letters) {
    std::vector<uint8_t> out;
    for (char c : letters) out.push_back(static_cast<uint8_t>(c - 'A'));
    return out;
}

std::string to_letters(const std::vector<uint8_t>& codes) {
    std::string out;
    for (uint8_t c : codes) out.push_back(static_cast<char>('A' + (c % 26)));
    return out;
}

}  // namespace

void test_empty_inputs() {
    std::cout << "test_empty_inputs\n";
    AutokeyCipher cipher;

    check(cipher.encrypt({}, to_codes("KEY")).empty(),
          "encrypt() with empty plaintext returns empty vector");
    check(cipher.encrypt(to_codes("HELLO"), {}).empty(),
          "encrypt() with empty key returns empty vector");
}

void test_zero_key_is_identity() {
    std::cout << "test_zero_key_is_identity\n";
    AutokeyCipher cipher;

    // A key of all zero bytes should leave the plaintext unchanged
    // regardless of how the key is indexed internally.
    auto plaintext = to_codes("HELLOWORLD");
    std::vector<uint8_t> key{0, 0, 0};

    auto ciphertext = cipher.encrypt(plaintext, key);
    check(ciphertext == plaintext,
          "all-zero key produces ciphertext identical to plaintext");
}

void test_round_trip() {
    std::cout << "test_round_trip: decrypt(encrypt(x, key), key) == x\n";
    AutokeyCipher cipher;

    auto plaintext = to_codes("ATTACKATDAWN");
    auto key = to_codes("LEMON");

    auto ciphertext = cipher.encrypt(plaintext, key);
    auto recovered = cipher.decrypt(ciphertext, key);

    check(recovered == plaintext,
          "decrypting an encrypted message recovers the original plaintext");

    if (recovered != plaintext) {
        std::cout << "    plaintext:  " << to_letters(plaintext) << "\n";
        std::cout << "    ciphertext: " << to_letters(ciphertext) << "\n";
        std::cout << "    recovered:  " << to_letters(recovered) << "\n";
    }
}

void test_key_advances_by_position() {
    std::cout << "test_key_advances_by_position\n";
    AutokeyCipher cipher;

    // Repeating the same plaintext letter under a multi-byte key should
    // produce *different* ciphertext letters as the key advances -- that's
    // the entire point of a polyalphabetic (Vigenere/autokey-style) cipher.
    auto plaintext = to_codes("AAAAAA");
    auto key = to_codes("BCD");

    auto ciphertext = cipher.encrypt(plaintext, key);

    bool all_same = true;
    for (size_t i = 1; i < ciphertext.size(); ++i) {
        if (ciphertext[i] != ciphertext[0]) {
            all_same = false;
            break;
        }
    }

    check(!all_same,
          "repeated plaintext letters produce varying ciphertext letters "
          "under a multi-byte key");

    if (all_same) {
        std::cout << "    ciphertext: " << to_letters(ciphertext)
                  << " (every position used the same key byte)\n";
    }
}

int main() {
    test_empty_inputs();
    test_zero_key_is_identity();
    test_round_trip();
    test_key_advances_by_position();

    std::cout << "\n" << (g_checks - g_failures) << "/" << g_checks
              << " checks passed\n";
    return g_failures == 0 ? 0 : 1;
}