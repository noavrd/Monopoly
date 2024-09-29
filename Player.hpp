#pragma once
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
    std::vector<Property*> ownedProperties;

    Player(const std::string& playerName);
    void addCash(int amount);
    bool subtractCash(int amount);
    void move(int steps);
    bool canAfford(int amount);
    void buyProperty(Property* property);
    void buildHouse(Property* property);
    void goToJail();
    void getOutOfJail();
};
