# Makefile for the renderer project. requires GNU Make
# This Makefile automates the build process for the renderer project, including configuration, library and dependency downloads

# select compiler
CXX = g++
# select compiler flags
CXXFLAGS = -std=c++23 -g -Wall

INCLUDEPATH = -Ilib/glad/build/include -Ilib/glfw/include -Ilib/glm -Ilib/stb -Ilib/ft2/include -Ilib/assimp/include -Ilib/assimp/build/include
LIB_GLFW = lib/glfw/build/src/libglfw.so
LIB_FT2 = lib/ft2/objs/.libs/libfreetype.so
LIB_ASSIMP = lib/assimp/build/bin/libassimp.so.6.0.2

OSFLAG = UNKNOWN
# Detect the operating system
ifeq ($(OS),Windows_NT)
	WIN_ARCH = $(wmic OS get OSArchitecture)
	ifeq ($(PROCESSOR_ARCHITECTURE),64-bit)
		OSFLAG = WIN64
	endif
	ifeq ($(OSFLAG),UNKNOWN)
		OSFLAG = WIN32
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG = LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG = MACOS
	endif
endif

.PHONY: all clean test

all: config build

test: TEST = -DTESTMODE=1
test: config build

FILESTRUCTURE = lib bin obj obj/test obj/stage

clean:
	@echo "Cleaning up..."
	@rm -rf $(FILESTRUCTURE)
	@echo "Cleaning complite."

config: config-file lib-downloads
	@echo "Configuration complite."

config-file: $(FILESTRUCTURE)
	@echo "all necessary directories created."

$(FILESTRUCTURE):
	@mkdir -p $@

lib-downloads: lib/glad/build/src/gl.c lib/glfw/installed.flag lib/glm/installed.flag lib/stb/installed.flag lib/ft2/installed.flag lib/assimp/installed.flag
	@echo "lib downloads complite."

