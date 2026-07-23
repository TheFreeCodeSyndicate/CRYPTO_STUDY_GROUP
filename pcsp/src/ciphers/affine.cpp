#include "pcsp/ciphers/affine.hpp"
#include <iostream>
#include <numeric>

std::vector<uint8_t> AffineCipher::encrypt(
    const std::vector<uint8_t>& plaintext,
    const std::vector<uint8_t>& key) const
{
    uint32_t a = key[0], b = key[1] ;

    std::vector<uint8_t>ciphertext;
    if (key.size() != 2 || std::gcd(key[0], 26) != 1) {
       std::cerr << "AffineCipher::encrypt: key must be 2 bytes (a, b) and a must be coprime to 26" << std::endl;
       return {};
    }
    ciphertext.reserve(plaintext.size());
    for(uint8_t t : plaintext){
        uint32_t encrypted_byte = (a*t +b)%26;
        ciphertext.push_back((uint8_t)encrypted_byte);
    }
    return ciphertext; 
}


std::vector<uint8_t> AffineCipher::decrypt(
    const std::vector<uint8_t>& ciphertext,
    const std::vector<uint8_t>& key) const
{
     uint32_t a = key[0], b = key[1], a_inv = 0, flag = 0, diff = 0;

    for(uint32_t i = 0; i < 26; i++){
        if((a*i)%26 == 1){
            a_inv = i;
            flag = 1;
            break;
        }
     }
     if (key.size() != 2 || std::gcd(key[0], 26) != 1) {
       std::cerr << "AffineCipher::decrypt: key must be 2 bytes (a, b) and a must be coprime to 26" << std::endl;
       return {};
    }
    std::vector<uint8_t>plaintext;
    plaintext.reserve(ciphertext.size());

    for(uint8_t t : ciphertext){
        diff = static_cast<uint32_t>(t) - b;
        diff = (diff + 26) % 26;
        uint32_t decrypted_bytes = a_inv*diff%26;
        plaintext.push_back((uint8_t)decrypted_bytes);
    }

    return plaintext;
}
