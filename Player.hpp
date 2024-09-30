#pragma once
#include <SFML/Graphics.hpp>  
#include <vector>
#include <string>
#include "Property.hpp"

class Player {
public:
    std::string name;
    int cash;
    int position;
    bool inJail;
    int jailTurns;
    sf::Color color; 
    std::vector<Property*> ownedProperties;

    Player(const std::string& playerName);

    void addCash(int amount);
    bool subtractCash(int amount);
    void move(int steps);
    bool canAfford(int amount) const;
    void buyProperty(Property* property);
    void buildHouse(Property* property);
    void buildHotel(Property* property);
    void goToJail();
    void getOutOfJail();
};
