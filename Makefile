CC      := gcc
CFLAGS  := -Wall -Wextra -I./src
AR      := ar
ARFLAGS := rcs

SRC_DIR   := src
BUILD_DIR := build
TEST_DIR  := test
LIB_DIR   := lib
RELEASE_DIR := releases

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
STATIC_OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
SHARED_OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.shared.o, $(SRC_FILES))

# Determine OS to set dynamic library file name
ifeq ($(OS),Windows_NT)
    SHARED_LIB = lib/bb101.dll
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        SHARED_LIB =lib/libbb101.dylib
    else
        SHARED_LIB = lib/libbb101.so
    endif
endif

LIB = lib/libbb101.a

# Default target builds both static and dynamic libraries.
all: static dynamic

# Create build directory if needed.
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(RELEASE_DIR):
	mkdir -p $(RELEASE_DIR)

# --- Static Library Build ---
# Compile source files to object files (for static library).
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Archive object files into a static library.
static: $(LIB_DIR) $(LIB) $(RELEASE_DIR)
$(LIB): $(STATIC_OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

# --- Dynamic Library Build ---
# Compile source files to PIC object files.
$(BUILD_DIR)/%.shared.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Link the shared object files into a dynamic library.
dynamic: $(LIB_DIR) $(SHARED_LIB) $(RELEASE_DIR)
$(SHARED_LIB): $(SHARED_OBJ_FILES)
	$(CC) -shared -o $@ $^

# --- Install and Uninstall ---
install: $(SHARED_LIB)
ifeq ($(OS),Windows_NT)
	copy $(SHARED_LIB) C:\Windows\System32
else
	install -m 755 $(SHARED_LIB) /usr/local/lib
	ldconfig
endif

uninstall:
ifeq ($(OS),Windows_NT)
	del C:\Windows\System32\bb101.dll
else
	rm -f /usr/local/lib/libbb101.dylib
	rm -f /usr/local/lib/libbb101.so
endif

# --- Test Target ---
# Build and run the test executable using the global dynamic library.
test: dynamic
	$(CC) $(CFLAGS) $(TEST_DIR)/ejemplo.c -L/usr/local/lib -lbb101 -o test_library
	./test_library

# --- Clean ---
clean:
	rm -rf $(BUILD_DIR) $(LIB) $(SHARED_LIB) $(LIB_DIR) $(RELEASE_DIR) test_library

.PHONY: all static dynamic test clean