all: build run

clean:
	@echo "Cleaning the build directory..."
	rm -rf build
build:
	@echo "Building the project..."
	cmake -S . -B build -G "Ninja"

run: build
	@echo "Running the project..."
	cmake --build build && ./build/src/VulkanApp

rebuild: 
	@echo "Rebuilding the project..."
	$(MAKE) clean
	$(MAKE) run