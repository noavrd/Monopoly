#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

Game::Game(int numPlayers) : currentPlayerIndex(0) {
    std::srand(std::time(0)); // Random seed for dice

    // Initialize players
    for (int i = 0; i < numPlayers; ++i) {
        players.emplace_back("Player " + std::to_string(i + 1));
    }

    // Initialize board
    board.initializeBoard();
}

void Game::takeTurn() {
    Player& currentPlayer = players[currentPlayerIndex];

    if (currentPlayer.inJail) {
        std::string message = currentPlayer.name + " is in jail.";
        board.setMessage(message);  // Update the message on the board
        currentPlayer.jailTurns--;

        if (currentPlayer.jailTurns == 0) {
            currentPlayer.getOutOfJail();
            board.setMessage(currentPlayer.name + " is out of jail.");
        }
    } else {
        rollDice();
        board.updatePlayerPosition(currentPlayer, currentPlayerIndex);  // Update the player position on the board

        // landing on a property and buying it need to fix not working for me
        Tile& landedTile = board.tiles[currentPlayer.position];
        // if (landedTile.type == TileType::PROPERTY && landedTile.price > 0 && landedTile.owner == nullptr) {
        //     if (currentPlayer.canAfford(landedTile.price)) {
        //         currentPlayer.buyProperty(static_cast<Property*>(&landedTile));
        //         std::string message = currentPlayer.name + " bought " + landedTile.name + " for $" + std::to_string(landedTile.price);
        //         board.setMessage(message);
        //     }
        // } else if (landedTile.owner != nullptr && landedTile.owner != &currentPlayer) {
        //     int rent = landedTile.calculateRent();
        //     if (currentPlayer.subtractCash(rent)) {
        //         landedTile.owner->addCash(rent);
        //         std::string message = currentPlayer.name + " paid $" + std::to_string(rent) + " rent to " + landedTile.owner->name;
        //         board.setMessage(message);
        //     }
        // }
    }
    endTurn();
}

void Game::rollDice() {
    int diceRoll = (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
    std::string message = players[currentPlayerIndex].name + " rolled a " + std::to_string(diceRoll);
    board.setMessage(message);  // Display the dice roll on the board
    players[currentPlayerIndex].move(diceRoll);
}

void Game::endTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

bool Game::isGameOver() const {
    int activePlayers = 0;
    for (const Player& player : players) {
        if (player.cash > 0) {
            // Game over if 1 player has more than 4000 cash
            if (player.cash > 4000) {
                // add message for winning
                // std::string message = players[player].name + " won!!!";
                // board.setMessage(message); 
                return true;
            }
            activePlayers++;
        }
    }
    // if (activePlayers <= 1) {
    //     std::string message = players[player].name + " won - everyone else bankrupt!!!";
    //     board.setMessage(message); 
    //     return true;
    // }
    return activePlayers <= 1;  // Game over when only 1 player has money - everyone else bankrupt
}

void Game::updateGraphics(sf::RenderWindow& window) {
    window.clear();
    board.draw(window);  // Draw the board and players
    window.display();
}
