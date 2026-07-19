#include <iostream>
#include "pcsp/protocol.hpp"

// Standalone roundtrip check for serialize_header()/deserialize_header()
// (REQ-NET-104). Build in isolation: `make -C tests protocol`.
int main() {
    PCSPHeader h{};
    h.version     = 0x01;
    h.cipher_id   = 0x20;   // Vigenere, for illustration
    h.key_length  = 5;
    h.payload_len = 16;

    PCSPHeader net  = serialize_header(h);
    PCSPHeader back = deserialize_header(net);
    (void)back; // TODO: remove once real assertions are added below

    std::cout << "TODO: assert back.key_length == h.key_length "
              << "and back.payload_len == h.payload_len (byte-order roundtrip)"
              << std::endl;
    return 0;
}
