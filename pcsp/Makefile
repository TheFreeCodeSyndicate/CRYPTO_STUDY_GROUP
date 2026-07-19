CXX       := g++
CXXFLAGS  := -Wall -Wextra -std=c++17 -g -Iinclude
LDFLAGS   :=

SRC_DIR   := src
BUILD_DIR := build
BIN_DIR   := bin

SERVER_MAIN := $(SRC_DIR)/server_main.cpp
CLIENT_MAIN := $(SRC_DIR)/client_main.cpp

# Every .cpp under src/, minus the two program entry points, is shared
# between both binaries (network, protocol, diagnostics, safety, ciphers).
ALL_SRCS    := $(shell find $(SRC_DIR) -name '*.cpp')
COMMON_SRCS := $(filter-out $(SERVER_MAIN) $(CLIENT_MAIN),$(ALL_SRCS))

COMMON_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(COMMON_SRCS))
SERVER_OBJS := $(COMMON_OBJS) $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SERVER_MAIN))
CLIENT_OBJS := $(COMMON_OBJS) $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CLIENT_MAIN))

SERVER_BIN := $(BIN_DIR)/pcsp_server
CLIENT_BIN := $(BIN_DIR)/pcsp_client

.PHONY: all server client tests clean

all: server client

server: $(SERVER_BIN)
client: $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(CLIENT_BIN): $(CLIENT_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Pattern rule mirrors src/<subdir>/<file>.cpp -> build/<subdir>/<file>.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Delegates to tests/Makefile, which builds each cipher/protocol test in
# isolation (see Division of Labor, API Doc Sec 7).
tests:
	$(MAKE) -C tests

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	$(MAKE) -C tests clean
