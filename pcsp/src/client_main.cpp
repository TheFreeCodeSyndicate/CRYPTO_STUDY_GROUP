#include <cstdint>
#include "pcsp/network.hpp"
#include "pcsp/protocol.hpp"
#include "pcsp/diagnostics.hpp"
#include "pcsp/icipher.hpp"

// TODO: parse argv (server ip, port, cipher id, key, plaintext), resolve
// the cipher via create_cipher(), encrypt(), pack [Header][Key][Payload]
// per REQ-PRT-202 using serialize_header(), call log_client_telemetry()
// (REQ-DSP-301), connect_to_server(), send() the packet, then read the
// connection to completion (REQ-NET-103).
int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    return 0;
}
