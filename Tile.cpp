#include "Tile.hpp"

Tile::Tile(const std::string& name, int price, TileType type, const sf::Vector2f& position, const sf::Color& color, sf::Font& font)
    : name(name), price(price), type(type)
{
    const float tileSize = 100.0f;
    
    // Set up the shape of the tile
    shape.setSize(sf::Vector2f(tileSize, tileSize));
    shape.setPosition(position);
    shape.setFillColor(color);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
    
    // Set up the name text
    nameText.setFont(font);
    nameText.setString(name);
    nameText.setCharacterSize(14);
    nameText.setFillColor(sf::Color::Black);
    nameText.setPosition(position.x + 10, position.y + 10);
    
    // Set up the price text 
    if (type == TileType::PROPERTY || type == TileType::RAILROAD || type == TileType::UTILITY) {
        priceText.setFont(font);
        priceText.setString("$" + std::to_string(price));
        priceText.setCharacterSize(14);
        priceText.setFillColor(sf::Color::Black);
        priceText.setPosition(position.x + 10, position.y + 40);
    }
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(nameText);
    if (!priceText.getString().isEmpty()) {
        window.draw(priceText);
    }
}
