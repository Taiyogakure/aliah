# Directories
SRC_DIR = src
BUILD_DIR = build

# Compiler settings
CC = emcc
CFLAGS = -s WASM=1 -s USE_SDL=2 -O2 $(FILE_FLAGS) $(ASYNC_FLAGS) $(IMG_FLAGS)
FILE_FLAGS = -s FORCE_FILESYSTEM=1 --preload-file assets
ASYNC_FLAGS = -sASYNCIFY
IMG_FLAGS = -lSDL2_image

# Target files
TARGET = $(BUILD_DIR)/index.html
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/map.c $(SRC_DIR)/player.c

# Build command
build: $(SRC_FILES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_FILES) $(CFLAGS) -o $(TARGET)

# Clean command
clean:
	rm -rf $(BUILD_DIR)

# Run the project using emrun (WebAssembly server)
serve: build
	emrun --no_browser --port 8080 $(BUILD_DIR)

.PHONY: build clean serve
