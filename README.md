# Pacman-Style 2D Game (C++17)

A Pacman-style arcade game with five stages, built in C++17 on [PTSD](https://github.com/ntut-open-source-club/practical-tools-for-simple-design), an OpenGL-based framework used in the Object-Oriented Programming Lab course at National Taipei University of Technology (Spring 2024). Team project of two.

## Features

- Five stages, each defined in a JSON file (`Resources/Text/level00X.json`)
- Ghosts that switch between behavior states and chase the player using BFS pathfinding
- Score, lives and fruit systems, with high scores saved per stage
- Event manager that lets game systems react to events without depending on each other

## My contributions

- **Map:** building the tile map the player and ghosts move on
- **Score, lives and fruit systems**
- **Event manager:** an Observer-pattern design where systems register `std::function` listeners and are notified when an event fires, so score and life updates stay decoupled from the game loop
- **BFS pathfinding:** wrote the first part of the ghost pathfinding; my teammate completed it

## Controls

| Key | Action |
| --- | --- |
| Mouse click | Press the start button on the title screen |
| Arrow keys | Move |
| Esc | Return to the menu / quit |
| Space | Toggle debug mode |

## Build and run

Requirements: CMake 3.16+, a C++17 compiler, and Git. Dependencies (SDL2, GLEW, etc.) are downloaded automatically on the first configure. Tested on Windows with MinGW-w64 GCC 13.1 and Ninja.

```bash
git clone --recursive https://github.com/JXDouDou/OOPL.git
cd OOPL
```

If you cloned without `--recursive`, run `git submodule update --init` first.

### Distributable build (Release)

```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DPORTABLE=ON
cmake --build build
```

`PORTABLE=ON` makes the game load resources by relative path and copies `Resources/` and `assets/` next to `build/Pacman.exe`. Copy `Pacman.exe` together with those two folders to run it on another PC; with MinGW the runtime is statically linked, so no DLLs are needed. Start it from its own folder (e.g. by double-clicking), since paths are relative to the working directory.

### Development build (Debug)

```bash
cmake -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
```

Resources are read directly from the source tree. Non-Debug builds require `-DPORTABLE=ON`.

## Project structure

```
include/
  Level/        stages, player, ghosts and their states
  event/        event manager (Observer pattern)
  UI/           title screen and buttons
src/            app entry point and main loop
Resources/      images and stage/score JSON files
PTSD/           framework (git submodule)
```
