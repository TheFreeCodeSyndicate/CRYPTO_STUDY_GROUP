#ifndef PCSP_NETWORK_HPP
#define PCSP_NETWORK_HPP

#include <cstdint>

// =============================================================================
// Network Transport Layer (REQ-NET). Owner: Network Operations.
// This is intentionally the "dumbest" subsystem: it moves bytes and knows
// nothing about cipher IDs or key formats (API Doc Sec 2).
// =============================================================================

// REQ-NET-101/102 (API Doc Sec 2.1) — passive socket + iterative server loop.
// run_iterative_loop must never return / never call exit(); malformed or
// unsupported packets degrade back to accept() (see REQ-NFR-802).
int  start_server(uint16_t port);
void run_iterative_loop(int server_fd);

// REQ-NET-103 (API Doc Sec 2.2) — active client connection to an IPv4
// loopback or remote address.
int connect_to_server(const char* ip_address, uint16_t port);

#endif // PCSP_NETWORK_HPP
