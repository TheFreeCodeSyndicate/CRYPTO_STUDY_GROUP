#ifndef PCSP_PROTOCOL_HPP
#define PCSP_PROTOCOL_HPP

#include <cstdint>
#include <vector>

// =============================================================================
// REQ-PRT-201 (SRS Sec 2.2 / API Doc Sec 3.1) — the rigid 6-byte wire header.
// Owner: Network Operations (struct layout) / State Parsing (consumers).
// =============================================================================
#pragma pack(push, 1)
struct PCSPHeader {
    uint8_t  version;      // Fixed at 0x01
    uint8_t  cipher_id;    // See Cipher ID Registry, API Doc Sec 5.2 / Table 1
    uint16_t key_length;   // Network byte order on the wire (REQ-NET-104)
    uint16_t payload_len;  // Network byte order on the wire (REQ-NET-104)
};
#pragma pack(pop)

// -----------------------------------------------------------------------------
// REQ-NET-104 (API Doc Sec 2.3 / 3.2) — the ONLY functions permitted to call
// htons()/ntohs(). Owner: Network Operations.
// -----------------------------------------------------------------------------
PCSPHeader serialize_header(const PCSPHeader& host_header);
PCSPHeader deserialize_header(const PCSPHeader& net_header);

// -----------------------------------------------------------------------------
// REQ-PRT-202/203 (API Doc Sec 3.3) — two-phase server parsing state machine:
// (1) read exactly 6 bytes, (2) dynamically size + read Key/Payload fields.
// Owner: State Parsing.
// -----------------------------------------------------------------------------
bool parse_incoming_stream(int client_fd);

// Glue step invoked by parse_incoming_stream once header + key + payload are
// fully read: resolves the cipher via the factory, decrypts, runs
// REQ-NFR-802 validation, and drives server-side telemetry (API Doc Sec 5.3
// & 4.3). Owner: State Parsing.
bool dispatch_and_report(const PCSPHeader& header,
                          const std::vector<uint8_t>& key,
                          const std::vector<uint8_t>& payload);

#endif // PCSP_PROTOCOL_HPP
