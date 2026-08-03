#include <cstdint>
#include <cstdlib>
#include "pcsp/network.hpp"

// TODO: parse the listen port from argv (default per team convention),
// call start_server(port), then run_iterative_loop(server_fd).
// (REQ-NET-101/102)

int main(int argc, char** argv){
    uint16_t port = 8080;

    if (argc > 1){
    port = static_cast<uint16_t>(std::atoi(argv[1]));
    }

    int server_fd = start_server(port);

    if (server_fd < 0)
        return 1;

    run_iterative_loop(server_fd);
    return 0;
}
