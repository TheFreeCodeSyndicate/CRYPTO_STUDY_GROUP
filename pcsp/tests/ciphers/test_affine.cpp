#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <numeric>
#include "pcsp/ciphers/affine.hpp"


namespace {

int g_failures = 0;
int g_expected_failures = 0;

void check(bool condition, const std::string& test_name) {
    if (condition) {
        printf("\033[32m [PASS] \033[0m");
        std::cout << test_name << std::endl;
    } else {
        printf("\033[31m [FAIL] \033[0m");
        std::cout << test_name << std::endl;
        ++g_failures;
    }
}


} // namespace

int main() {
    AffineCipher cipher;
    {
        std::vector<uint8_t> plaintext(26);
        std::iota(plaintext.begin(), plaintext.end(), 0); // 0..25
        std::vector<uint8_t> key = { 7, 0 }; // a=7 (inverse is 15), b=0

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        std::vector<uint8_t> recovered  = cipher.decrypt(ciphertext, key);

        check(recovered == plaintext, "round_trip_b_zero_full_alphabet_domain");
    }

    {
        std::vector<uint8_t> plaintext = { 0, 1, 2, 7, 22, 25 };
        std::vector<uint8_t> key       = { 7, 3 };
        std::vector<uint8_t> expected  = { 3, 10, 17, 0, 1, 22 }; // (7t+3) mod 26

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        check(ciphertext == expected, "known_vector_encrypt_a7_b3");
    }

    {
        std::vector<uint8_t> plaintext(26);
        std::iota(plaintext.begin(), plaintext.end(), 0);
        std::vector<uint8_t> key = { 7, 3 };

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        std::vector<uint8_t> recovered  = cipher.decrypt(ciphertext, key);

        check(recovered == plaintext,
                         "round_trip_b_nonzero_full_alphabet_domain");
    }


    {
        std::vector<uint8_t> ciphertext = { 0 };
        std::vector<uint8_t> key        = { 7, 3 };
        std::vector<uint8_t> expected   = { 7 };

        std::vector<uint8_t> recovered = cipher.decrypt(ciphertext, key);
        check(recovered == expected, "decrypt_negative_subtraction_underflow");
    }

    {
        std::vector<uint8_t> plaintext = { 25 };
        std::vector<uint8_t> key       = { 25, 25 };
        std::vector<uint8_t> expected  = { 0 };

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        check(ciphertext == expected, "encrypt_overflow_before_mod26");
    }

    {
        std::vector<uint8_t> plaintext = { 1, 2, 3 };
        std::vector<uint8_t> key       = { 4, 8 }; // a=4, not coprime to 26

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        check(ciphertext.empty(), "encrypt_rejects_noninvertible_a");
    }

    {
        std::vector<uint8_t> plaintext = { 1, 2, 3 };
        std::vector<uint8_t> key       = { 5, 8, 1 }; // wrong size, a=5 IS coprime to 26

        std::vector<uint8_t> ciphertext = cipher.encrypt(plaintext, key);
        check(ciphertext.empty(), "encrypt_rejects_wrong_size_key");
    }

    
    {
        std::vector<uint8_t> plaintext;
        std::vector<uint8_t> key = { 7, 3 };

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