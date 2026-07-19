#include "pcsp/status.hpp"

// TODO(API Doc Sec 6.2): Extended Euclidean check -- a Hill key matrix is
// invertible mod 26 iff gcd(determinant mod 26, 26) == 1.
bool is_invertible_mod26(int determinant) {
    (void)determinant;
    return false; // placeholder
}

// TODO(REQ-NFR-802): compare key_bytes_read/payload_bytes_read against
// header.key_length/header.payload_len (-> ERR_LENGTH_MISMATCH if they
// differ), then confirm create_cipher(header.cipher_id) != nullptr
// (-> ERR_UNSUPPORTED_CIPHER otherwise). Hill-specific determinant checks
// are delegated to HillCipher's own constructor/validator.
PCSPStatus validate_packet(const PCSPHeader& header,
                           std::size_t key_bytes_read,
                           std::size_t payload_bytes_read) {
    (void)header;
    (void)key_bytes_read;
    (void)payload_bytes_read;
    return PCSPStatus::OK; // placeholder
}
