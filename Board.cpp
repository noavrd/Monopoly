#include "Board.hpp"
#include <iostream>

Board::Board() {
    // Load the font for text on the board
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    initializeBoard();
}
void Board::initializeBoard() {
    const float tileSize = 100.0f;

    // Define custom colors using RGB values
    sf::Color Pink(255, 192, 203);
    sf::Color Orange(255, 165, 0);
    sf::Color Yellow(255, 255, 0);
    sf::Color Grey(169, 169, 169);

    // Bottom row (right to left from GO to Connecticut Ave)
    createTile("GO", 0, TileType::GO, {10 * tileSize, 10 * tileSize}, sf::Color::Green);  // Corner
    createTile("Mediterranean Ave", 60, TileType::PROPERTY, {9 * tileSize, 10 * tileSize}, sf::Color::Magenta);
    createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, {8 * tileSize, 10 * tileSize}, sf::Color::White);
    createTile("Baltic Ave", 60, TileType::PROPERTY, {7 * tileSize, 10 * tileSize}, sf::Color::Magenta);
    createTile("Income Tax", 200, TileType::TAX, {6 * tileSize, 10 * tileSize}, sf::Color::White);
    createTile("Reading Railroad", 200, TileType::RAILROAD, {5 * tileSize, 10 * tileSize}, Grey);
    createTile("Oriental Ave", 100, TileType::PROPERTY, {4 * tileSize, 10 * tileSize}, sf::Color::Cyan);
    createTile("Chance", 0, TileType::CHANCE, {3 * tileSize, 10 * tileSize}, sf::Color::White);
    createTile("Vermont Ave", 100, TileType::PROPERTY, {2 * tileSize, 10 * tileSize}, sf::Color::Cyan);
    createTile("Connecticut Ave", 120, TileType::PROPERTY, {1 * tileSize, 10 * tileSize}, sf::Color::Cyan);
    createTile("Jail / Just Visiting", 0, TileType::JAIL, {0 * tileSize, 10 * tileSize}, sf::Color::Red);  // Corner

    // Left column (bottom to top from Jail to Free Parking)
    createTile("St. Charles Place", 140, TileType::PROPERTY, {0 * tileSize, 9 * tileSize}, Pink);
    createTile("Electric Company", 150, TileType::UTILITY, {0 * tileSize, 8 * tileSize}, Grey);
    createTile("States Ave", 140, TileType::PROPERTY, {0 * tileSize, 7 * tileSize}, Pink);
    createTile("Virginia Ave", 160, TileType::PROPERTY, {0 * tileSize, 6 * tileSize}, Pink);
    createTile("Pennsylvania Railroad", 200, TileType::RAILROAD, {0 * tileSize, 5 * tileSize}, Grey);
    createTile("St. James Place", 180, TileType::PROPERTY, {0 * tileSize, 4 * tileSize}, Orange);
    createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, {0 * tileSize, 3 * tileSize}, sf::Color::White);
    createTile("Tennessee Ave", 180, TileType::PROPERTY, {0 * tileSize, 2 * tileSize}, Orange);
    createTile("New York Ave", 200, TileType::PROPERTY, {0 * tileSize, 1 * tileSize}, Orange);
    createTile("Free Parking", 0, TileType::FREE_PARKING, {0 * tileSize, 0 * tileSize}, Yellow);  // Corner

    // Top row (left to right from Free Parking to Marvin Gardens)
    createTile("Kentucky Ave", 220, TileType::PROPERTY, {1 * tileSize, 0 * tileSize}, sf::Color::Red);
    createTile("Chance", 0, TileType::CHANCE, {2 * tileSize, 0 * tileSize}, sf::Color::White);
    createTile("Indiana Ave", 220, TileType::PROPERTY, {3 * tileSize, 0 * tileSize}, sf::Color::Red);
    createTile("Illinois Ave", 240, TileType::PROPERTY, {4 * tileSize, 0 * tileSize}, sf::Color::Red);
    createTile("B. & O. Railroad", 200, TileType::RAILROAD, {5 * tileSize, 0 * tileSize}, Grey);
    createTile("Atlantic Ave", 260, TileType::PROPERTY, {6 * tileSize, 0 * tileSize}, sf::Color::Yellow);
    createTile("Ventnor Ave", 260, TileType::PROPERTY, {7 * tileSize, 0 * tileSize}, sf::Color::Yellow);
    createTile("Water Works", 150, TileType::UTILITY, {8 * tileSize, 0 * tileSize}, Grey);
    createTile("Marvin Gardens", 280, TileType::PROPERTY, {9 * tileSize, 0 * tileSize}, sf::Color::Yellow);
    createTile("Go to Jail", 0, TileType::GO_TO_JAIL, {10 * tileSize, 0 * tileSize}, sf::Color::Magenta);  // Corner

    // Right column (top to bottom from Go to Jail to Boardwalk)
    createTile("Pacific Ave", 300, TileType::PROPERTY, {10 * tileSize, 1 * tileSize}, sf::Color::Green);
    createTile("North Carolina Ave", 300, TileType::PROPERTY, {10 * tileSize, 2 * tileSize}, sf::Color::Green);
    createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, {10 * tileSize, 3 * tileSize}, sf::Color::White);
    createTile("Pennsylvania Ave", 320, TileType::PROPERTY, {10 * tileSize, 4 * tileSize}, sf::Color::Green);
    createTile("Short Line", 200, TileType::RAILROAD, {10 * tileSize, 5 * tileSize}, Grey);
    createTile("Chance", 0, TileType::CHANCE, {10 * tileSize, 6 * tileSize}, sf::Color::White);
    createTile("Park Place", 350, TileType::PROPERTY, {10 * tileSize, 7 * tileSize}, sf::Color::Blue);
    createTile("Boardwalk", 400, TileType::PROPERTY, {10 * tileSize, 8 * tileSize}, sf::Color::Blue);
    createTile("Luxury Tax", 100, TileType::TAX, {10 * tileSize, 9 * tileSize}, sf::Color::White);
    createTile("GO", 0, TileType::GO, {10 * tileSize, 10 * tileSize}, sf::Color::Green);  // Corner
}
void Board::createTile(const std::string& name, int price, TileType type, const sf::Vector2f& position, const sf::Color& color) {
    tiles.emplace_back(name, price, type, position, color, font);
}

void Board::draw(sf::RenderWindow& window) {
    for (auto& tile : tiles) {
        tile.draw(window);
    }
}
