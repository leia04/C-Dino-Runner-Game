# Terminal Dino Runner (C / ncurses)

## Abstract
A terminal-based runner game implemented in C using ncurses. The player avoids obstacles, collects items with temporary effects, and aims for a high score. The project focuses on real-time game loop design and modular C code organization. The project emphasizes low-level system design and real-time input handling without relying on external game engines.


## Features
- Real-time game loop with collision detection
- Jump and crouch controls
- Random items affecting gameplay
- Pause/resume functionality
- Local score persistence and leaderboard
- Multiple playable characters (ASCII-based)

## Project Structure
- `src/`: gameplay logic, rendering, UI, score handling
- `include/`: headers and shared constants
- `demo/`: gameplay demo assets (video / GIF)

## How to Run

#### Prerequisites
- C compiler (gcc or clang)
- `ncurses` library

#### Install ncurses
macOS (Homebrew):
```bash
brew install ncurses
```
Ubuntu / Debian:
```bash
sudo apt-get update
sudo apt-get install -y libncurses5-dev libncursesw5-dev
```

#### Build and Run
```bash
make
./dino_game
```

## Controls
- Jump: `Space` / `Up Arrow`
- Crouch: `Down Arrow`
- Pause/Resume: `p`
- Restart: `r`
- Quit: `q`

## Demo
![Gameplay demo](demo/demo.gif)
Full video: [dino_game_video.mp4](demo/dino_game_video.mp4)

## Tech Stack
- C
- ncurses

## Contribution
- Independently designed and implemented the entire project, including the real-time game loop and input handling.
- Built an ncurses-based rendering system for characters, obstacles, and background elements.
- Implemented collision detection, item mechanics, and game state management.
- Designed a local score persistence system with leaderboard parsing and display.
- Refactored the original monolithic code into modular C components to improve clarity, maintainability, and extensibility.
