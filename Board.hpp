#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Board {
public:
    Board();
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::RectangleShape> tiles;
    std::vector<sf::Text> tileLabels;
    sf::Font font;

    void initializeBoard();
    void createTile(const std::string& label, const sf::Vector2f& position, const sf::Color& color);
};

#endif // BOARD_HPP
