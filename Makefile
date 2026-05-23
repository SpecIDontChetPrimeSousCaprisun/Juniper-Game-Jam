CXX = g++
WIN_CXX = x86_64-w64-mingw32-g++

# Targets
TARGET = game
WIN_TARGET = publish/windows/game.exe

WINDOWS_DLLS = /usr/x86_64-w64-mingw32/bin/glfw3.dll \
							 /usr/x86_64-w64-mingw32/bin/libassimp.dll \
							 /usr/x86_64-w64-mingw32/bin/libgcc_s_seh-1.dll \
							 /usr/x86_64-w64-mingw32/bin/libssp-0.dll \
							 /usr/x86_64-w64-mingw32/bin/libstdc++-6.dll \
							 /usr/x86_64-w64-mingw32/bin/zlib1.dll \
							 /usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll

# Flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
WINDOWS_CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude 

# Libraries
LIBS_LINUX = \
-lassimp \
-lglfw \
-lGL \
-ldl \
-lpthread \
-lX11 \
-lXrandr \
-lXi \
-lXxf86vm \
-lXcursor \
-lm

LIBS_WINDOWS = \
-L/usr/x86_64-w64-mingw32/lib \
-lassimp \
-lglfw3 \
-lopengl32 \
-lgdi32 \
-lwinmm

# Sources
SRC = src/stbImpl.cpp \
			src/glad.c \
			src/main.cpp \
			src/Window.cpp \
			src/Object.cpp \
			src/FileLoader.cpp \
			src/Player.cpp \
			src/Sound.cpp \
			src/UIElement.cpp \
			src/Font.cpp \
			src/TextElement.cpp \
			src/Container.cpp


PUBLISH_SRC = textures \
							fonts \
							shaders

# Object files
OBJ_DIR = build

OBJ = $(SRC:src/%.cpp=$(OBJ_DIR)/src/%.o)
OBJ := $(OBJ:src/glad.c=$(OBJ_DIR)/src/glad.o)

# Build
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS_LINUX)	

$(OBJ_DIR)/src/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/src/glad.o: src/glad.c
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

windows:
	mkdir -p build
	mkdir -p publish/windows

	$(WIN_CXX) \
	$(WINDOWS_CXXFLAGS) \
	$(SRC) \
	-o $(WIN_TARGET) \
	$(LIBS_WINDOWS)

test: all
	./$(TARGET)

clean:
	rm -rf build
	rm -f $(TARGET)
	rm -r $(WIN_TARGET)

publish:
	rm -rf publish
	mkdir -p publish/linux
	mkdir -p publish/windows

	cp -r $(PUBLISH_SRC) publish/linux
	$(MAKE)

	cp $(TARGET) publish/linux/$(TARGET)

	cp -r $(PUBLISH_SRC) $(WINDOWS_DLLS) publish/windows
	$(MAKE) windows

	cd publish && zip -r -9 linux.zip linux && zip -r -9 windows.zip windows

.PHONY: all clean test windows publish
