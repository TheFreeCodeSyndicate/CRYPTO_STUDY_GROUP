#include "pcsp/ciphers/autokey.hpp"
#include <iostream>


std::vector<uint8_t> AutokeyCipher::encrypt(
    const std::vector<uint8_t>& plaintext,
    const std::vector<uint8_t>& key) const
{
    if(plaintext.empty() || key.empty()){
        return {};
    }
   std::vector<uint8_t> ciphertext;
   ciphertext.reserve(plaintext.size());
    for (size_t i = 0; i < plaintext.size(); ++i) {
        uint8_t k = key[i % key.size()];
        ciphertext.push_back((plaintext[i] + k) % 26);
    }
    (void)key;
    return ciphertext; 
}


std::vector<uint8_t> AutokeyCipher::decrypt(
    const std::vector<uint8_t>& ciphertext,
    const std::vector<uint8_t>& key) const
{
    std::vector<uint8_t> plaintext;
    plaintext.reserve(ciphertext.size());
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        uint8_t k = key[i % key.size()];
        plaintext.push_back((ciphertext[i] + 26 - k) % 26);
    }
    (void)key;
    return plaintext; 
}
