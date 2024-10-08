#include "Tile.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;

/*
 * Constructor for the Tile class.
 * Initializes the tile's attributes such as name, price, type, color group, 
 * position, color, font, and house cost. Sets up the SFML shape for the tile
 * and creates the label for display.
 * @param name: The name of the tile.
 * @param price: The price of the tile (if applicable).
 * @param type: The type of tile (e.g., property, utility, railroad).
 * @param colorGroup: The color group the tile belongs to.
 * @param position: The position of the tile on the board.
 * @param color: The color of the tile.
 * @param font: The font used for the tile's text.
 * @param houseCost: The cost to build a house on the tile.
 */
Tile::Tile(const string& name, int price, TileType type, ColorGroup colorGroup, sf::Vector2f position, sf::Color color, const sf::Font& font, int houseCost)
    : name(name), price(price), type(type), colorGroup(colorGroup), houseCost(houseCost), houses(0), hasHotel(false), owner(nullptr), font(font), position(position) {  
    shape.setSize({ 80.0f, 80.0f });
    shape.setFillColor(color);
    shape.setPosition(position);

    // Set outline properties
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color::Black);

    // Create the initial label display
    updateLabel();
}


/*
 * Draws the tile, along with the tile's name, owner label, and house/hotel label
 * on the game window using SFML.
 * @param window: The render window to draw the tile onto.
 */
void Tile::draw(sf::RenderWindow& window) {
    window.draw(shape);       // Draw the tile
    window.draw(label);       // Draw the tile's name
    if (!ownerLabel.getString().isEmpty()) {
        window.draw(ownerLabel);  // Draw the owner's name if set
    }
    if (!houseHotelLabel.getString().isEmpty()) {
        window.draw(houseHotelLabel);  // Draw the house/hotel label if set
    }
}

/*
 * Sets the owner of the tile to the specified player. Updates the owner label
 * with the player's name and adjusts the position of the owner label based on
 * the tile's position on the board. Also updates the house/hotel label.
 * @param newOwner: The new owner of the tile.
 */
void Tile::setOwner(Player* newOwner) {
    owner = newOwner;

    if (owner) {
        ownerLabel.setFont(font);  // Ensure we use the correct font
        ownerLabel.setString(owner->name);  // Set the label to the player's name
        ownerLabel.setCharacterSize(10);  // Set the size of the text
        ownerLabel.setFillColor(sf::Color::Black);  // Set the text color

        // Determine the label position based on the tile's position on the board
        if (position.y == 0) {
            // Top row: place below the tile
            ownerLabel.setPosition(shape.getPosition().x + (shape.getSize().x - ownerLabel.getLocalBounds().width) / 2,
                                   shape.getPosition().y + shape.getSize().y + 5);
        } else if (position.x == 0) {
            // Left column: place to the right of the tile
            ownerLabel.setPosition(shape.getPosition().x + shape.getSize().x + 5,
                                   shape.getPosition().y + (shape.getSize().y - ownerLabel.getLocalBounds().height) / 2);
        } else if (position.y == 10 * 80.0f) {
            // Bottom row: place above the tile
            ownerLabel.setPosition(shape.getPosition().x + (shape.getSize().x - ownerLabel.getLocalBounds().width) / 2,
                                   shape.getPosition().y - ownerLabel.getLocalBounds().height - 5);
        } else if (position.x == 10 * 80.0f) {
            // Right column: place to the left of the tile
            ownerLabel.setPosition(shape.getPosition().x - ownerLabel.getLocalBounds().width - 5,
                                   shape.getPosition().y + (shape.getSize().y - ownerLabel.getLocalBounds().height) / 2);
        }

        // Update house/hotel label
        houseHotelLabel.setFont(font);
        houseHotelLabel.setCharacterSize(10);  // Small text for house/hotel
        houseHotelLabel.setFillColor(sf::Color::Black);

        if (hasHotel) {
            houseHotelLabel.setString("Hotel");
        } else if (houses > 0) {
            houseHotelLabel.setString("Houses: " + to_string(houses));
        } else {
            houseHotelLabel.setString("");  // Clear if no houses or hotel
        }

        // Position the house/hotel label above the owner's name
        houseHotelLabel.setPosition(ownerLabel.getPosition().x + (ownerLabel.getLocalBounds().width - houseHotelLabel.getLocalBounds().width) / 2,
                                    ownerLabel.getPosition().y - houseHotelLabel.getLocalBounds().height - 5);
    } else {
        ownerLabel.setString("");  // Clear the label if no owner
        houseHotelLabel.setString("");  // Clear the house/hotel label
    }
}

/*
 * Updates the label that displays the tile's name and price.
 * Formats the name to fit within the tile by replacing spaces with line breaks.
 * The label is then centered within the tile.
 */
void Tile::updateLabel() {
    // Format the name with price
    string formattedName = name;
    replace(formattedName.begin(), formattedName.end(), ' ', '\n');
    if (price > 0) {
        formattedName = formattedName + "\n" + to_string(price) + "$";
    }

    // Set up the label with updated content
    label.setFont(font);
    label.setString(formattedName);
    label.setCharacterSize(13);  // Adjust size for visibility within the tile
    label.setFillColor(sf::Color::Black);  // Ensure text color contrasts with tile

    // Center the label within the tile
    centerLabel();
}

/*
 * Centers the tile's label within the tile's shape by calculating the correct position
 * based on the label's text bounds and the tile's dimensions.
 */
void Tile::centerLabel() {
    // Get the bounds of the label text
    sf::FloatRect textBounds = label.getLocalBounds();

    // Center the label within the tile
    label.setPosition(
        shape.getPosition().x + (shape.getSize().x - textBounds.width) / 2,
        shape.getPosition().y + (shape.getSize().y - textBounds.height) / 2 - 5
    );
}

/*
 * Calculates the rent owed for landing on this tile.
 * Rent is determined based on the tile type (utility, railroad, or property) and
 * any improvements (houses or hotel) on the property.
 * @param diceRollResult: The result of the dice roll, used to calculate utility rent.
 * @return The rent owed for landing on the tile.
 */
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

/*
 * Returns the type of tile (e.g., property, utility, railroad).
 * @return The tile type.
 */
TileType Tile::getType() const {
    return type;
}
