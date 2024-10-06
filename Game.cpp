#include "Game.hpp"
#include "Tile.hpp"  
#include "ChanceCard.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp> 

using namespace std; 

// Vector of player colors for the game
vector<sf::Color> playerColors = {
    sf::Color(218, 165, 32), 
    sf::Color(135, 206, 250),  
    sf::Color(144, 238, 144),  
    sf::Color(255, 228, 196),
    sf::Color(221, 160, 221),
    sf::Color(255, 255, 224),
    sf::Color(172, 238, 238),
    sf::Color(210, 180, 140)
};

/*
 * Game constructor
 * Initializes the game by setting up players, the board, and the chance cards.
 * @param numPlayers: The number of players in the game.
 */
Game::Game(int numPlayers) : currentPlayerIndex(0), diceRollResult(0), isDoubleRoll(false), consecutiveDoubles(0) {
    srand(time(0));  // Seed for random dice rolls

    // Initialize players and assign colors
    for (int i = 0; i < numPlayers; ++i) {
        Player player("Player " + to_string(i + 1));
        player.color = playerColors[i % playerColors.size()];  
        players.push_back(player);
    }

    // Initialize chance cards and the board
    chanceCards = initializeChanceCards();
    board.initializeBoard();
}

/*
 * Handles a player's turn in the game. Includes rolling dice, handling special tiles,
 * updating player position, and calling the appropriate handlers based on the landed tile.
 * @param window: The window where the game graphics are rendered.
 */
void Game::takeTurn(sf::RenderWindow& window) {
    Player& currentPlayer = players[currentPlayerIndex];

    // Print current player with the amount of money they have
    cout << "Current player: " << currentPlayer.name << " (Money: $" << currentPlayer.cash << ")" << endl;

    // Jail logic
    if (currentPlayer.inJail) {
        cout << currentPlayer.name << " is in jail." << endl;

        // Roll dice to try and get doubles to leave jail
        int die1 = rand() % 6 + 1;
        int die2 = rand() % 6 + 1;
        cout << "Rolling to try to get out of jail: " << die1 << " and " << die2 << endl;

        if (die1 == die2) {
            currentPlayer.inJail = false;
            currentPlayer.jailTurns = 0;
            cout << currentPlayer.name << " rolled doubles and is out of jail!" << endl;
        } else {
            currentPlayer.decrementJailTurn();
            if (currentPlayer.inJail) {
                cout << currentPlayer.name << " stays in jail for another turn." << endl;
                updateGraphics(window);
                endTurn(window);
                return;
            } else {
                cout << currentPlayer.name << " has completed their time in jail and is now out!" << endl;
            }
        }
    }

    // Roll dice and move player
    rollDice();
    board.updatePlayerPosition(currentPlayer, currentPlayerIndex);

    // Update graphics after rolling dice and moving player
    updateGraphics(window);

    // Get the tile the player landed on and handle accordingly
    Tile& landedTile = board.tiles[currentPlayer.position];

    // Property, Railroad, or Utility handling
    if (landedTile.type == TileType::PROPERTY || landedTile.type == TileType::RAILROAD || landedTile.type == TileType::UTILITY) {
        handlePropertyLanding(currentPlayer, landedTile, window);  // Call handlePropertyLanding with window for graphics update
    } 
    // Tax handling
    else if (landedTile.type == TileType::TAX) {
        // Handle tax payment
        if (currentPlayer.canAfford(landedTile.price)) {
            currentPlayer.subtractCash(landedTile.price);
            cout << currentPlayer.name << " paid $" << landedTile.price << " in taxes." << endl;
        } else {
            handleBankruptcy(currentPlayer, nullptr, window);  // Bankrupt due to taxes (to the bank)
            return;  // End turn after handling bankruptcy
        }
    } 
    // Go to Jail handling
    else if (landedTile.type == TileType::GO_TO_JAIL) {
        currentPlayer.goToJail();
        board.updatePlayerPosition(currentPlayer, currentPlayerIndex);
        cout << currentPlayer.name << " has been sent to jail!" << endl;
    } 
    // Free Parking handling
    else if (landedTile.type == TileType::FREE_PARKING) {
        cout << currentPlayer.name << " is resting at Free Parking." << endl;
    } 
    // Chance handling
    else if (landedTile.type == TileType::CHANCE) {
        handleChanceCard(currentPlayer);
    } 
    // Go tile handling
    else if (landedTile.type == TileType::GO) {
        cout << currentPlayer.name << " landed on GO! Collect $200." << endl;
        currentPlayer.addCash(200);
    }

    updateGraphics(window);  // Update the graphics after handling the tile action
    endTurn(window);  // Pass window to endTurn for graphical updates
}

