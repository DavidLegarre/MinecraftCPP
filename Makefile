BUILD_DIR  := build
BUILD_TYPE ?= Debug
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

.PHONY: all configure build run clean rebuild

all: build

configure:
	cmake -S . -B $(BUILD_DIR) $(CMAKE_FLAGS)

build: configure
	cmake --build $(BUILD_DIR) -j

run: build
	./$(BUILD_DIR)/minecraft

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean build
