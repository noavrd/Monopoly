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
    
    // Create and define the top row tiles
    createTile("GO", 0, TileType::GO, {0, 0}, sf::Color::Green);
    createTile("Mediterranean Ave", 60, TileType::PROPERTY, {1 * tileSize, 0}, sf::Color::Magenta);
    createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, {2 * tileSize, 0}, sf::Color::White);
    createTile("Baltic Ave", 60, TileType::PROPERTY, {3 * tileSize, 0}, sf::Color::Magenta);
    createTile("Income Tax", 200, TileType::TAX, {4 * tileSize, 0}, sf::Color::White);
    createTile("Reading Railroad", 200, TileType::RAILROAD, {5 * tileSize, 0}, sf::Color::Black);
    createTile("Oriental Ave", 100, TileType::PROPERTY, {6 * tileSize, 0}, sf::Color::Cyan);
    createTile("Chance", 0, TileType::CHANCE, {7 * tileSize, 0}, sf::Color::White);
    createTile("Vermont Ave", 100, TileType::PROPERTY, {8 * tileSize, 0}, sf::Color::Cyan);
    createTile("Connecticut Ave", 120, TileType::PROPERTY, {9 * tileSize, 0}, sf::Color::Cyan);
    
    // Create the right column tiles
    createTile("St. Charles Place", 140, TileType::PROPERTY, {9 * tileSize, 1 * tileSize}, sf::Color::Pink);
    createTile("Electric Company", 150, TileType::UTILITY, {9 * tileSize, 2 * tileSize}, sf::Color::White);
    createTile("States Ave", 140, TileType::PROPERTY, {9 * tileSize, 3 * tileSize}, sf::Color::Pink);
    createTile("Virginia Ave", 160, TileType::PROPERTY, {9 * tileSize, 4 * tileSize}, sf::Color::Pink);
    createTile("Pennsylvania Railroad", 200, TileType::RAILROAD, {9 * tileSize, 5 * tileSize}, sf::Color::Black);
    createTile("St. James Place", 180, TileType::PROPERTY, {9 * tileSize, 6 * tileSize}, sf::Color::Orange);
    createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, {9 * tileSize, 7 * tileSize}, sf::Color::White);
    createTile("Tennessee Ave", 180, TileType::PROPERTY, {9 * tileSize, 8 * tileSize}, sf::Color::Orange);
    createTile("New York Ave", 200, TileType::PROPERTY, {9 * tileSize, 9 * tileSize}, sf::Color::Orange);
    
    // Create the bottom row tiles
    createTile("Kentucky Ave", 220, TileType::PROPERTY, {8 * tileSize, 9 * tileSize}, sf::Color::Red);
    createTile("Chance", 0, TileType::CHANCE, {7 * tileSize, 9 * tileSize}, sf::Color::White);
    createTile("Indiana Ave", 220, TileType::PROPERTY, {6 * tileSize, 9 * tileSize}, sf::Color::Red);
    createTile("Illinois Ave", 240, TileType::PROPERTY, {5 * tileSize, 9 * tileSize}, sf::Color::Red);
    createTile("B. & O. Railroad", 200, TileType::RAILROAD, {4 * tileSize, 9 * tileSize}, sf::Color::Black);
    createTile("Atlantic Ave", 260, TileType::PROPERTY, {3 * tileSize, 9 * tileSize}, sf::Color::Yellow);
    createTile("Ventnor Ave", 260, TileType::PROPERTY, {2 * tileSize, 9 * tileSize}, sf::Color::Yellow);
    createTile("Water Works", 150, TileType::UTILITY, {1 * tileSize, 9 * tileSize}, sf::Color::White);
    createTile("Marvin Gardens", 280, TileType::PROPERTY, {0 * tileSize, 9 * tileSize}, sf::Color::Yellow);

    // Create the left column tiles
    createTile("Pacific Ave", 300, TileType::PROPERTY, {0, 8 * tileSize}, sf::Color::Green);
    createTile("North Carolina Ave", 300, TileType::PROPERTY, {0, 7 * tileSize}, sf::Color::Green);
    createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, {0, 6 * tileSize}, sf::Color::White);
    createTile("Pennsylvania Ave", 320, TileType::PROPERTY, {0, 5 * tileSize}, sf::Color::Green);
    createTile("Short Line", 200, TileType::RAILROAD, {0, 4 * tileSize}, sf::Color::Black);
    createTile("Chance", 0, TileType::CHANCE, {0, 3 * tileSize}, sf::Color::White);
    createTile("Park Place", 350, TileType::PROPERTY, {0, 2 * tileSize}, sf::Color::Blue);
    createTile("Luxury Tax", 100, TileType::TAX, {0, 1 * tileSize}, sf::Color::White);
    createTile("Boardwalk", 400, TileType::PROPERTY, {0, 0 * tileSize}, sf::Color::Blue);
}

void Board::createTile(const std::string& name, int price, TileType type, const sf::Vector2f& position, const sf::Color& color) {
    tiles.emplace_back(name, price, type, position, color, font);
}

void Board::draw(sf::RenderWindow& window) {
    for (auto& tile : tiles) {
        tile.draw(window);
    }
}
