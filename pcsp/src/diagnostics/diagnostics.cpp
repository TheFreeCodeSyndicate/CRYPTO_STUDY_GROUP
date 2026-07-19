#include "pcsp/diagnostics.hpp"
#include <iostream>

// TODO(API Doc Sec 4.1): print each byte as two-digit lowercase hex,
// space-separated, prefixed by `label`.
void print_hex(const std::string& label, const std::vector<uint8_t>& data) {
    (void)data;
    std::cout << label << ": (TODO print_hex)" << std::endl;
}

// TODO(REQ-DSP-301): print plaintext, cipher id (0x-prefixed hex), key
// length, and the ciphertext via print_hex(), before transmission.
void log_client_telemetry(const std::string& plaintext,
                           uint8_t cipher_id,
                           const std::vector<uint8_t>& key,
                           const std::vector<uint8_t>& ciphertext) {
    (void)plaintext;
    (void)cipher_id;
    (void)key;
    (void)ciphertext;
}

// TODO(REQ-DSP-302): print, in order -- raw unresolved stream (print_hex),
// isolated ciphertext block (print_hex), recovered plaintext string.
void log_server_telemetry(const std::vector<uint8_t>& raw_stream,
                           const std::vector<uint8_t>& ciphertext,
                           const std::vector<uint8_t>& plaintext) {
    (void)raw_stream;
    (void)ciphertext;
    (void)plaintext;
}
