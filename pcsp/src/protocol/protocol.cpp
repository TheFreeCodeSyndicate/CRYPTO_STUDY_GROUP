#include "pcsp/protocol.hpp"

// TODO(REQ-NET-104): htons() key_length and payload_len before transmission.
// version/cipher_id are single bytes and pass through unchanged.
PCSPHeader serialize_header(const PCSPHeader& host_header) {
    return host_header; // placeholder -- no byte-order conversion yet
}

// TODO(REQ-NET-104): ntohs() key_length and payload_len immediately upon
// ingestion, before any length field is read by the caller.
PCSPHeader deserialize_header(const PCSPHeader& net_header) {
    return net_header; // placeholder -- no byte-order conversion yet
}
