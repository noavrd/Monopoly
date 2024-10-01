#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

Player::Player(const std::string& playerName)
    : name(playerName), cash(1500), position(0), inJail(false), jailTurns(0), hasGetOutOfJailCard(false), color(sf::Color::White) {}

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

void Player::buyProperty(Tile* property) {
    if (canAfford(property->price)) {
        subtractCash(property->price);
        ownedTiles.push_back(property);
        property->owner = this;
        std::cout << name << " bought " << property->name << " for $" << property->price << std::endl;
    } else {
        std::cout << name << " cannot afford to buy " << property->name << std::endl;
    }
}

void Player::buildHouse(Tile* property, Board& board) {
    // Ensure the player owns all properties in the color group
    std::vector<Tile*> colorGroupTiles = board.getTilesInColorGroup(property);
    bool ownsAllInColorGroup = true;

    for (Tile* tile : colorGroupTiles) {
        if (tile->owner != this) {
            ownsAllInColorGroup = false;
            break;
        }
    }

    if (!ownsAllInColorGroup) {
        std::cout << name << " cannot build a house on " << property->name << " because they do not own all properties in the color group." << std::endl;
        return;
    }

    // Ensure even distribution of houses
    for (Tile* tile : colorGroupTiles) {
        if (tile->houses < property->houses) {
            std::cout << name << " must build evenly across all properties in the color group." << std::endl;
            return;
        }
    }

    if (property->houses < 4 && !property->hasHotel && canAfford(property->houseCost)) {
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

void Player::buildHotel(Tile* property, Board& board) {
    // Ensure the player owns all properties in the color group
    std::vector<Tile*> colorGroupTiles = board.getTilesInColorGroup(property);
    bool ownsAllInColorGroup = true;

    for (Tile* tile : colorGroupTiles) {
        if (tile->owner != this) {
            ownsAllInColorGroup = false;
            break;
        }
    }

    if (!ownsAllInColorGroup) {
        std::cout << name << " cannot build a hotel on " << property->name << " because they do not own all properties in the color group." << std::endl;
        return;
    }

    // Ensure that the property has 4 houses before building a hotel
    if (property->houses == 4 && !property->hasHotel && canAfford(property->houseCost + 100)) {
        subtractCash(property->houseCost + 100);  // Cost of 4 houses plus an additional 100 for the hotel
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
    position = 10;  
}

void Player::tryExitJail() {
    if (hasGetOutOfJailCard) {
        inJail = false;
        jailTurns = 0;
        hasGetOutOfJailCard = false;
        std::cout << name << " used a 'Get Out of Jail Free' card to exit jail." << std::endl;
    } else if (jailTurns == 0) {
        if (cash >= 50) {
            subtractCash(50);
            inJail = false;
            std::cout << name << " paid 50 shekels to exit jail." << std::endl;
        } else {
            std::cout << name << " cannot afford to pay the fine and remains in jail." << std::endl;
        }
    }
}

void Player::decrementJailTurn() {
    if (inJail) {
        jailTurns--;
        if (jailTurns == 0) {
            tryExitJail();
        }
    }
}


int Player::getNumberOfTrains() const {
    int count = 0;
    for (const Tile* tile : ownedTiles) {
        if (tile->getType() == TileType::RAILROAD) {
            count++;
        }
    }
    return count;
}
