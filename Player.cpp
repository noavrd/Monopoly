#include "Player.hpp"
#include <iostream>

Player::Player(const std::string& playerName) : name(playerName), cash(1500), position(0), inJail(false), jailTurns(0) {}

void Player::addCash(int amount) {
    cash += amount;
}

bool Player::subtractCash(int amount) {
    if (cash >= amount) {
        cash -= amount;
        return true;
    } else {
        std::cout << name << " is bankrupt!" << std::endl;
        return false;
    }
}

void Player::move(int steps) {
    position = (position + steps) % 40;
}

bool Player::canAfford(int amount) {
    return cash >= amount;
}

void Player::buyProperty(Property* property) {
    if (canAfford(property->price)) {
        subtractCash(property->price);
        ownedProperties.push_back(property);
        property->owner = this;
        std::cout << name << " bought " << property->name << std::endl;
    }
}

void Player::buildHouse(Property* property) {
    if (canAfford(property->houseCost) && property->owner == this && property->houses < 4) {
        subtractCash(property->houseCost);
        property->houses++;
        std::cout << name << " built a house on " << property->name << std::endl;
    }
}

void Player::goToJail() {
    inJail = true;
    jailTurns = 3;
    position = 10; // Jail position
    std::cout << name << " is in jail!" << std::endl;
}

void Player::getOutOfJail() {
    inJail = false;
    jailTurns = 0;
    std::cout << name << " is out of jail!" << std::endl;
}
