#include "Game.hpp"
#include "Tile.hpp"  
#include "ChanceCard.hpp"
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

    chanceCards = initializeChanceCards();

    // Initialize board
    board.initializeBoard();
}

void Game::takeTurn() {
    Player& currentPlayer = players[currentPlayerIndex];

    std::cout << "Current player: " << currentPlayer.name << " (Money: $" << currentPlayer.cash << ")" << std::endl;
    // Jail logic
    if (currentPlayer.inJail) {
        std::cout << currentPlayer.name << " is in jail." << std::endl;

        // Roll dice to try and get doubles to leave jail
        int die1 = std::rand() % 6 + 1;
        int die2 = std::rand() % 6 + 1;
        std::cout << "Rolling to try to get out of jail: " << die1 << " and " << die2 << std::endl;

        if (die1 == die2) {
            currentPlayer.inJail = false;
            currentPlayer.jailTurns = 0;
            std::cout << currentPlayer.name << " rolled doubles and is out of jail!" << std::endl;
        } else {
            currentPlayer.decrementJailTurn();
            if (currentPlayer.inJail) {
                std::cout << currentPlayer.name << " stays in jail for another turn." << std::endl;
                std::cout << std::endl;  // Empty line after player's turn
                endTurn();
                return;
            } else {
                std::cout << currentPlayer.name << " has completed their time in jail and is now out!" << std::endl;
            }
        }
    }

    // Roll dice and move player
    rollDice();
    board.updatePlayerPosition(currentPlayer, currentPlayerIndex);

    Tile& landedTile = board.tiles[currentPlayer.position];

    // Property, Railroad, or Utility handling
    if (landedTile.type == TileType::PROPERTY || landedTile.type == TileType::RAILROAD || landedTile.type == TileType::UTILITY) {
        if (landedTile.owner == nullptr) {
            // Tile is available for purchase
            std::cout << currentPlayer.name << " landed on " << landedTile.name << ". Would you like to buy it for $"
                      << landedTile.price << "? Press 'y' to buy or 'n' to decline." << std::endl;

            bool decisionMade = false;
            while (!decisionMade) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                    currentPlayer.subtractCash(landedTile.price);
                    landedTile.owner = &currentPlayer;
                    currentPlayer.ownedTiles.push_back(&landedTile);
                    std::cout << currentPlayer.name << " bought " << landedTile.name << " for $" << landedTile.price << std::endl;
                    decisionMade = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                    std::cout << currentPlayer.name << " decided not to buy " << landedTile.name << std::endl;
                    decisionMade = true;
                }
            }
        } else if (landedTile.owner != &currentPlayer) {
            // Tile is owned by another player
            int rent = landedTile.calculateRent();
            if (currentPlayer.canAfford(rent)) {
                currentPlayer.subtractCash(rent);
                landedTile.owner->addCash(rent);
                std::cout << currentPlayer.name << " paid $" << rent << " in rent to " << landedTile.owner->name << std::endl;
            } else {
                // Handle bankruptcy due to inability to pay rent
                handleBankruptcy(currentPlayer, landedTile.owner);  // Pass the owner pointer directly
                return;  // End turn after handling bankruptcy
            }
        }
    } 
    // Tax handling
    else if (landedTile.type == TileType::TAX) {
        if (currentPlayer.canAfford(landedTile.price)) {
            currentPlayer.subtractCash(landedTile.price);
            std::cout << currentPlayer.name << " paid $" << landedTile.price << " in taxes." << std::endl;
        } else {
            // Handle bankruptcy due to inability to pay taxes
            handleBankruptcy(currentPlayer, nullptr);  // Bankrupt due to taxes (to the bank)
            return;  // End turn after handling bankruptcy
        }
    } 
    // Go to Jail handling
    else if (landedTile.type == TileType::GO_TO_JAIL) {
        currentPlayer.goToJail();
        board.updatePlayerPosition(currentPlayer, currentPlayerIndex);
        std::cout << currentPlayer.name << " has been sent to jail!" << std::endl;
    } 
    // Free Parking handling
    else if (landedTile.type == TileType::FREE_PARKING) {
        std::cout << currentPlayer.name << " is resting at Free Parking." << std::endl;
    } 
    // Chance handling
    else if (landedTile.type == TileType::CHANCE) {
        // Pick a random chance card
        int cardIndex = std::rand() % chanceCards.size();
        ChanceCard& card = chanceCards[cardIndex];

        std::cout << "Chance Card: " << card.description << std::endl;
        // Apply the card's effect
        card.applyEffect(currentPlayer, players, currentPlayerIndex);
    } 
    // Go tile handling
    else if (landedTile.type == TileType::GO) {
        std::cout << currentPlayer.name << " landed on GO! Collect $200." << std::endl;
        currentPlayer.addCash(200);
    }

    std::cout << std::endl;
    endTurn();
}

