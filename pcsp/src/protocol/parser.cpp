#include "pcsp/protocol.hpp"

// TODO(REQ-PRT-202/203): Phase 1 -- recv() exactly sizeof(PCSPHeader) with
// MSG_WAITALL, then deserialize_header(). Phase 2 -- dynamically size two
// std::vector<uint8_t> buffers from header.key_length / header.payload_len
// and recv() into them. Finish by calling dispatch_and_report().
bool parse_incoming_stream(int client_fd) {
    (void)client_fd;
    return false; // placeholder
}

// TODO(API Doc Sec 5.3 & 4.3): validate_packet() -> create_cipher() ->
// decrypt() -> log_server_telemetry(). On any REQ-NFR-802 failure, print the
// diagnostic status code and return false -- never terminate the process.
bool dispatch_and_report(const PCSPHeader& header,
                          const std::vector<uint8_t>& key,
                          const std::vector<uint8_t>& payload) {
    (void)header;
    (void)key;
    (void)payload;
    return false; // placeholder
}
