#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Player;

enum class TileType {
    PROPERTY, RAILROAD, UTILITY, TAX, GO, JAIL, COMMUNITY_CHEST, CHANCE, FREE_PARKING, GO_TO_JAIL
};

enum class ColorGroup {
    PINK, ORANGE, YELLOW, GREY, MAGENTA, CYAN, WHITE, RED, GREEN, BLUE, NONE
};

class Tile {
public:
    std::string name;
    int price;
    int houses;
    bool hasHotel;
    int houseCost;
    TileType type;
    ColorGroup colorGroup;
    sf::RectangleShape shape;
    sf::Text label;
    sf::Text ownerLabel;
    sf::Text houseHotelLabel;
    Player* owner;
    sf::Vector2f position;
    const sf::Font& font;

    Tile(const std::string& name, int price, TileType type, ColorGroup colorGroup, sf::Vector2f position, sf::Color color, const sf::Font& font, int houseCost);

    void draw(sf::RenderWindow& window);
    int calculateRent(int diceRollResult) const;
    TileType getType() const;
    void setOwner(Player* newOwner);
    void updateLabel();
    void centerLabel();
};