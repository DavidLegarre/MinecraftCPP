CMAKE ?= cmake
BUILD_DIR ?= build
CMAKE_BUILD_TYPE ?= Release
BINARY := $(BUILD_DIR)/MinecraftCPP
GLSLC ?= glslc
CLANG_FORMAT ?= clang-format

.DEFAULT_GOAL := all

.PHONY: all configure build run shaders format lint clean clean-shaders distclean rebuild help

all: build

configure:
	$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

build: configure
	$(CMAKE) --build $(BUILD_DIR) -- -j$(shell nproc)

run: build
	$(BINARY)

shaders:
	find assets/ -type f \( -name '*.vert' -o -name '*.frag' -o -name '*.slang' \) | while read src; do \
		if command -v $(GLSLC) >/dev/null 2>&1; then \
			$(GLSLC) "$$src" -o "$$src.spv"; \
		else \
			echo "glslc not found. Install Vulkan SDK."; \
			exit 1; \
		fi; \
	done

format:
	find src/ -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \) -exec $(CLANG_FORMAT) -i -style=file {} +

lint:
	$(CMAKE) --build $(BUILD_DIR) --target $(BINARY) -- -j$(shell nproc) 2>&1 | head -1 || true
	find src/ -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \) -exec $(CLANG_FORMAT) --dry-run -Werror -style=file {} +

clean:
	rm -rf $(BUILD_DIR)

clean-shaders:
	find assets/ -name '*.spv' -delete

distclean: clean clean-shaders
	rm -rf $(BUILD_DIR) compile_commands.json

rebuild: clean build

help:
	@echo "Targets:"
	@echo "  all           - build (default)"
	@echo "  configure     - cmake configure"
	@echo "  build         - configure + compile"
	@echo "  run           - build + run"
	@echo "  shaders       - compile GLSL/Slang to SPIR-V"
	@echo "  format        - clang-format src/ recursively"
	@echo "  lint          - format check + build check"
	@echo "  clean         - remove build/"
	@echo "  clean-shaders - remove .spv files"
	@echo "  distclean     - clean + shaders + artifacts"
	@echo "  rebuild       - clean + build"
