# PCSP — Poly-Cipher Socket Protocol

Scaffolding only. Every header declares the exact contracts from the SRS /
API doc; every `.cpp` is a stub with a `TODO(REQ-...)` marking what to fill
in. The project builds and links out of the box (identity-transform
placeholders), so `git clone` -> `make` works for everyone from commit zero.

Full specs live in `docs/PCSP_SRS.pdf` and `docs/PCSP_API_DOC.pdf`.

## Layout

```
include/pcsp/            <- shared contracts (the "rigid interface boundaries")
  protocol.hpp            PCSPHeader struct, serialize/deserialize, parse/dispatch decls
  network.hpp             server/client socket function decls
  diagnostics.hpp         print_hex + telemetry decls
  status.hpp               PCSPStatus enum, validate_packet, is_invertible_mod26
  icipher.hpp              ICipher interface + create_cipher() factory decl
  ciphers/<name>.hpp        one header per cipher, all inherit ICipher

src/
  network/                 REQ-NET-101/102/103 socket contracts
  protocol/                 protocol.cpp (REQ-NET-104 byte order),
                            parser.cpp (REQ-PRT-202/203 state machine + dispatch)
  diagnostics/              REQ-DSP telemetry
  safety/                   REQ-NFR-802 validation
  ciphers/                  cipher_factory.cpp + one .cpp per cipher
  server_main.cpp           pcsp_server entry point
  client_main.cpp           pcsp_client entry point

tests/
  ciphers/test_<name>.cpp   standalone per-cipher test main (no sockets needed)
  test_protocol.cpp         standalone header serialization roundtrip test
  Makefile                  builds each test in isolation

docs/                       PCSP_SRS.pdf, PCSP_API_DOC.pdf
```

## Building

```sh
make            # builds bin/pcsp_server and bin/pcsp_client
make server     # just the server
make client     # just the client
make tests      # builds every standalone cipher/protocol test binary
make -C tests caesar    # build just one cipher's test, e.g. bin/tests/test_caesar
make clean      # removes build/ and bin/
```

## Division of labor (API Doc Sec 7)

| Owner                      | Files                                      | Requirements            |
|-----------------------------|---------------------------------------------|--------------------------|
| Network Operations          | `src/network/*`, `include/pcsp/network.hpp` | REQ-NET-101/102/103/104 |
| State Parsing                | `src/protocol/*`, `include/pcsp/protocol.hpp` | REQ-PRT-201/202/203     |
| Cryptographic Implementations | `src/ciphers/*.cpp` (not `cipher_factory.cpp`), `include/pcsp/ciphers/*` | REQ-CIP-401 .. REQ-CIP-702 |
| Diagnostics                  | `src/diagnostics/*`, `include/pcsp/diagnostics.hpp` | REQ-DSP-301/302        |
| Safety & QA                  | `src/safety/*`, `include/pcsp/status.hpp`   | REQ-NFR-801/802         |

Crypto devs never need to touch a socket: build and run your cipher alone
against its own test main via `make -C tests <name>`, per the interface
boundary the API doc establishes in Section 1.

`cipher_factory.cpp` (the `create_cipher()` switch) is owned by whoever is
doing State Parsing, since it's the one function that bridges the network
loop into the cipher subsystem.

## Cipher ID Registry

| ID   | Cipher                     | Key field format                     |
|------|-----------------------------|----------------------------------------|
| 0x10 | Caesar                      | 1 byte — shift K                      |
| 0x11 | Affine                       | 2 bytes — pair (a, b)                 |
| 0x12 | Atbash                       | 0 bytes — keyless                     |
| 0x13 | Monoalphabetic Substitution  | 26 bytes — permutation array          |
| 0x20 | Vigenère                    | Variable — ASCII string               |
| 0x21 | Beaufort                     | Variable — ASCII string               |
| 0x22 | Autokey                      | Variable — ASCII priming key          |
| 0x30 | Playfair                     | Variable — keyword string             |
| 0x31 | Hill                         | n² bytes — row-major matrix, mod 26   |
| 0x40 | Rail Fence                   | 1 byte — rail count                   |
| 0x41 | Columnar Transposition       | Variable — keyword string             |
