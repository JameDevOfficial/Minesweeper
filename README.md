<div align="center">
<img src="assets/logo.png" width="100%" alt="Minesweeper Logo"/>

Minesweeper is a CLI implementation of the classical Minesweeper game.

[![Minesweeper](https://hackatime-badge.hackclub.com/U087BUC6ZFW/Minesweeper?logo=hackclub&logoColor=white)](https://hackatime-badge.hackclub.com/U087BUC6ZFW/Minesweeper) 
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![Release](https://img.shields.io/github/v/release/JameDevOfficial/Minesweeper?label=Release&color=red&logo=lua&logoColor=white)](https://github.com/JameDevOfficial/Minesweeper/releases/latest)
[![Commits](https://img.shields.io/github/commit-activity/t/JameDevOfficial/Minesweeper?label=Commits&color=F28C28&logo=git&logoColor=white)](https://github.com/JameDevOfficial/Minesweeper/commits/main)

</div>

# Features
- Play a round of minesweeper
- Choose between easy, medium and hard
- Beat your personal highscores (they save in files!)
- Auto reveal when clicking on a tile with enough flags set
- Reveal connected 0 fields when clicking on one

Entirely written in C with custom print library (for printing with colors and styles)

# Screenshots
### The Menu
<img src="assets/menu.png" height="300px" alt="Start Screen"/> 

### The Game (Easy)
<img src="assets/game.png" height="300px" alt="Game Screen (Easy)"/>

### Game won (Easy)
<img src="assets/game_won.png" height="300px" alt="Game won Screen (Easy)"/> 

### Help Menu
<img src="assets/help.png" height="300px" alt="Help Menu"/> 

# Run
## Windows
Build the game using mingw32 and run the .exe file

```sh
    >cd src
    >gcc.exe main.c -o minesweeper.exe
    >./minesweeper.exe
``` 

## Linux
Build the game using a c compiler (downloaded trough a package manager)

```sh
    >cd src
    >gcc main.c -o minesweeper.out
    >./minesweeper.out
``` 

# Bugs
- last frame not rendering after game is won/lost

# License
This project is published under the [MIT LICENSE](LICENSE)

# Other
This project was made for hackclub siege week 10 (main week 6)