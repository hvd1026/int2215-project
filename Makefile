CC := g++
EXEC := main.exe

FILES := \
    src/Pages/HomePage.cpp \
    src/Pages/GamePage.cpp \
    src/Collision/Collision.cpp \
    src/GameObject/Enemy.cpp \
    src/GameObject/Bullet.cpp \
    src/Manager/EventManager.cpp \
    src/GameObject/Player.cpp \
    src/Manager/GameManager.cpp \
    src/Manager/TimeManager.cpp \
    src/Manager/AssetManager.cpp \
    src/Animation/Animation.cpp \
    src/GameObject/Background.cpp \
    src/main.cpp

# Detect OS
OS := $(shell uname)
ifeq ($(OS),Linux)
    CFLAGS := -I/usr/include/SDL2 -L/usr/lib
    LIBS := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
    EXEC := main
else
	CFLAGS := -Isdl/include/SDL2 -Lsdl/lib
    LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
endif

all: build run

build:
	$(CC) -o $(EXEC) $(FILES) $(CFLAGS) $(LIBS)

run:
	./$(EXEC)