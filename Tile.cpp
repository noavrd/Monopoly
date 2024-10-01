#include "Tile.hpp"
#include "Player.hpp"

Tile::Tile(const std::string& name, int price, TileType type, ColorGroup colorGroup, sf::Vector2f position, sf::Color color, const sf::Font& font, int houseCost)
    : name(name), price(price), type(type), colorGroup(colorGroup), houseCost(houseCost), houses(0), hasHotel(false), owner(nullptr) {  
    shape.setSize({ 60.0f, 60.0f });
    shape.setFillColor(color);
    shape.setPosition(position);

    // Set outline properties
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color::Black);

    std::string formattedName = name;
    std::replace(formattedName.begin(), formattedName.end(), ' ', '\n');

    label.setFont(font);
    label.setString(formattedName);
    label.setCharacterSize(10);
    label.setFillColor(sf::Color::Black);

    // Center the text inside the tile
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setPosition(position.x + (shape.getSize().x - textBounds.width) / 2,
                      position.y + (shape.getSize().y - textBounds.height) / 2 - 5);
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}

int Tile::calculateRent() const {
    if (type == TileType::RAILROAD) {
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
