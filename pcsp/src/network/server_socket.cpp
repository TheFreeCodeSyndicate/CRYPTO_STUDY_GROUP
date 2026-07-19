#include "pcsp/network.hpp"

// TODO(REQ-NET-101): AF_INET/SOCK_STREAM socket, SO_REUSEADDR, bind() to
// `port`, listen(). Return the bound listening file descriptor.
int start_server(uint16_t port) {
    (void)port;
    return -1; // placeholder
}

// TODO(REQ-NET-102): accept() -> parse_incoming_stream(client_fd) -> close()
// -> loop back to accept(). Must never return and never call exit(); a
// malformed/unsupported packet degrades back to this loop (REQ-NFR-802),
// it does not terminate the server process.
void run_iterative_loop(int server_fd) {
    (void)server_fd;
}
