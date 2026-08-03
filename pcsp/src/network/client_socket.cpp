#include "pcsp/network.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <src/ciphers/cipher_factory.cpp>
#include <cstdint>
#include <cstring>
#include <vector>


void print_ciphers(){
    std::cout << "List of Ciphers: \n"
              << "0x10 \t CaeserCipher \n"
              << "0x11 \t AffineCipher \n"
              << "0x12 \t AtbashCipher \n"
              << "0x13 \t MonoSubstitutionCipher \n"
              << "0x20 \t VigenereCipher \n"
              << "0x21 \t BeaufortCipher \n"
              << "0x22 \t AutokeyCipher \n"
              << "0x30 \t PlayfairCipher \n"
              << "0x31 \t HillCipher \n"
              << "0x40 \t RailFenchCipher \n"; 

}

int connect_to_server(const char* ip_address, uint16_t port) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd < 0)
        return -1;

    sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip_address, &server_addr.sin_addr) <= 0) {
        close(sock_fd);
        throw std::invalid_argument("Invalid IP address format");
    }

    if (connect(sock_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        close(sock_fd);
        throw std:: invalid_argument("Connection Failed!");
    }

    char* message;
    size_t msg_size = 0;
    

    while (true)
    {   
        size_t read = getline(&message, &msg_size, stdin);


        /* CIPHER STUFF */
        print_ciphers();
        std::cout << "Enter Cipher ID \n";
        uint8_t cipherID = NULL;
        std::cin >> cipherID;
        auto cipher = create_cipher(cipherID);

        //KEY STUFF
        std::cout << "Enter the key";
        std::string key_txt;
        std::getline(std::cin, key_txt);
        std::vector<u_int8_t> key ( key_txt.begin(), key_txt.end());

        std::cout << "Enter a Message or type EXIT to quit";
        std::cin >> message;
        std::vector<uint8_t> int_message(
            reinterpret_cast<uint8_t*>(message),
            reinterpret_cast<uint8_t*>(message) + std::strlen(message));
        auto encrypted_message = cipher ->encrypt(int_message, key);

        if (strcmp(message, "EXIT\n")){
            std::cout <<"[INFO]: Message Loop Ended: Exiting...";
            break;
        }
        send(sock_fd,message,strlen(message), 0);
       
    }
    

    return sock_fd;
}