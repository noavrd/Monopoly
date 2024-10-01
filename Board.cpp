#include "Board.hpp"
#include <iostream>

Board::Board() {
    // Load the Arial font
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    initializeBoard();

    // Initialize player tokens on GO
    for (int i = 0; i < 8; i++) {
        sf::CircleShape token(7.0f);  
        token.setPosition(10 * 60.0f + i * 5, 10 * 60.0f);  
        playerTokens.push_back(token);
    }

    // Initialize the text box
    gameText.setFont(font);
    gameText.setCharacterSize(20); 
    gameText.setFillColor(sf::Color::White);
    gameText.setPosition(50, 780);  
    gameText.setString("Welcome to Monopoly!");
}

void Board::initializeBoard() {
    const float tileSize = 60.0f;  

    // Define colors using RGB values
    sf::Color Pink(255, 192, 203);
    sf::Color Orange(255, 165, 0);
    sf::Color Yellow(255, 255, 0);
    sf::Color Grey(169, 169, 169);

    // Bottom row (right to left from GO to Jail)
    createTile("GO", 0, TileType::GO, ColorGroup::NONE, {10 * tileSize, 10 * tileSize}, sf::Color::Green, 0);
    createTile("Mediterranean Ave", 60, TileType::PROPERTY, ColorGroup::MAGENTA, {9 * tileSize, 10 * tileSize}, sf::Color::Magenta, 40);
    createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, ColorGroup::NONE, {8 * tileSize, 10 * tileSize}, sf::Color::White, 0);
    createTile("Baltic Ave", 60, TileType::PROPERTY, ColorGroup::MAGENTA, {7 * tileSize, 10 * tileSize}, sf::Color::Magenta, 70);
    createTile("Income Tax", 200, TileType::TAX, ColorGroup::NONE, {6 * tileSize, 10 * tileSize}, sf::Color::White, 0);
    createTile("Reading Railroad", 200, TileType::RAILROAD, ColorGroup::NONE, {5 * tileSize, 10 * tileSize}, Grey, 0);
    createTile("Oriental Ave", 100, TileType::PROPERTY, ColorGroup::CYAN, {4 * tileSize, 10 * tileSize}, sf::Color::Cyan, 80);
    createTile("Chance", 0, TileType::CHANCE, ColorGroup::NONE, {3 * tileSize, 10 * tileSize}, sf::Color::White, 0);
    createTile("Vermont Ave", 100, TileType::PROPERTY, ColorGroup::CYAN, {2 * tileSize, 10 * tileSize}, sf::Color::Cyan, 80);
    createTile("Connecticut Ave", 120, TileType::PROPERTY, ColorGroup::CYAN, {1 * tileSize, 10 * tileSize}, sf::Color::Cyan, 110);
    createTile("Jail / Just Visiting", 0, TileType::JAIL, ColorGroup::NONE, {0 * tileSize, 10 * tileSize}, sf::Color::Red, 0);

    // Left column (bottom to top from Jail to Free Parking)
    createTile("St. Charles Place", 140, TileType::PROPERTY, ColorGroup::PINK, {0 * tileSize, 9 * tileSize}, Pink, 120);
    createTile("Electric Company", 150, TileType::UTILITY, ColorGroup::NONE, {0 * tileSize, 8 * tileSize}, Grey, 0);
    createTile("States Ave", 140, TileType::PROPERTY, ColorGroup::PINK, {0 * tileSize, 7 * tileSize}, Pink, 110);
    createTile("Virginia Ave", 160, TileType::PROPERTY, ColorGroup::PINK, {0 * tileSize, 6 * tileSize}, Pink, 105);
    createTile("Pennsylvania Railroad", 200, TileType::RAILROAD, ColorGroup::NONE, {0 * tileSize, 5 * tileSize}, Grey, 0);
    createTile("St. James Place", 180, TileType::PROPERTY, ColorGroup::ORANGE, {0 * tileSize, 4 * tileSize}, Orange, 170);
    createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, ColorGroup::NONE, {0 * tileSize, 3 * tileSize}, sf::Color::White, 0);
    createTile("Tennessee Ave", 180, TileType::PROPERTY, ColorGroup::ORANGE, {0 * tileSize, 2 * tileSize}, Orange, 150);
    createTile("New York Ave", 200, TileType::PROPERTY, ColorGroup::ORANGE, {0 * tileSize, 1 * tileSize}, Orange, 100);
    createTile("Free Parking", 0, TileType::FREE_PARKING, ColorGroup::NONE, {0 * tileSize, 0 * tileSize}, Yellow, 0);

    // Top row (left to right from Free Parking to Marvin Gardens)
    createTile("Kentucky Ave", 220, TileType::PROPERTY, ColorGroup::RED, {1 * tileSize, 0 * tileSize}, sf::Color::Red, 200);
    createTile("Chance", 0, TileType::CHANCE, ColorGroup::NONE, {2 * tileSize, 0 * tileSize}, sf::Color::White, 0);
    createTile("Indiana Ave", 220, TileType::PROPERTY, ColorGroup::RED, {3 * tileSize, 0 * tileSize}, sf::Color::Red, 170);
    createTile("Illinois Ave", 240, TileType::PROPERTY, ColorGroup::RED, {4 * tileSize, 0 * tileSize}, sf::Color::Red, 160);
    createTile("B.&O. Railroad", 200, TileType::RAILROAD, ColorGroup::NONE, {5 * tileSize, 0 * tileSize}, Grey, 0);
    createTile("Atlantic Ave", 260, TileType::PROPERTY, ColorGroup::YELLOW, {6 * tileSize, 0 * tileSize}, sf::Color::Yellow, 200);
    createTile("Ventnor Ave", 260, TileType::PROPERTY, ColorGroup::YELLOW, {7 * tileSize, 0 * tileSize}, sf::Color::Yellow, 210);
    createTile("Water Works", 150, TileType::UTILITY, ColorGroup::NONE, {8 * tileSize, 0 * tileSize}, Grey, 0);
    createTile("Marvin Gardens", 280, TileType::PROPERTY, ColorGroup::YELLOW, {9 * tileSize, 0 * tileSize}, sf::Color::Yellow, 140);
    createTile("Go to Jail", 0, TileType::GO_TO_JAIL, ColorGroup::NONE, {10 * tileSize, 0 * tileSize}, sf::Color::Magenta, 0);

    // Right column (top to bottom from Go to Jail to Boardwalk)
    createTile("Pacific Ave", 300, TileType::PROPERTY, ColorGroup::GREEN, {10 * tileSize, 1 * tileSize}, sf::Color::Green, 280);
    createTile("North Carolina Ave", 300, TileType::PROPERTY, ColorGroup::GREEN, {10 * tileSize, 2 * tileSize}, sf::Color::Green, 240);
    createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, ColorGroup::NONE, {10 * tileSize, 3 * tileSize}, sf::Color::White, 0);
    createTile("Pennsylvania Ave", 320, TileType::PROPERTY, ColorGroup::GREEN, {10 * tileSize, 4 * tileSize}, sf::Color::Green, 270);
    createTile("Short Line", 200, TileType::RAILROAD, ColorGroup::NONE, {10 * tileSize, 5 * tileSize}, Grey, 0);
    createTile("Chance", 0, TileType::CHANCE, ColorGroup::NONE, {10 * tileSize, 6 * tileSize}, sf::Color::White, 0);
    createTile("Park Place", 350, TileType::PROPERTY, ColorGroup::BLUE, {10 * tileSize, 7 * tileSize}, sf::Color::Blue, 300);
    createTile("Boardwalk", 400, TileType::PROPERTY, ColorGroup::BLUE, {10 * tileSize, 8 * tileSize}, sf::Color::Blue, 320);
    createTile("Luxury Tax", 100, TileType::TAX, ColorGroup::NONE, {10 * tileSize, 9 * tileSize}, sf::Color::White, 0);
    createTile("GO", 0, TileType::GO, ColorGroup::NONE, {10 * tileSize, 10 * tileSize}, sf::Color::Green, 0);
}

