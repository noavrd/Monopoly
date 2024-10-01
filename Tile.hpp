#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.hpp"

enum class TileType {
    PROPERTY, RAILROAD, UTILITY, TAX, GO, JAIL, COMMUNITY_CHEST, CHANCE, FREE_PARKING, GO_TO_JAIL
};

class Player;  

class Tile {
public:
    std::string name;
    int price;
    int houses;  
    bool hasHotel; 
    int houseCost;  
    TileType type;
    sf::RectangleShape shape;
    sf::Text label;
    Player* owner;  

    Tile(const std::string& name, int price, TileType type, sf::Vector2f position, sf::Color color, const sf::Font& font, int houseCost);

    void draw(sf::RenderWindow& window);
    int calculateRent() const;
    TileType getType() const;
};
