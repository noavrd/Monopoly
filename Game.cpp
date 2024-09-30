#include "Game.hpp"
#include "Tile.hpp"  
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp> 


std::vector<sf::Color> playerColors = {
    sf::Color::Red, sf::Color::Green, sf::Color::Blue,
    sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan,
    sf::Color::White, sf::Color::Black
};

Game::Game(int numPlayers) : currentPlayerIndex(0), diceRollResult(0), isDoubleRoll(false), consecutiveDoubles(0) {
    std::srand(std::time(0));  // Seed for random dice rolls

    // Initialize players and assign colors
    for (int i = 0; i < numPlayers; ++i) {
        Player player("Player " + std::to_string(i + 1));
        player.color = playerColors[i % playerColors.size()];  
        players.push_back(player);
    }

    // Initialize board
    board.initializeBoard();
}

void Game::takeTurn() {
    Player& currentPlayer = players[currentPlayerIndex];

     std::cout << "Current player: " << currentPlayer.name << std::endl;

    if (currentPlayer.inJail) {
        std::cout << currentPlayer.name << " is in jail." << std::endl;

        currentPlayer.jailTurns--;

        if (currentPlayer.jailTurns == 0 || (std::rand() % 6 + 1 == std::rand() % 6 + 1)) {
            currentPlayer.inJail = false;
            std::cout << currentPlayer.name << " is out of jail!" << std::endl;
        } else {
            std::cout << currentPlayer.name << " stays in jail for another turn." << std::endl;
            std::cout << std::endl;  // Empty line after player's turn
            endTurn();
            return;
        }
    }

    rollDice();
    board.updatePlayerPosition(currentPlayer, currentPlayerIndex);

    Tile& landedTile = board.tiles[currentPlayer.position];

    if (landedTile.type == TileType::PROPERTY || landedTile.type == TileType::RAILROAD || landedTile.type == TileType::UTILITY) {
        if (landedTile.owner == nullptr) {
            std::cout << currentPlayer.name << " landed on " << landedTile.name << ". Would you like to buy it for $" 
                      << landedTile.price << "? Press 'y' to buy or 'n' to decline." << std::endl;

            bool decisionMade = false;
            while (!decisionMade) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                    currentPlayer.subtractCash(landedTile.price);
                    landedTile.owner = &currentPlayer;
                    std::cout << currentPlayer.name << " bought " << landedTile.name << " for $" << landedTile.price << std::endl;
                    decisionMade = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                    std::cout << currentPlayer.name << " decided not to buy " << landedTile.name << std::endl;
                    decisionMade = true;
                }
            }
        } else if (landedTile.owner != &currentPlayer) {
            int rent = landedTile.calculateRent();
            if (currentPlayer.canAfford(rent)) {
                currentPlayer.subtractCash(rent);
                landedTile.owner->addCash(rent);
                std::cout << currentPlayer.name << " paid $" << rent << " in rent to " << landedTile.owner->name << std::endl;
            } else {
                std::cout << currentPlayer.name << " cannot afford rent and is bankrupt!" << std::endl;
            }
        }
    } else if (landedTile.type == TileType::TAX) {
        currentPlayer.subtractCash(landedTile.price);
        std::cout << currentPlayer.name << " paid $" << landedTile.price << " in taxes." << std::endl;
    } else if (landedTile.type == TileType::GO_TO_JAIL) {
        currentPlayer.goToJail();
        board.updatePlayerPosition(currentPlayer, currentPlayerIndex);
        std::cout << currentPlayer.name << " has been sent to jail!" << std::endl;
    } else if (landedTile.type == TileType::FREE_PARKING) {
        std::cout << currentPlayer.name << " is resting at Free Parking." << std::endl;
    } else if (landedTile.type == TileType::GO) {
        std::cout << currentPlayer.name << " landed on GO! Collect $200." << std::endl;
        currentPlayer.addCash(200);
    }

    std::cout << std::endl;  
    endTurn();
}


void Game::rollDice() {
    // Roll two dice
    int die1 = std::rand() % 6 + 1;
    int die2 = std::rand() % 6 + 1;
    diceRollResult = die1 + die2;

    // Print the dice roll result
    std::cout << "Player " << players[currentPlayerIndex].name << " rolled " << die1 << " and " << die2 << " (" << diceRollResult << ")" << std::endl;

    // Check for doubles
    if (die1 == die2) {
        isDoubleRoll = true;
        consecutiveDoubles++;
        if (consecutiveDoubles == 3) {
            players[currentPlayerIndex].goToJail();
            board.updatePlayerPosition(players[currentPlayerIndex], currentPlayerIndex);
            std::cout << players[currentPlayerIndex].name << " rolled doubles three times and is sent to Jail!" << std::endl;
            endTurn();
            return;
        }
    } else {
        isDoubleRoll = false;
        consecutiveDoubles = 0;
    }

    players[currentPlayerIndex].move(diceRollResult);

    // Handle passing GO and collecting $200
    if (players[currentPlayerIndex].position < diceRollResult) {
        players[currentPlayerIndex].addCash(200);
        std::cout << players[currentPlayerIndex].name << " passed GO! Collect $200" << std::endl;
    }
}

void Game::endTurn() {
    if (!isDoubleRoll) {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();  // Move to the next player
    } else {
         std::cout << players[currentPlayerIndex].name << " rolled doubles! Take another turn." << std::endl;

    }
    isDoubleRoll = false;
    consecutiveDoubles = 0;
}

bool Game::isGameOver() const {
    int activePlayers = 0;
    for (const Player& player : players) {
        if (player.cash > 0) {
            activePlayers++;
        }
    }
    return activePlayers <= 1;
}

void Game::updateGraphics(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    board.draw(window, players);
    window.display();
}