void Board::createTile(const std::string& name, int price, TileType type, ColorGroup colorGroup, sf::Vector2f position, sf::Color color, int houseCost) {
    Tile tile(name, price, type, colorGroup, position, color, font, houseCost);
    tiles.push_back(tile);
}

std::vector<Tile*> Board::getTilesInColorGroup(Tile* property) {
    std::vector<Tile*> colorGroupTiles;
    
    for (Tile& tile : tiles) {
        if (tile.colorGroup == property->colorGroup) {
            colorGroupTiles.push_back(&tile);
        }
    }
    
    return colorGroupTiles;
}


void Board::draw(sf::RenderWindow& window, const std::vector<Player>& players) {
    // Draw the board (tiles, etc.)
    for (Tile& tile : tiles) {
        tile.draw(window);
    }

    // Draw each player as a circle with their player number
    for (size_t i = 0; i < players.size(); ++i) {
        const Player& player = players[i];

        // Create a circle to represent the player
        sf::CircleShape playerToken(20);  
        playerToken.setFillColor(player.color);
        playerToken.setPosition(tiles[player.position].shape.getPosition());

        // Adjust position so the circle fits within the tile
        playerToken.setPosition(
            tiles[player.position].shape.getPosition().x + 10,
            tiles[player.position].shape.getPosition().y + 10
        );

        // Draw the circle
        window.draw(playerToken);

        // Create a text to show the player number
        sf::Text playerNumber;
        playerNumber.setFont(font); 
        playerNumber.setString(std::to_string(i + 1));  
        playerNumber.setCharacterSize(14); 
        playerNumber.setFillColor(sf::Color::Black);

        // Center the number inside the circle
        sf::FloatRect textBounds = playerNumber.getLocalBounds();
        playerNumber.setPosition(
            playerToken.getPosition().x + playerToken.getRadius() - textBounds.width / 2,
            playerToken.getPosition().y + playerToken.getRadius() - textBounds.height / 2
        );

        // Draw the number inside the circle
        window.draw(playerNumber);
    }
}


void Board::updatePlayerPosition(Player& player, int playerIndex) {
    float tileSize = 60.0f;
    int pos = player.position;
    sf::Vector2f newPosition;

    // Logic to update token position based on smaller tile size
    if (pos >= 0 && pos < 10) {  // Bottom row
        newPosition = { 10 * tileSize - (pos * tileSize), 10 * tileSize };
    } else if (pos >= 10 && pos < 20) {  // Left column
        newPosition = { 0, 10 * tileSize - ((pos - 10) * tileSize) };
    } else if (pos >= 20 && pos < 30) {  // Top row
        newPosition = { (pos - 20) * tileSize, 0 };
    } else if (pos >= 30 && pos < 40) {  // Right column
        newPosition = { 10 * tileSize, (pos - 30) * tileSize };
    }

    playerTokens[playerIndex].setPosition(newPosition);
}