void Game::handleBankruptcy(Player& bankruptPlayer, Player* creditor) {
    std::cout << bankruptPlayer.name << " is bankrupt!" << std::endl;

    if (creditor) {
        std::cout << "All assets are transferred to " << creditor->name << std::endl;
        creditor->cash += bankruptPlayer.cash;
        bankruptPlayer.cash = 0;

        // Transfer properties
        for (Tile* property : bankruptPlayer.ownedTiles) {
            property->owner = creditor;
            creditor->ownedTiles.push_back(property);
        }
        bankruptPlayer.ownedTiles.clear();

    } else {
        // Bankruptcy to the bank
        std::cout << "All properties are returned to the bank." << std::endl;
        bankruptPlayer.cash = 0;

        // Release all properties to no owner
        for (Tile* property : bankruptPlayer.ownedTiles) {
            property->owner = nullptr;
        }
        bankruptPlayer.ownedTiles.clear();
    }

    // Remove bankrupt player from the game
    auto it = std::find(players.begin(), players.end(), bankruptPlayer);
    if (it != players.end()) {
        players.erase(it);
    }

    std::cout << bankruptPlayer.name << " is removed from the game." << std::endl;

    if (isGameOver()) {
        std::cout << "The game is over!" << std::endl;
    }
}

void Game::rollDice() {
    // Roll two dice
    int die1 = std::rand() % 6 + 1;
    int die2 = std::rand() % 6 + 1;
    diceRollResult = die1 + die2;

    // Print the dice roll result
    std::cout << players[currentPlayerIndex].name << " rolled " << die1 << " and " << die2 << " (" << diceRollResult << ")" << std::endl;

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

void Game::handlePropertyLanding(Player& currentPlayer, Tile& landedTile) {
    if (landedTile.owner == nullptr) {
        std::cout << currentPlayer.name << " landed on " << landedTile.name << ". Would you like to buy it for $"
                  << landedTile.price << "? Press 'y' to buy or 'n' to decline." << std::endl;

        bool decisionMade = false;
        while (!decisionMade) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                currentPlayer.buyProperty(&landedTile);
                decisionMade = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                std::cout << currentPlayer.name << " decided not to buy " << landedTile.name << std::endl;
                decisionMade = true;
            }
        }
    } else if (landedTile.owner == &currentPlayer) {
        std::cout << currentPlayer.name << " landed on their own property: " << landedTile.name
                  << ". Would you like to build a house or a hotel? Press 'h' for house, 't' for hotel, or 'n' to do nothing." << std::endl;

        bool decisionMade = false;
        while (!decisionMade) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                currentPlayer.buildHouse(&landedTile, board);  // Pass the board to buildHouse
                decisionMade = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                currentPlayer.buildHotel(&landedTile, board);  // Pass the board to buildHotel
                decisionMade = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                std::cout << currentPlayer.name << " decided not to build anything on " << landedTile.name << std::endl;
                decisionMade = true;
            }
        }
    } else {
        int rent = landedTile.calculateRent();
        if (currentPlayer.canAfford(rent)) {
            currentPlayer.subtractCash(rent);
            landedTile.owner->addCash(rent);
            std::cout << currentPlayer.name << " paid $" << rent << " in rent to " << landedTile.owner->name << std::endl;
        } else {
            std::cout << currentPlayer.name << " cannot afford rent and is bankrupt!" << std::endl;
        }
    }
}


void Game::handleChanceCard(Player& currentPlayer) {
    // Pick a random chance card
    int cardIndex = std::rand() % chanceCards.size();
    ChanceCard& card = chanceCards[cardIndex];

    std::cout << "Chance Card: " << card.description << std::endl;
    // Apply the card's effect
    card.applyEffect(currentPlayer, players, currentPlayerIndex);
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