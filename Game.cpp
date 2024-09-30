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

    std::cout << "Current player: " << currentPlayer.name << ", Position: " << currentPlayer.position << std::endl;

    if (currentPlayer.inJail) {
        std::ostringstream jailMessage;
        jailMessage << currentPlayer.name << " is in jail.";
        board.setMessage(jailMessage.str());
        
        currentPlayer.jailTurns--;

        if (currentPlayer.jailTurns == 0 || (std::rand() % 6 + 1 == std::rand() % 6 + 1)) {
            currentPlayer.inJail = false;
            std::ostringstream outOfJailMessage;
            outOfJailMessage << currentPlayer.name << " is out of jail!";
            board.setMessage(outOfJailMessage.str());
        } else {
            std::ostringstream stayInJailMessage;
            stayInJailMessage << currentPlayer.name << " stays in jail for another turn.";
            board.setMessage(stayInJailMessage.str());
            endTurn();  // Move to the next player
            return;
        }
    }

    rollDice();  // Roll the dice and move the current player
    board.updatePlayerPosition(currentPlayer, currentPlayerIndex);  // Update the player's position on the board

    // Ensure position is within bounds
    if (currentPlayer.position >= board.tiles.size()) {
        std::cerr << "Error: Player position out of bounds!" << std::endl;
        return;
    }

    // Handle the action for the tile the player landed on
    Tile& landedTile = board.tiles[currentPlayer.position];

    std::ostringstream actionMessage;

    if (landedTile.type == TileType::PROPERTY || landedTile.type == TileType::RAILROAD || landedTile.type == TileType::UTILITY) {
        if (landedTile.owner == nullptr) {
            if (currentPlayer.canAfford(landedTile.price)) {
                currentPlayer.subtractCash(landedTile.price);
                landedTile.owner = &currentPlayer;
                actionMessage << currentPlayer.name << " bought " << landedTile.name << " for $" << landedTile.price;
                board.setMessage(actionMessage.str());
            } else {
                actionMessage << currentPlayer.name << " cannot afford " << landedTile.name;
                board.setMessage(actionMessage.str());
            }
        } else if (landedTile.owner != &currentPlayer) {
            if (landedTile.owner) {
                int rent = landedTile.calculateRent();
                if (currentPlayer.canAfford(rent)) {
                    currentPlayer.subtractCash(rent);
                    landedTile.owner->addCash(rent);
                    actionMessage << currentPlayer.name << " paid $" << rent << " in rent to " << landedTile.owner->name;
                    board.setMessage(actionMessage.str());
                } else {
                    actionMessage << currentPlayer.name << " cannot afford rent and is bankrupt!";
                    board.setMessage(actionMessage.str());
                    // add bankruptcy logic
                }
            } else {
                std::cerr << "Error: landedTile.owner is nullptr" << std::endl;
            }
        }
    } else if (landedTile.type == TileType::TAX) {
        currentPlayer.subtractCash(landedTile.price);
        actionMessage << currentPlayer.name << " paid $" << landedTile.price << " in taxes";
        board.setMessage(actionMessage.str());
    } else if (landedTile.type == TileType::GO_TO_JAIL) {
        currentPlayer.goToJail();
        board.updatePlayerPosition(currentPlayer, currentPlayerIndex);
        board.setMessage(currentPlayer.name + " is sent to jail!");
    } else if (landedTile.type == TileType::FREE_PARKING) {
        board.setMessage(currentPlayer.name + " is resting at Free Parking");
    } else if (landedTile.type == TileType::GO) {
        board.setMessage(currentPlayer.name + " landed on GO! Collect $200");
        currentPlayer.addCash(200);
    }

    endTurn();  // End the current player's turn
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
            board.setMessage(players[currentPlayerIndex].name + " rolled doubles three times and is sent to Jail!");
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
        board.setMessage(players[currentPlayerIndex].name + " passed GO! Collect $200");
    }
}

void Game::endTurn() {
    if (!isDoubleRoll) {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();  // Move to the next player
    } else {
        board.setMessage(players[currentPlayerIndex].name + " rolled doubles! Take another turn.");
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
