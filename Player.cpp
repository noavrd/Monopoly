#include "Player.hpp"
#include <iostream>

Player::Player(const std::string& playerName)
    : name(playerName), cash(1500), position(0), inJail(false), jailTurns(0), color(sf::Color::White) {}

void Player::addCash(int amount) {
    cash += amount;
    std::cout << name << " received $" << amount << ". Total cash: $" << cash << std::endl;
}

bool Player::subtractCash(int amount) {
    if (canAfford(amount)) {
        cash -= amount;
        std::cout << name << " paid $" << amount << ". Remaining cash: $" << cash << std::endl;
        return true;
    } else {
        std::cout << name << " cannot afford to pay $" << amount << " and is bankrupt!" << std::endl;
        return false;
    }
}

void Player::move(int steps) {
    position = (position + steps) % 40;  // Circular board logic
}

bool Player::canAfford(int amount) const {
    return cash >= amount;
}

void Player::buyProperty(Property* property) {
    if (canAfford(property->price)) {
        subtractCash(property->price);
        ownedProperties.push_back(property);
        property->owner = this;
        std::cout << name << " bought " << property->name << " for $" << property->price << std::endl;
    } else {
        std::cout << name << " cannot afford to buy " << property->name << std::endl;
    }
}

void Player::buildHouse(Property* property) {
    if (property->owner == this && property->houses < 4 && !property->hasHotel && canAfford(property->houseCost)) {
        subtractCash(property->houseCost);
        property->houses++;
        std::cout << name << " built a house on " << property->name << ". Total houses: " << property->houses << std::endl;
    } else {
        if (property->houses >= 4) {
            std::cout << name << " cannot build more houses on " << property->name << " (max 4)." << std::endl;
        } else if (property->hasHotel) {
            std::cout << name << " cannot build houses on " << property->name << " because it already has a hotel." << std::endl;
        } else {
            std::cout << name << " does not own " << property->name << " or cannot afford to build a house." << std::endl;
        }
    }
}

void Player::buildHotel(Property* property) {
    if (property->owner == this && property->houses == 4 && !property->hasHotel && canAfford(property->houseCost)) {
        subtractCash(property->houseCost);  //  hotel cost is the same as a house cost, maybe change it.
        property->houses = 0;  // Reset house count
        property->hasHotel = true;
        std::cout << name << " built a hotel on " << property->name << "!" << std::endl;
    } else {
        if (property->houses < 4) {
            std::cout << name << " needs 4 houses on " << property->name << " before building a hotel." << std::endl;
        } else if (property->hasHotel) {
            std::cout << name << " cannot build more hotels on " << property->name << "." << std::endl;
        } else {
            std::cout << name << " does not own " << property->name << " or cannot afford to build a hotel." << std::endl;
        }
    }
}

void Player::goToJail() {
    inJail = true;
    jailTurns = 3;
    position = 10;  // position 10 is the Jail tile - maybe change
}

void Player::getOutOfJail() {
    inJail = false;
    jailTurns = 0;
    std::cout << name << " has been released from jail!" << std::endl;
}
