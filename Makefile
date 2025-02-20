all: build run

FILES = src/GameObject/Enemy.cpp src/GameObject/Bullet.cpp src/Manager/EventManager.cpp src/GameObject/Player.cpp src/Manager/GameManager.cpp src/Manager/TimeManager.cpp src/Manager/AssetManager.cpp src/Animation/Animation.cpp src/GameObject/Background.cpp

build:
	g++ -o main.exe \
	${FILES} \
	src/main.cpp \
	-Isdl/include/SDL2 -Lsdl/lib \
	-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
run:
	.\main.exe