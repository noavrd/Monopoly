#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "ChanceCard.hpp" 
#include <SFML/Graphics.hpp>
#include <vector>

class Game {
public:
    Game(int numPlayers);
    void takeTurn();
    void rollDice();
    void endTurn();
    bool isGameOver() const;
    void updateGraphics(sf::RenderWindow& window);

private:
    std::vector<Player> players;
    int currentPlayerIndex;
    Board board;
    int diceRollResult;
    bool isDoubleRoll;
    int consecutiveDoubles;
    std::vector<ChanceCard> chanceCards; 
};
