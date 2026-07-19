#ifndef PCSP_DIAGNOSTICS_HPP
#define PCSP_DIAGNOSTICS_HPP

#include <cstdint>
#include <string>
#include <vector>

// =============================================================================
// Diagnostic & Telemetry Contract (REQ-DSP, API Doc Sec 4). Owner: Diagnostics.
// This subsystem only ever sees byte vectors + labels — never a cipher object
// or a socket descriptor.
// =============================================================================

// Shared hex-dump utility (API Doc Sec 4.1).
void print_hex(const std::string& label, const std::vector<uint8_t>& data);

// REQ-DSP-301 (API Doc Sec 4.2) — client prints plaintext, cipher id, key
// metadata, and the resulting ciphertext (via print_hex) before sending.
void log_client_telemetry(const std::string& plaintext,
                           uint8_t cipher_id,
                           const std::vector<uint8_t>& key,
                           const std::vector<uint8_t>& ciphertext);

// REQ-DSP-302 (API Doc Sec 4.3) — server prints the raw unresolved stream,
// the isolated ciphertext block, and the recovered plaintext, in that order.
void log_server_telemetry(const std::vector<uint8_t>& raw_stream,
                           const std::vector<uint8_t>& ciphertext,
                           const std::vector<uint8_t>& plaintext);

#endif // PCSP_DIAGNOSTICS_HPP
