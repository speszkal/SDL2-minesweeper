# SDL2-minesweeper
Minesweeper copy made using SDL2.

## Installation
I didn't want to include the whole SDL2 library in the repo so if you want to play the game you'll also have to download SDL2 and setup it the same way i did. </br>

1. Download the `main.exe` file.
2. Download the `graphics/` folder.
3. Install th required libraries (SDL2):
  - Install the `include/` and `lib/` folders from the `x86_64-w64-mingw32/` folder from the MinGW version of [SDL2](https://github.com/libsdl-org/SDL/releases/tag/release-2.26.5) to this path `./libs/SDL2/` and the `SDL2.dll` file to this path `./` (the `./` path is the current working directory).
  - Install the `include/` and `lib/` folders from the `x86_64-w64-mingw32/` folder from the MinGW version of [SDL-image](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.8.2) to this path `./libs/SDL2-image/` and the `SDL2_image.dll` file to this path `./`.
  - Install the `include/` and `lib/` folders from the `x86_64-w64-mingw32/` folder from the MinGW version of [SDL-ttf](https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.22.0) to this path `./libs/SDL2-ttf/` and the `SDL2_ttf.dll` file to this path `./`.
4. Open the terminal, navigate to the current working directory and run `main.exe` (it's beter to run `main.exe` through the terminal, otherwise you won't be able to see win/lose messages or potential error messages).

#### In the end your file tree should look something like this:
graphics/ <br>
libs/ <br>
├─ SDL2/ <br>
│  ├─ include/ <br>
│  ├─ lib/ <br>
├─ SDL2-image/ <br>
│  ├─ include/ <br>
│  ├─ lib/ <br>
├─ SDL2-ttf/ <br>
│  ├─ include/ <br>
│  ├─ lib/ <br>
main.exe <br>
SDL2.dll <br>
SDL2_image.dll <br>
SDL2_ttf.dll <br> <br>
**NOTE: Inside the `include/` and `lib/` folders there can't be another folder (like `SDL2/`), but instead the raw SDL files (like `SDL_image.h`).**
