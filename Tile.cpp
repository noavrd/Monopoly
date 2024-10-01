#include "Tile.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;

Tile::Tile(const string& name, int price, TileType type, ColorGroup colorGroup, sf::Vector2f position, sf::Color color, const sf::Font& font, int houseCost)
    : name(name), price(price), type(type), colorGroup(colorGroup), houseCost(houseCost), houses(0), hasHotel(false), owner(nullptr), font(font), position(position) {  
    shape.setSize({ 60.0f, 60.0f });
    shape.setFillColor(color);
    shape.setPosition(position);

    // Set outline properties
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color::Black);

    // Create the initial label display
    updateLabel();
}

void Tile::draw(sf::RenderWindow& window) {
    // Draw the tile first
    window.draw(shape);

    // Then draw the label on top of it
    window.draw(label);
}

void Tile::setOwner(Player* newOwner) {
    owner = newOwner;

    // Update the label content to reflect the new owner
    updateLabel();

    // Debugging information
    cout << "Tile: " << name << " now owned by: " << (owner ? owner->name : "None") << endl;
}

void Tile::updateLabel() {
    // Format the name with owner information if available
    string formattedName = name;
    replace(formattedName.begin(), formattedName.end(), ' ', '\n');

    if (owner) {
        formattedName += "\n(" + owner->name + ")";
    }

    // Set up the label with updated content
    label.setFont(font);
    label.setString(formattedName);
    label.setCharacterSize(12);  // Adjust size for visibility within the tile
    label.setFillColor(sf::Color::Black);  // Ensure text color contrasts with tile

    // Center the label within the tile
    centerLabel();
}

void Tile::centerLabel() {
    // Get the bounds of the label text
    sf::FloatRect textBounds = label.getLocalBounds();

    // Center the label within the tile
    label.setPosition(
        shape.getPosition().x + (shape.getSize().x - textBounds.width) / 2,
        shape.getPosition().y + (shape.getSize().y - textBounds.height) / 2 - 5
    );

    // Debugging information to confirm label position
    cout << "Label centered at position: " << label.getPosition().x << ", " << label.getPosition().y << endl;
}

int Tile::calculateRent(int diceRollResult) const {
    // Utility Rent Logic
    if (type == TileType::UTILITY) {
        // Rent is 10 times the dice roll if owned by another player
        return 10 * diceRollResult;
    } else if (type == TileType::RAILROAD) {
        // Railroad rent logic as before
        int numberOfTrainsOwned = owner->getNumberOfTrains();
        switch (numberOfTrainsOwned) {
            case 1: return 50;
            case 2: return 100;
            case 3: return 150;
            case 4: return 200;
            default: return 0;
        }
    } else if (hasHotel) {
        return price / 5 + 100;  // Rent for hotel
    } else if (houses > 0) {
        int baseRent = price / 10;  // Base rent for the property
        return baseRent * (1 << (houses - 1));  
    } else {
        return price / 10;  // Base rent without houses or hotels
    }
}

TileType Tile::getType() const {
    return type;
}
