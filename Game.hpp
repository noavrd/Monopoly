#pragma once
#include <vector>
#include "Player.hpp"
#include "Tile.hpp"
#include "Board.hpp"

class Game {
public:
    std::vector<Player> players;
    Board board;
    int currentPlayerIndex;

    Game(int numPlayers);
    void takeTurn();
    void rollDice();
    void endTurn();
    bool isGameOver() const;
    void updateGraphics(sf::RenderWindow& window);
};
