#include "Board.hpp"
#include <iostream>

Board::Board() {
    // Load the font for text on the board
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    initializeBoard();
}

void Board::initializeBoard() {
    const float tileSize = 100.0f;
    
    // Define the corner tiles
    createTile("GO", {0, 0}, sf::Color::Green);
    createTile("Jail", {0, 9 * tileSize}, sf::Color::Red);
    createTile("Free Parking", {9 * tileSize, 9 * tileSize}, sf::Color::Yellow);
    createTile("Go to Jail", {9 * tileSize, 0}, sf::Color::Magenta);
    
    // Top row (11 tiles)
    createTile("Mediterranean Ave", {1 * tileSize, 0}, sf::Color::Magenta);
    createTile("Community Chest", {2 * tileSize, 0}, sf::Color::White);
    createTile("Baltic Ave", {3 * tileSize, 0}, sf::Color::Magenta);
    createTile("Income Tax", {4 * tileSize, 0}, sf::Color::White);
    createTile("Reading Railroad", {5 * tileSize, 0}, sf::Color::Black);
    createTile("Oriental Ave", {6 * tileSize, 0}, sf::Color::Cyan);
    createTile("Chance", {7 * tileSize, 0}, sf::Color::White);
    createTile("Vermont Ave", {8 * tileSize, 0}, sf::Color::Cyan);
    createTile("Connecticut Ave", {9 * tileSize, 0}, sf::Color::Cyan);

    // Right column (9 tiles)
    createTile("St. Charles Place", {9 * tileSize, 1 * tileSize}, sf::Color::Pink);
    createTile("Electric Company", {9 * tileSize, 2 * tileSize}, sf::Color::White);
    createTile("States Ave", {9 * tileSize, 3 * tileSize}, sf::Color::Pink);
    createTile("Virginia Ave", {9 * tileSize, 4 * tileSize}, sf::Color::Pink);
    createTile("Pennsylvania Railroad", {9 * tileSize, 5 * tileSize}, sf::Color::Black);
    createTile("St. James Place", {9 * tileSize, 6 * tileSize}, sf::Color::Orange);
    createTile("Community Chest", {9 * tileSize, 7 * tileSize}, sf::Color::White);
    createTile("Tennessee Ave", {9 * tileSize, 8 * tileSize}, sf::Color::Orange);
    createTile("New York Ave", {9 * tileSize, 9 * tileSize}, sf::Color::Orange);

    // Bottom row (10 tiles)
    createTile("Kentucky Ave", {8 * tileSize, 9 * tileSize}, sf::Color::Red);
    createTile("Chance", {7 * tileSize, 9 * tileSize}, sf::Color::White);
    createTile("Indiana Ave", {6 * tileSize, 9 * tileSize}, sf::Color::Red);
    createTile("Illinois Ave", {5 * tileSize, 9 * tileSize}, sf::Color::Red);
    createTile("B. & O. Railroad", {4 * tileSize, 9 * tileSize}, sf::Color::Black);
    createTile("Atlantic Ave", {3 * tileSize, 9 * tileSize}, sf::Color::Yellow);
    createTile("Ventnor Ave", {2 * tileSize, 9 * tileSize}, sf::Color::Yellow);
    createTile("Water Works", {1 * tileSize, 9 * tileSize}, sf::Color::White);
    createTile("Marvin Gardens", {0 * tileSize, 9 * tileSize}, sf::Color::Yellow);

    // Left column (8 tiles)
    createTile("Pacific Ave", {0, 8 * tileSize}, sf::Color::Green);
    createTile("North Carolina Ave", {0, 7 * tileSize}, sf::Color::Green);
    createTile("Community Chest", {0, 6 * tileSize}, sf::Color::White);
    createTile("Pennsylvania Ave", {0, 5 * tileSize}, sf::Color::Green);
    createTile("Short Line", {0, 4 * tileSize}, sf::Color::Black);
    createTile("Chance", {0, 3 * tileSize}, sf::Color::White);
    createTile("Park Place", {0, 2 * tileSize}, sf::Color::Blue);
    createTile("Luxury Tax", {0, 1 * tileSize}, sf::Color::White);
    createTile("Boardwalk", {0, 0 * tileSize}, sf::Color::Blue);
}

void Board::createTile(const std::string& label, const sf::Vector2f& position, const sf::Color& color) {
    const float tileSize = 100.0f;

    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
    tile.setPosition(position);
    tile.setFillColor(color);
    tile.setOutlineThickness(2);
    tile.setOutlineColor(sf::Color::Black);

    sf::Text tileText(label, font, 14);
    tileText.setFillColor(sf::Color::Black);
    tileText.setPosition(position.x + 10, position.y + 40);

    tiles.push_back(tile);
    tileLabels.push_back(tileText);
}

void Board::draw(sf::RenderWindow& window) {
    for (const auto& tile : tiles) {
        window.draw(tile);
    }
    for (const auto& label : tileLabels) {
        window.draw(label);
    }
}
