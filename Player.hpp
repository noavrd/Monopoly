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
    bool hasGetOutOfJailCard;  
    sf::Color color;
    std::vector<Tile*> ownedTiles;

    // Constructor
    Player(const std::string& playerName);

    void addCash(int amount);
    bool subtractCash(int amount);
    bool canAfford(int amount) const;
    void move(int steps);
    void buyProperty(Tile* property);
    void buildHouse(Tile* property, Board& board);  
    void buildHotel(Tile* property, Board& board);  
    void goToJail();          
    void tryExitJail();        
    void decrementJailTurn();  
    int getNumberOfTrains() const; 

    bool operator==(const Player& other) const {
        return name == other.name;
    }

private:
    bool ownsAllInColorGroup(const std::vector<Tile*>& colorGroupTiles) const;
    bool isEvenHouseDistribution(const std::vector<Tile*>& colorGroupTiles, Tile* targetProperty) const;
};
