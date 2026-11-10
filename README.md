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

Requirements: CMake 3.16+, a C++17 compiler, and Git.

```bash
git clone --recursive https://github.com/JXDouDou/OOPL.git
cd OOPL
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build
```

Build in `Debug`; the framework's `Release` resource path does not work. The executable is created in `build/`. If you cloned without `--recursive`, run `git submodule update --init` first.

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
