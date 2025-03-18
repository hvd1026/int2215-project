# Space Shooter 🚀
In this game, the player controls a spaceship on a journey through the universe. Along the way, they will encounter alien enemies. The goal is to use their piloting skills to dodge and shoot down all enemies in order to achieve the highest score.
## 📌 Features
+ Uses keyboard to control
+ Enemies appear randomly
+ Difficulty gradually increases
+ Score system based on damage dealt to enemies.
## 🎥 Demo Video
**Video URL**: https://youtu.be/XpFIGYSv71c
## 🛠 Technologies Used
+ **Programming Language**: C++
+ **Graphics Library**: SDL2
+ **Code editor**: Visual Studio Code
+ **Version Control**: Git, Github
## 📥 Installation & Running the Game
 **Tested Platforms**
 + [x] Linux (Fedora 40, Ubuntu 22.04)
 + [x] Windows (Windows 10)
 + [ ] MacOS

**Requirements**
+ C++ Compiler (GCC, MinGW)
+ GNU make
+ SDL2, SDL2_image, SDL2_mixer libraries

**Installation Steps**
1. Clone the repository
```
git clone https://github.com/hvd1026/int2215-project.git
cd int2215-project
```
2. Install SDL2 dependencies
- On Windows:
  + Download SDL2, SDL2_image, and SDL2_mixer from SDL's official website.
  + Extract the downloaded files and place them in the ```sdl/``` folder inside the project directory.
  + Add all ```.dll``` files to the project directory.
- On Linux(Debian-based):
```
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
```
- On Linux(Fedora-based):
```
sudo dnf install SDL2-devel SDL2_image-devel SDL2_mixer-devel
```
3. Compile the game using Makefile:
  ```
  make build
  ```
4. Run the game:
```
make run
```
## 🎮 How to Play
+ **Arrow Keys**: Move the spaceship.
+ **Spacebar**: Shoot bullets.

## 🎨 Credits
+ Images & Sprites:
  + https://grafxkid.itch.io/mini-pixel-pack-3
  + https://screamingbrainstudios.itch.io/seamless-space-backgrounds
  + https://cassala.itch.io/bubble-sprites
  + https://nicolemariet.itch.io/pixel-heart-animation-32x32-16x16-freebie
+ Sound Effects & Music:
  + https://kronbits.itch.io/freesfx
