#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "ChanceCard.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Game {
public:
    Game(int numPlayers);
    void takeTurn();
    void rollDice();
    void endTurn();
    bool isGameOver() const;
    void updateGraphics(sf::RenderWindow& window);
    void handleBankruptcy(Player& bankruptPlayer, Player* creditor);
    void handlePropertyLanding(Player& currentPlayer, Tile& landedTile);
    void handleChanceCard(Player& currentPlayer);

private:
    std::vector<Player> players;
    int currentPlayerIndex;
    Board board;
    int diceRollResult;
    bool isDoubleRoll;
    int consecutiveDoubles;
    std::vector<ChanceCard> chanceCards; 
};
