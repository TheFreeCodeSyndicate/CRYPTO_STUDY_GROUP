#include "pcsp/network.hpp"

// TODO(REQ-NET-103): create AF_INET/SOCK_STREAM socket, resolve
// `ip_address` with inet_pton(), connect() to `port`. Return the connected
// socket fd, or -1 on failure (caller decides how to report it).
int connect_to_server(const char* ip_address, uint16_t port) {
    (void)ip_address;
    (void)port;
    return -1; // placeholder
}
