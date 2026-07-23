#include "pcsp/ciphers/vigenere.hpp"
#include <cctype>

// ascii only
uint8_t index_norm(uint8_t ch) {
    if (std::isupper(ch)) {
        return ch - 'A';
    }
    return ch - 'a';
}

uint8_t C(uint8_t P, uint8_t K) {
    uint8_t P_norm = index_norm(P), K_norm = index_norm(K);
    return (P_norm + K_norm) % 26; 
}

uint8_t P(uint8_t C, uint16_t K) {
    uint8_t C_norm = index_norm(C), K_norm = index_norm(K);
    return (C_norm - K_norm + 26) % 26;
}

// TODO(REQ-CIP-501): implement VigenereCipher::encrypt
// Key field format: Variable -- ASCII string
std::vector<uint8_t> VigenereCipher::encrypt(
    const std::vector<uint8_t>& plaintext,
    const std::vector<uint8_t>& key) const
{
    // reject empty key
    if (key.size() <= 0) {
        // not including the error message here right now.
        return {};
    }
    std::vector<uint8_t> ciphertext(plaintext.size());
    size_t key_index = 0;

    for (size_t i = 0; i < plaintext.size(); i++) {
        if (! std::isalpha(plaintext[i])) {
            ciphertext[i] = plaintext[i];
            continue;
        }
        if (! std::isalpha(key[key_index % key.size()])) {
            key_index = (key_index + 1) % key.size();
        }
        bool l = plaintext[i] >= 'a';
        ciphertext[i] = (l * 'a' + (!l) * 'A') + C(plaintext[i], key[key_index]);
        key_index = (key_index + 1) % key.size();
    }

    return ciphertext; // placeholder identity transform -- replace with real math
}

// TODO(REQ-CIP-501): implement VigenereCipher::decrypt
std::vector<uint8_t> VigenereCipher::decrypt(
    const std::vector<uint8_t>& ciphertext,
    const std::vector<uint8_t>& key) const
{
    if (key.size() <= 0) {
        // not including the error message here right now.
        return {};
    }
    std::vector<uint8_t> plaintext(ciphertext.size());
    size_t key_index = 0;

    for (size_t i = 0; i < ciphertext.size(); i++) {
        if (! std::isalpha(ciphertext[i])) {
            plaintext[i] = ciphertext[i];
            continue;
        }
        if (! std::isalpha(key[key_index % key.size()])) {
            key_index = (key_index + 1) % key.size();
        }
        bool l = ciphertext[i] >= 'a';
        plaintext[i] = (l * 'a' + (!l) * 'A') + P(ciphertext[i], key[key_index]);
        key_index = (key_index + 1) % key.size();
    }

    return plaintext; // placeholder identity transform -- replace with real math
}