/*
 * Handles the scenario when a player goes bankrupt. 
 * Transfers all assets to the creditor or to the bank depending on the cause of bankruptcy.
 * @param bankruptPlayer: The player who is bankrupt.
 * @param creditor: The player who the bankrupt player owes money to, or nullptr if the bank is the creditor.
 * @param window: The window where the game graphics are rendered.
 */
void Game::handleBankruptcy(Player& bankruptPlayer, Player* creditor, sf::RenderWindow& window) {
    cout << bankruptPlayer.name << " is bankrupt!" << endl;

    // Transfer assets to the creditor or bank
    if (creditor) {
        cout << "All assets are transferred to " << creditor->name << endl;
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
        cout << "All properties are returned to the bank." << endl;
        bankruptPlayer.cash = 0;

        // Release all properties to no owner
        for (Tile* property : bankruptPlayer.ownedTiles) {
            property->owner = nullptr;
        }
        bankruptPlayer.ownedTiles.clear();
    }

    // Remove bankrupt player from the game
    auto it = find(players.begin(), players.end(), bankruptPlayer);
    if (it != players.end()) {
        players.erase(it);
    }

    cout << bankruptPlayer.name << " is removed from the game." << endl;

    if (isGameOver()) {
        cout << "The game is over!" << endl;
    }

    // Update graphics after handling bankruptcy
    updateGraphics(window);
}


/*
 * Handles the logic when a player lands on a property, railroad, or utility.
 * The player can choose to buy the property, build houses/hotels, or pay rent if owned by another player.
 * @param currentPlayer: The player who landed on the tile.
 * @param landedTile: The tile the player landed on.
 * @param window: The window where the game graphics are rendered.
 */
void Game::handlePropertyLanding(Player& currentPlayer, Tile& landedTile, sf::RenderWindow& window) {
    if (landedTile.owner == nullptr) {
        // Check if player can afford the property
        if (currentPlayer.canAfford(landedTile.price)) {
            cout << currentPlayer.name << " landed on " << landedTile.name << ". Would you like to buy it for $"
                 << landedTile.price << "? Press 'y' to buy or 'n' to decline." << endl;

            bool decisionMade = false;
            while (!decisionMade) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                    // Use buyProperty to handle the purchase
                    currentPlayer.buyProperty(&landedTile);
                    updateGraphics(window);  // Update the graphics after the purchase
                    decisionMade = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                    cout << currentPlayer.name << " decided not to buy " << landedTile.name << endl;
                    decisionMade = true;
                }
            }
        } else {
            // Inform the player they can't afford the property
            cout << currentPlayer.name << " landed on " << landedTile.name << " but cannot afford it. The property costs $"
                 << landedTile.price << ", but " << currentPlayer.name << " only has $" << currentPlayer.cash << "." << endl;
        }
    } else if (landedTile.owner == &currentPlayer && landedTile.type == TileType::PROPERTY) {
        // If the player owns the property, allow them to build houses/hotels
        cout << currentPlayer.name << " landed on their own property: " << landedTile.name
             << ". Would you like to build a house or a hotel? Press 'h' for house, 't' for hotel, or 'n' to do nothing." << endl;

        bool decisionMade = false;
        while (!decisionMade) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                currentPlayer.buildHouse(&landedTile, board);  // Build house
                updateGraphics(window);  // Update the graphics after building a house
                decisionMade = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                currentPlayer.buildHotel(&landedTile, board);  // Build hotel
                updateGraphics(window);  // Update the graphics after building a hotel
                decisionMade = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                cout << currentPlayer.name << " decided not to build anything on " << landedTile.name << endl;
                decisionMade = true;
            }
        }
    } else if (landedTile.owner != &currentPlayer) {
        // Tile is owned by another player, pay rent
        int rent = (landedTile.type == TileType::UTILITY) ? 10 * diceRollResult : landedTile.calculateRent(diceRollResult);

        if (currentPlayer.canAfford(rent)) {
            currentPlayer.subtractCash(rent);
            landedTile.owner->addCash(rent);
            cout << currentPlayer.name << " paid $" << rent << " in rent to " << landedTile.owner->name << endl;
        } else {
            cout << currentPlayer.name << " cannot afford rent and is bankrupt!" << endl;
            handleBankruptcy(currentPlayer, landedTile.owner, window);
        }
    }

    // Ensure graphics update after all actions on property
    updateGraphics(window);
}

