#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.hpp"
#include "Player.hpp"

class Board {
public:
    sf::Font font;
    std::vector<Tile> tiles;
    std::vector<sf::CircleShape> playerTokens;
    sf::Text gameText;  

    Board();
    void initializeBoard();
    void draw(sf::RenderWindow& window, const std::vector<Player>& players);
    void updatePlayerPosition(Player& player, int playerIndex);
    void createTile(const std::string& name, int price, TileType type, ColorGroup colorGroup, sf::Vector2f position, sf::Color color, int houseCost);
    std::vector<Tile*> getTilesInColorGroup(Tile* property);
};
