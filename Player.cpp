#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

using namespace std; 

/*
 * Constructor for the Player class.
 * Initializes the player's name, starting cash, position on the board,
 * jail status, number of jail turns, whether they have a Get Out of Jail card,
 * and their default color.
 */
Player::Player(const string& playerName)
    : name(playerName), cash(1500), position(0), inJail(false), jailTurns(0), hasGetOutOfJailCard(false), color(sf::Color::White) {}

/*
 * Adds the specified amount of cash to the player's total cash.
 * Prints the updated cash amount.
 * @param amount: The amount of cash to add.
 */
void Player::addCash(int amount) {
    cash += amount;
    cout << name << " received $" << amount << ". Total cash: $" << cash << endl;
}

/*
 * Subtracts the specified amount of cash from the player's total cash if they can afford it.
 * Prints the remaining cash or indicates that the player is bankrupt if they can't afford it.
 * @param amount: The amount of cash to subtract.
 * @return True if the player can afford to pay, false if they are bankrupt.
 */
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

/*
 * Moves the player by the specified number of steps on the board.
 * The position is wrapped around using modulo 40 for a circular board.
 * @param steps: The number of steps to move the player.
 */
void Player::move(int steps) {
    position = (position + steps) % 40;  // Circular board logic
}

/*
 * Checks if the player can afford to pay the specified amount.
 * @param amount: The amount to check.
 * @return True if the player has enough cash, false otherwise.
 */
bool Player::canAfford(int amount) const {
    return cash >= amount;
}

/*
 * Allows the player to buy a property if they can afford it.
 * Deducts the property price from the player's cash and adds the property to their owned tiles.
 * Prints the details of the purchase.
 * @param property: The property tile that the player wants to buy.
 */
void Player::buyProperty(Tile* property) {
    if (canAfford(property->price)) {
        subtractCash(property->price);
        ownedTiles.push_back(property);
        property->setOwner(this);  // Ensure this sets the owner correctly
        cout << name << " bought " << property->name << " for $" << property->price << endl;
    } else {
        cout << name << " cannot afford to buy " << property->name << endl;
    }
}

/*
 * Checks if the player owns all properties in a given color group.
 * Prints the result of the check for each property.
 * @param colorGroupTiles: A vector of tiles in the color group.
 * @return True if the player owns all tiles in the color group, false otherwise.
 */
bool Player::ownsAllInColorGroup(const vector<Tile*>& colorGroupTiles) const {
    cout << "Checking ownership for player: " << name << endl;
    for (const Tile* tile : colorGroupTiles) {
        cout << "Tile: " << tile->name << " owned by: " 
             << (tile->owner ? tile->owner->name : "None") << endl;
        if (tile->owner != this) {
            cout << name << " does not own " << tile->name << endl;
            return false;
        }
    }
    cout << name << " owns all properties in the color group!" << endl;
    return true;
}

/*
 * Checks if the player has an even house distribution across all properties
 * in the color group, compared to the target property.
 * @param colorGroupTiles: A vector of tiles in the color group.
 * @param targetProperty: The property on which the player wants to build a house.
 * @return True if the player has built houses evenly across the group, false otherwise.
 */
bool Player::isEvenHouseDistribution(const vector<Tile*>& colorGroupTiles, Tile* targetProperty) const {
    return all_of(colorGroupTiles.begin(), colorGroupTiles.end(), [targetProperty](Tile* tile) {
        return tile->houses >= targetProperty->houses;
    });
}

/*
 * Builds a house on the specified property if the player owns all properties in the color group,
 * has built evenly across the group, and can afford it. Prints the result of the action.
 * @param property: The property on which the player wants to build a house.
 * @param board: The game board used to retrieve the tiles in the color group.
 */
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


/*
 * Builds a hotel on the specified property if the player owns all properties in the color group,
 * has built 4 houses, and can afford it. Prints the result of the action.
 * @param property: The property on which the player wants to build a hotel.
 * @param board: The game board used to retrieve the tiles in the color group.
 */
void Player::buildHotel(Tile* property, Board& board) {
    auto colorGroupTiles = board.getTilesInColorGroup(property);

    // Validate ownership and house count
    if (!ownsAllInColorGroup(colorGroupTiles)) {
        cout << name << " cannot build a hotel on " << property->name << " because they do not own all properties in the color group." << endl;
        return;
    }
    if (property->houses == 4 && !property->hasHotel && canAfford(property->houseCost + 100)) {
        subtractCash(property->houseCost * 4 + 100);  // Cost of 4 houses + 100 for the hotel
        property->houses = 0;  // Reset house count
        property->hasHotel = true;
        cout << name << " built a hotel on " << property->name << "!" << endl;
    } else {
        cout << name << " needs 4 houses on " << property->name << " before building a hotel." << endl;
    }
}

/*
 * Sends the player to jail, setting their position to the jail tile,
 * flagging them as in jail, and starting their jail turns.
 */
void Player::goToJail() {
    inJail = true;
    jailTurns = 3;  
    position = 10;  // Jail position
}

/*
 * Attempts to exit jail by using a Get Out of Jail Free card or paying a fine.
 * Prints the result of the attempt.
 */
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

/*
 * Decrements the player's remaining jail turns. If the player's turns reach 0,
 * they attempt to exit jail.
 */
void Player::decrementJailTurn() {
    if (inJail && --jailTurns == 0) {
        tryExitJail();
    }
}

/*
 * Counts and returns the number of railroad tiles the player owns.
 * @return The number of railroads owned by the player.
 */
int Player::getNumberOfTrains() const {
    int count = 0;
    for (const Tile* tile : ownedTiles) {
        if (tile->getType() == TileType::RAILROAD) {
            count++;
        }
    }
    return count;
}