/*
 * Rolls two dice for the current player's turn.
 * Handles movement, checking for doubles, and passing GO to collect $200.
 */
void Game::rollDice() {
    // Roll two dice
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    diceRollResult = die1 + die2;

    // Print the dice roll result
    cout << players[currentPlayerIndex].name << " rolled " << die1 << " and " << die2 << " (" << diceRollResult << ")" << endl;

    // Check for doubles
    if (die1 == die2) {
        isDoubleRoll = true;
        consecutiveDoubles++;
        if (consecutiveDoubles == 3) {
            players[currentPlayerIndex].goToJail();
            board.updatePlayerPosition(players[currentPlayerIndex], currentPlayerIndex);
            cout << players[currentPlayerIndex].name << " rolled doubles three times and is sent to Jail!" << endl;
        }
    } else {
        isDoubleRoll = false;
        consecutiveDoubles = 0;
    }

    players[currentPlayerIndex].move(diceRollResult);

    // Handle passing GO and collecting $200
    if (players[currentPlayerIndex].position < diceRollResult) {
        players[currentPlayerIndex].addCash(200);
        cout << players[currentPlayerIndex].name << " passed GO! Collect $200" << endl;
    }
}

/*
 * Handles the logic for drawing a chance card and applying its effect.
 * @param currentPlayer: The player who drew the chance card.
 */
void Game::handleChanceCard(Player& currentPlayer) {
    // Pick a random chance card
    int cardIndex = rand() % chanceCards.size();
    ChanceCard& card = chanceCards[cardIndex];

    cout << "Chance Card: " << card.description << endl;
    // Apply the card's effect
    card.applyEffect(currentPlayer, players, currentPlayerIndex);
}


/*
 * Ends the current player's turn and moves to the next player.
 * If doubles were rolled, the current player takes another turn.
 * @param window: The window where the game graphics are rendered.
 */
void Game::endTurn(sf::RenderWindow& window) {
    if (!isDoubleRoll) {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();  // Move to the next player
    } else {
        cout << players[currentPlayerIndex].name << " rolled doubles! Take another turn." << endl;
    }
    isDoubleRoll = false;
    consecutiveDoubles = 0;

    // Ensure graphics update after ending the turn
    updateGraphics(window);
}

/*
 * Checks if the game is over by counting the number of players still in the game.
 * @return True if the game is over, false otherwise.
 */
bool Game::isGameOver() const {
    int activePlayers = 0;
    for (const Player& player : players) {
        if (player.cash > 0) {
            activePlayers++;
        }
    }
    return activePlayers <= 1;
}

/*
 * Updates the graphics of the game by clearing the window and redrawing the board and players.
 * @param window: The window where the game graphics are rendered.
 */
void Game::updateGraphics(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    board.draw(window, players);
    window.display();
}
