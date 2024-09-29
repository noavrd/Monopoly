#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Tile.hpp"

class Board {
public:
    Board();
    void draw(sf::RenderWindow& window);

private:
    std::vector<Tile> tiles;
    sf::Font font;

    void initializeBoard();
    void createTile(const std::string& name, int price, TileType type, const sf::Vector2f& position, const sf::Color& color);
};

#endif // BOARD_HPP
