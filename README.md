# Monopoly Game Simulation

This project is a Monopoly game simulation implemented in C++ using the SFML library for graphical rendering. The game follows the classic rules of Monopoly and supports 2 to 8 players. The game board is fully functional with properties, utilities, railroads, chance cards, taxes, and other Monopoly features.

## Features

- **Fully Interactive Board**: The game board is rendered using SFML, complete with properties, railroads, utilities, and special tiles like "Go to Jail" and "Free Parking."
- **Player Movement**: Players roll dice to move around the board, interact with tiles, and take actions such as buying properties, paying rent, or drawing Chance cards.
- **Property Management**: Players can buy properties, build houses and hotels, and collect rent from other players.
- **Jail System**: Players can be sent to jail for rolling three consecutive doubles or landing on the "Go to Jail" tile.
- **Chance Cards**: Chance cards provide random events that can affect player position, money, or other game mechanics.
- **Bankruptcy Handling**: Players can go bankrupt if they can't afford to pay rent or taxes. Their assets are transferred to the bank or other players.

## Code Overview

### `Game.cpp`
This file contains the main logic for the game, including player turns, dice rolling, and handling the different game events such as property purchases, rent payment, and landing on special tiles.

### `Board.cpp`
The `Board` class manages the game board, including initializing tiles and drawing the board and players on the screen.

### `Tile.cpp`
The `Tile` class represents individual tiles on the board, such as properties, utilities, and special tiles. It handles drawing the tiles, displaying the owner, and calculating rent.

### `Player.cpp`
The `Player` class manages each player's state, including their cash, properties, position on the board, and jail status. It also handles actions like buying properties, paying rent, and building houses/hotels.

### `ChanceCard.cpp`
This file handles the initialization and execution of Chance cards, which cause random events during the game.

### `SFML Graphics`
The game uses SFML (Simple and Fast Multimedia Library) for rendering the board, players, and other graphical elements.

## How to Run the Game (Ubuntu and macOS)

### Installation

1. **Install SFML**

   You need to have SFML installed to render the graphics of the game.

   - **Ubuntu**:
     ```bash
     sudo apt-get update
     sudo apt-get install libsfml-dev
     ```

   - **macOS**:
     ```bash
     brew install sfml
     ```

2. **Install Arial Font**

   The game uses the Arial font, which may not be installed by default on some systems. Follow the instructions below to install it:

   - **Ubuntu**:
     ```bash
     sudo apt-get install ttf-mscorefonts-installer
     ```

     After installation, the Arial font will be available at `/usr/share/fonts/truetype/msttcorefonts/Arial.ttf`.

   - **macOS**: The Arial font is pre-installed on macOS, so no additional installation is required.

3. **C++ Compiler**

   Ensure you have a C++ compiler installed that supports C++11 or later. Common options include GCC and Clang.

### Clone the Repository
   ```
  git clone https://github.com/noavrd/monopoly.git
  cd monopoly
  ```

### Build the Project
    ```
    make
    ```
    
### Run the Project
    ```bash
    ./monopoly
    ```
