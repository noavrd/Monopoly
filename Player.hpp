#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Tile.hpp"

class Board; 

class Player {
public:
    std::string name;
    int cash;
    int position;
    bool inJail;
    int jailTurns;
    sf::Color color;
    std::vector<Tile*> ownedTiles;

    Player(const std::string& playerName);

    void addCash(int amount);
    bool subtractCash(int amount);
    void move(int steps);
    bool canAfford(int amount) const;
    void buyProperty(Tile* property);
    void buildHouse(Tile* property, Board& board);  // Updated to accept Board as a parameter
    void buildHotel(Tile* property, Board& board);  // Updated to accept Board as a parameter
    void goToJail();
    void getOutOfJail();
    int getNumberOfTrains() const;
};
