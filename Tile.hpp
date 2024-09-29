#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class TileType {
    PROPERTY,
    RAILROAD,
    UTILITY,
    TAX,
    GO,
    JAIL,
    CHANCE,
    COMMUNITY_CHEST,
    FREE_PARKING,
    GO_TO_JAIL
};

class Tile {
public:
    std::string name;
    int price;
    TileType type;
    sf::RectangleShape shape;
    sf::Text label;

    Tile(const std::string& name, int price, TileType type, sf::Vector2f position, sf::Color color, const sf::Font& font);

    void draw(sf::RenderWindow& window);
};
