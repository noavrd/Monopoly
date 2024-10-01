#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

using namespace std; 

Player::Player(const string& playerName)
    : name(playerName), cash(1500), position(0), inJail(false), jailTurns(0), hasGetOutOfJailCard(false), color(sf::Color::White) {}

void Player::addCash(int amount) {
    cash += amount;
    cout << name << " received $" << amount << ". Total cash: $" << cash << endl;
}

bool Player::subtractCash(int amount) {
    if (canAfford(amount)) {
        cash -= amount;
        cout << name << " paid $" << amount << ". Remaining cash: $" << cash << endl;
        return true;
    } else {
        cout << name << " cannot afford to pay $" << amount << " and is bankrupt!" << endl;
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
        property->setOwner(this);
        cout << name << " bought " << property->name << " for $" << property->price << endl;
    } else {
        cout << name << " cannot afford to buy " << property->name << endl;
    }
}


// Helper function to check color group ownership
bool Player::ownsAllInColorGroup(const vector<Tile*>& colorGroupTiles) const {
    return all_of(colorGroupTiles.begin(), colorGroupTiles.end(), [this](Tile* tile) {
        return tile->owner == this;
    });
}

// Helper function to check house distribution
bool Player::isEvenHouseDistribution(const vector<Tile*>& colorGroupTiles, Tile* targetProperty) const {
    return all_of(colorGroupTiles.begin(), colorGroupTiles.end(), [targetProperty](Tile* tile) {
        return tile->houses >= targetProperty->houses;
    });
}

void Player::buildHouse(Tile* property, Board& board) {
    auto colorGroupTiles = board.getTilesInColorGroup(property);

    // Validate ownership and house distribution
    if (!ownsAllInColorGroup(colorGroupTiles)) {
        cout << name << " cannot build a house on " << property->name << " because they do not own all properties in the color group." << endl;
        return;
    }
    if (!isEvenHouseDistribution(colorGroupTiles, property)) {
        cout << name << " must build evenly across all properties in the color group." << endl;
        return;
    }

    // Build the house if allowed
    if (property->houses < 4 && !property->hasHotel && canAfford(property->houseCost)) {
        subtractCash(property->houseCost);
        property->houses++;
        cout << name << " built a house on " << property->name << ". Total houses: " << property->houses << endl;
    } else {
        cout << name << " cannot build more houses on " << property->name << " or already has a hotel." << endl;
    }
}

void Player::buildHotel(Tile* property, Board& board) {
    auto colorGroupTiles = board.getTilesInColorGroup(property);

    // Validate ownership and house count
    if (!ownsAllInColorGroup(colorGroupTiles)) {
        cout << name << " cannot build a hotel on " << property->name << " because they do not own all properties in the color group." << endl;
        return;
    }
    if (property->houses == 4 && !property->hasHotel && canAfford(property->houseCost + 100)) {
        subtractCash(property->houseCost + 100);  // Cost of 4 houses + 100 for the hotel
        property->houses = 0;  // Reset house count
        property->hasHotel = true;
        cout << name << " built a hotel on " << property->name << "!" << endl;
    } else {
        cout << name << " needs 4 houses on " << property->name << " before building a hotel." << endl;
    }
}

void Player::goToJail() {
    inJail = true;
    jailTurns = 3;  
    position = 10;  // Jail position
}

void Player::tryExitJail() {
    if (hasGetOutOfJailCard) {
        inJail = false;
        jailTurns = 0;
        hasGetOutOfJailCard = false;
        cout << name << " used a 'Get Out of Jail Free' card to exit jail." << endl;
    } else if (jailTurns == 0) {
        if (canAfford(50)) {
            subtractCash(50);
            inJail = false;
            cout << name << " paid 50 shekels to exit jail." << endl;
        } else {
            cout << name << " cannot afford to pay the fine and remains in jail." << endl;
        }
    }
}

void Player::decrementJailTurn() {
    if (inJail && --jailTurns == 0) {
        tryExitJail();
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

