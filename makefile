DIR = Framework
FRAMEWORK_FILES = $(DIR)/Window.cpp $(DIR)/Vector2.cpp $(DIR)/Color.cpp $(DIR)/Rect.cpp $(DIR)/Texture.cpp $(DIR)/Renderer.cpp $(DIR)/Event.cpp $(DIR)/Sprite.cpp $(DIR)/Surface.cpp $(DIR)/Timer.cpp
OBJS = main.cpp $(FRAMEWORK_FILES)
CC = g++

INCLUDE_PATHS = -I E:\C\SDL\$(DIR)\SDL2-2.0.3\include\SDL2 -I E:\C\SDL\$(DIR)\SDL2_image-2.0.0\include\SDL2
LIBRARY_PATHS = -L E:\C\SDL\$(DIR)\SDL2-2.0.3\lib -L E:\C\SDL\$(DIR)\SDL2_image-2.0.0\lib

COMPILER_WARNINGS = -Wall -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wmain -pedantic -Wzero-as-null-pointer-constant -Wextra
COMPILER_FLAGS = -std=c++1y
COMPILER_FLAGS_DEBUG = -g
COMPILER_FLAGS_RELEASE = -O3

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = main

all:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_WARNINGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
debug:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_WARNINGS) $(COMPILER_FLAGS) $(COMPILER_FLAGS_DEBUG) $(LINKER_FLAGS) -o $(OBJ_NAME)
release:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_WARNINGS) $(COMPILER_FLAGS) $(COMPILER_FLAGS_RELEASE) $(LINKER_FLAGS) -o $(OBJ_NAME)