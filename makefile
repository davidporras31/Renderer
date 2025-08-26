# Makefile for the renderer project. requires GNU Make
# This Makefile automates the build process for the renderer project, including configuration, library and dependency downloads

# select compiler
CXX = g++
# select compiler flags
CXXFLAGS = -std=c++17 -g -Wall

OSFLAG = UNKNOWN
# Detect the operating system
ifeq ($(OS),Windows_NT)
	WIN_ARCH = $(wmic OS get OSArchitecture)
	ifeq ($(PROCESSOR_ARCHITECTURE),64-bit)
		OSFLAG = WIN64
	endif
	OSFLAG ?= WIN32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG = LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG = MACOS
	endif
endif

.PHONY: all clean config config-file build lib-downloads

all: config build

FILESTRUCTURE = lib bin obj

clean:
	@echo "Cleaning up..."
	@rm -rf $(FILESTRUCTURE)
	@echo "Cleaning complite."

config: config-file lib-downloads
	@echo "Configuration complite."

config-file:
	@echo "Creating file structure..."
	@mkdir -p $(FILESTRUCTURE)

lib-downloads: lib/glad/build/src/gl.c lib/glfw/bin/libglfw3.a
	@echo "lib downloads complite."

lib/glad/build/src/gl.c: lib/glad/installed.flag
	@echo "building glad..."
	@python -m venv lib/glad/venv
	@lib/glad/venv/bin/pip install -r lib/glad/requirements.txt
	@cd lib/glad && venv/bin/python -m glad --out-path=build --api=gl:core=3.3 c --loader
	@echo "glad build complite."

lib/glad/installed.flag: lib/glad/glad.zip
	@echo "extracting glad..."
	@unzip -o lib/glad/glad.zip -d lib/glad
	@mv -n lib/glad/glad-glad2/* lib/glad
	@rm -rf lib/glad/glad-glad2
	@touch lib/glad/installed.flag
	@echo "glad installed."

lib/glad/glad.zip:
	@echo "Downloading glad..."
	@mkdir -p lib/glad
	@wget "https://github.com/Dav1dde/glad/archive/refs/heads/glad2.zip" -O lib/glad/glad.zip

lib/glfw/bin/libglfw3.a: lib/glfw/glfw-3.4.zip $(OSFLAG)

WIN64:
	@echo "building glfw..."
	@unzip -o lib/glfw/glfw-3.4.bin.WIN64.zip -d lib/glfw
	@mv lib/glfw/glfw-3.4.bin.WIN32/lib-mingw-64/* lib/glfw/bin
	@echo "glfw build complite."
WIN32:
	@echo "building glfw..."
	@unzip -o lib/glfw/glfw-3.4.bin.WIN32.zip -d lib/glfw
	@mv lib/glfw/glfw-3.4.bin.WIN64/lib-mingw-32/* lib/glfw/bin
	@echo "glfw build complite."
MACOS:
	@echo "building glfw..."
	@unzip -o lib/glfw/glfw-3.4.bin.WIN64.zip -d lib/glfw
	@mv lib/glfw/glfw-3.4.bin.WIN64/lib-arm64/* lib/glfw/bin
	@echo "glfw build complite."
LINUX:
	@echo "building glfw..."
	@unzip -o lib/glfw/glfw-3.4.zip -d lib/glfw
	@-mv lib/glfw/glfw-3.4/* lib/glfw/
	@rm -rf lib/glfw/glfw-3.4
	@cd lib/glfw && cmake -B build -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=ON -D GLFW_BUILD_EXAMPLES=OFF
	@echo "glfw build complite."
UNKNOWN:
	@echo "Unsupported OS:$(OSFLAG)"
	@echo "OS: $(OS)"
	@echo "UNAME_S: $(UNAME_S)"
	@exit 1



lib/glfw/glfw-3.4.zip:
	@echo "Downloading glfw..."
	@mkdir -p lib/glfw
	@curl -s -L -o lib/glfw/assets.json https://api.github.com/repos/glfw/glfw/releases/latest
	@python download_json.py lib/glfw/assets.json