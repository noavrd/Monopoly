#include "Tile.hpp"
#include "Player.hpp"

Tile::Tile(const std::string& name, int price, TileType type, sf::Vector2f position, sf::Color color, const sf::Font& font)
    : name(name), price(price), type(type), owner(nullptr) {  // Initialize owner to nullptr
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
    return price / 10;  // Rent is 10% of the property's price
}
