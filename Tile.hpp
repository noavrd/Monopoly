#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <string>

enum class TileType {
    PROPERTY,
    RAILROAD,
    UTILITY,
    TAX,
    CHANCE,
    COMMUNITY_CHEST,
    JAIL,
    GO_TO_JAIL,
    FREE_PARKING,
    GO
};

class Tile {
public:
    Tile(const std::string& name, int price, TileType type, const sf::Vector2f& position, const sf::Color& color, sf::Font& font);
    
    void draw(sf::RenderWindow& window);
    const std::string& getName() const { return name; }
    int getPrice() const { return price; }
    TileType getType() const { return type; }
    
private:
    std::string name;
    int price;
    TileType type;
    sf::RectangleShape shape;
    sf::Text nameText;
    sf::Text priceText;
};

#endif // TILE_HPP