lib/assimp/installed.flag: lib/assimp/assimp.zip
	@echo "Install assimp..."
	@unzip -o lib/assimp/assimp.zip -d lib/assimp
	@mv -n lib/assimp/assimp-6.0.2/* lib/assimp
	@echo "building assimp..."
	@cd lib/assimp && cmake CMakeLists.txt -B build -D CMAKE_BUILD_TYPE=Release -D ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT=OFF -D ASSIMP_BUILD_OBJ_IMPORTER=ON -D ASSIMP_BUILD_FBX_IMPORTER=ON -D ASSIMP_BUILD_GLTF_IMPORTER=ON -D ASSIMP_BUILD_TESTS=OFF -D ASSIMP_BUILD_SAMPLES=OFF -D ASSIMP_BUILD_DOCS=OFF
	@cd lib/assimp/build && make
	@echo "assimp Install complite."
	@touch lib/assimp/installed.flag	

lib/assimp/assimp.zip:
	@echo "Downloading assimp..."
	@mkdir -p lib/assimp
	@curl -s -L -o lib/assimp/assimp.zip https://github.com/assimp/assimp/archive/refs/tags/v6.0.2.zip

lib/ft2/installed.flag: lib/ft2/ft2.tar.gz
	@echo "Install ft2..."
	@tar -xvzf lib/ft2/ft2.tar.gz -C lib/ft2
	@mv -n lib/ft2/freetype-2.14.1/* lib/ft2
	@echo "building ft2..."
	@cd lib/ft2 && make
	@cd lib/ft2 && make
	@echo "ft2 Install complite."
	@touch lib/ft2/installed.flag

lib/ft2/ft2.tar.gz:
	@echo "Downloading ft2..."
	@mkdir -p lib/ft2
	@curl -s -L -o lib/ft2/ft2.tar.gz https://download.savannah.gnu.org/releases/freetype/freetype-2.14.1.tar.gz

lib/stb/installed.flag: lib/stb/stb.zip
	@echo "Install stb..."
	@unzip -o lib/stb/stb.zip -d lib/stb
	@mv -n lib/stb/stb-master/* lib/stb/stb
	@rm -rf lib/stb/stb-master
	@echo "stb Install complite."
	@touch lib/stb/installed.flag

lib/stb/stb.zip:
	@echo "Downloading stb..."
	@mkdir -p lib/stb/stb
	@curl -s -L -o lib/stb/stb.zip https://github.com/nothings/stb/archive/refs/heads/master.zip
	
lib/glm/installed.flag: lib/glm/glm-1.0.2.zip
	@echo "Install glm..."
	@unzip -o lib/glm/glm-1.0.2.zip -d lib/glm
	@echo "glm Install complite."
	@touch lib/glm/installed.flag

lib/glm/glm-1.0.2.zip:
	@echo "Downloading glm..."
	@mkdir -p lib/glm
	@curl -s -L -o lib/glm/assets.json https://api.github.com/repos/g-truc/glm/releases/tags/1.0.2
	@python download_json.py lib/glm/assets.json

lib/glad/build/src/gl.c: lib/glad/installed.flag
	@echo "building glad..."
	@python -m venv lib/glad/venv
	@lib/glad/venv/bin/pip install -r lib/glad/requirements.txt
	@cd lib/glad && venv/bin/python -m glad --out-path=build --api=gl:core=4.3 c --loader
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

lib/glfw/build/CMakeCache.txt: lib/glfw/installed.flag

lib/glfw/installed.flag: lib/glfw/glfw-3.4.zip

ifeq ($(OSFLAG),WIN64)
	@echo "building glfw..."
	@unzip -o lib/glfw/glfw-3.4.bin.WIN64.zip -d lib/glfw
	@mv lib/glfw/glfw-3.4.bin.WIN32/lib-mingw-64/* lib/glfw/build
	@echo "glfw build complite."
	@echo "not yet implemented for win64"
	@exit 1
endif
ifeq ($(OSFLAG),WIN32)
	@echo "building glfw..."
	@unzip -o lib/glfw/glfw-3.4.bin.WIN32.zip -d lib/glfw
	@mv lib/glfw/glfw-3.4.bin.WIN64/lib-mingw-32/* lib/glfw/build
	@echo "glfw build complite."
	@echo "not yet implemented for win32"
	@exit 1
endif
ifeq ($(OSFLAG),MACOS)
	@echo "building glfw..."
	@unzip -o lib/glfw/glfw-3.4.bin.WIN64.zip -d lib/glfw
	@mv lib/glfw/glfw-3.4.bin.WIN64/lib-arm64/* lib/glfw/build
	@echo "glfw build complite."
	@echo "not yet implemented for macos"
	@exit 1
endif
ifeq ($(OSFLAG),LINUX)
	@echo "building glfw..."
	@unzip -o lib/glfw/glfw-3.4.zip -d lib/glfw
	@mv lib/glfw/glfw-3.4/* lib/glfw/
	@rm -rf lib/glfw/glfw-3.4
	@echo "Configuring glfw..."
	@cd lib/glfw && cmake -B build -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=ON -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF -D GLFW_BUILD_DOCS=OFF
	@echo "Compiling glfw..."
	@cd lib/glfw/build && make
	@echo "glfw build complite."
endif
ifeq ($(OSFLAG),UNKNOWN)
	@echo "Unsupported OS:$(OSFLAG)"
	@echo "OS: $(OS)"
	@echo "UNAME_S: $(UNAME_S)"
	@exit 1
endif
	@touch lib/glfw/installed.flag
	@echo "glfw already installed."

lib/glfw/glfw-3.4.zip:
	@echo "Downloading glfw..."
	@mkdir -p lib/glfw
	@curl -s -L -o lib/glfw/assets.json https://api.github.com/repos/glfw/glfw/releases/tags/3.4
	@python download_json.py lib/glfw/assets.json

BUILD_FILES = \
	Renderer\
	Transformable\
	test/TriangleTest\
	Camera\
	OrthographicCamera\
	PerspectiveCamera\
	ShaderProgram\
	ComputeShader\
	ShaderBase\
	Texture\
	Square\
	Cube\
	stage/ForwardGeometry\
	Font\
	Vector\
	Text\
	Model\
	Mesh
OBJECTS_FILES = $(foreach file,$(BUILD_FILES),obj/$(file).o)

build: bin/main.exe
	@rm -rf bin/test bin/shaders
	@cp -r test bin/test
	@cp -r shaders bin/shaders
	@echo "Build complite."

bin/main.exe: test/main.cpp bin/libglfw.so bin/libfreetype.so bin/libassimp.so.6 $(OBJECTS_FILES)
	@$(CXX) $(CXXFLAGS) $(INCLUDEPATH) $(TEST) -o bin/main.out test/main.cpp -Wl,-rpath=. bin/libglfw.so bin/libfreetype.so bin/libassimp.so.6 $(OBJECTS_FILES) lib/glad/build/src/gl.c

bin/libglfw.so:
	@cp $(LIB_GLFW) bin/libglfw.so
bin/libfreetype.so:
	@cp $(LIB_FT2) bin/libfreetype.so
bin/libassimp.so.6:
	@cp $(LIB_ASSIMP) bin/libassimp.so.6

$(OBJECTS_FILES): obj/%.o: %.cpp %.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDEPATH) $(TEST) -c $< -o $@
