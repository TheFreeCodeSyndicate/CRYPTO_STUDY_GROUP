CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g -I../include
BIN_DIR  := ../bin/tests

# One target per cipher, matching src/ciphers/<name>.cpp + ciphers/test_<name>.cpp
CIPHERS  := caesar affine atbash mono_substitution vigenere beaufort autokey \
            playfair hill rail_fence columnar_transposition

.PHONY: all clean $(CIPHERS) protocol

all: $(CIPHERS) protocol

# `make -C tests caesar` (etc.) builds and does NOT run the test -- run the
# resulting binary yourself, e.g. ./../bin/tests/test_caesar
$(CIPHERS): %: $(BIN_DIR)/test_%

$(BIN_DIR)/test_%: ciphers/test_%.cpp ../src/ciphers/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

protocol: $(BIN_DIR)/test_protocol

$(BIN_DIR)/test_protocol: test_protocol.cpp ../src/protocol/protocol.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)
