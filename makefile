# Makefile for the renderer project. requires GNU Make
# This Makefile automates the build process for the renderer project, including configuration, library and dependency downloads

# select compiler
CXX = g++
# select compiler flags
CXXFLAGS = -std=c++17 -g -Wall

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

lib-downloads: lib/glad/build/src/gl.c lib/glfw/glfw.zip
	@echo "lib downloads complite."

lib/glad/build/src/gl.c: lib/glad/installed.flag
	@echo "building glad..."
	@python -m venv lib/glad/venv
	@lib/glad/venv/bin/pip install -r lib/glad/requirements.txt
	@cd lib/glad && venv/bin/python -m glad --out-path=build --api=gl:core=3.3 c --loader
	ls
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

lib/glfw/glfw.zip:
	@echo "Downloading glfw..."
	@mkdir -p lib/glfw