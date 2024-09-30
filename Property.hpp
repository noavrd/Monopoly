#pragma once
#include <string>

class Player;  // Forward declaration

class Property {
public:
    std::string name;
    int price;
    int rent;
    int houseCost;
    int rentWithHouse;
    int rentWithHotel;
    Player* owner;
    int houses;
    bool hasHotel;

    Property(const std::string& propertyName, int propertyPrice, int propertyRent, int houseCost, int rentHouse, int rentHotel);

    int calculateRent() const;
};
