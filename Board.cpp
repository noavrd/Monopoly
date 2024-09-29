// #include "Board.hpp"
// #include <iostream>

// Board::Board() {
//     // Load the font from the specified path
//     if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf")) {
//         std::cerr << "Error loading font" << std::endl;
//     }

//     initializeBoard();

//     // Initialize player tokens (example for up to 8 players)
//     for (int i = 0; i < 8; i++) {
//         sf::CircleShape token(7.0f);  // Smaller tokens, radius reduced to 7
//         token.setFillColor(sf::Color::Red);  // Different colors can be assigned for each player
//         token.setPosition(10 * 60.0f + i * 5, 10 * 60.0f);  // Position adjusted for smaller tiles
//         playerTokens.push_back(token);
//     }

//     // Initialize the text box
//     gameText.setFont(font);
//     gameText.setCharacterSize(20);  // Adjusted font size for smaller window
//     gameText.setFillColor(sf::Color::White);
//     gameText.setPosition(50, 780);  // Position adjusted for smaller window
//     gameText.setString("Welcome to Monopoly!");  // Initial message
// }

// void Board::initializeBoard() {
//     const float tileSize = 60.0f; // Smaller tile size

//     // Define custom colors using RGB values
//     sf::Color Pink(255, 192, 203);
//     sf::Color Orange(255, 165, 0);
//     sf::Color Yellow(255, 255, 0);
//     sf::Color Grey(169, 169, 169);

//     // Bottom row (right to left from GO to Jail)
//     createTile("GO", 0, TileType::GO, {10 * tileSize, 10 * tileSize}, sf::Color::Green);  // Corner
//     createTile("Mediterranean Ave", 60, TileType::PROPERTY, {9 * tileSize, 10 * tileSize}, sf::Color::Magenta);
//     createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, {8 * tileSize, 10 * tileSize}, sf::Color::White);
//     createTile("Baltic Ave", 60, TileType::PROPERTY, {7 * tileSize, 10 * tileSize}, sf::Color::Magenta);
//     createTile("Income Tax", 200, TileType::TAX, {6 * tileSize, 10 * tileSize}, sf::Color::White);
//     createTile("Reading Railroad", 200, TileType::RAILROAD, {5 * tileSize, 10 * tileSize}, Grey);
//     createTile("Oriental Ave", 100, TileType::PROPERTY, {4 * tileSize, 10 * tileSize}, sf::Color::Cyan);
//     createTile("Chance", 0, TileType::CHANCE, {3 * tileSize, 10 * tileSize}, sf::Color::White);
//     createTile("Vermont Ave", 100, TileType::PROPERTY, {2 * tileSize, 10 * tileSize}, sf::Color::Cyan);
//     createTile("Connecticut Ave", 120, TileType::PROPERTY, {1 * tileSize, 10 * tileSize}, sf::Color::Cyan);
//     createTile("Jail / Just Visiting", 0, TileType::JAIL, {0 * tileSize, 10 * tileSize}, sf::Color::Red);  // Corner

//     // Left column (bottom to top from Jail to Free Parking)
//     createTile("St. Charles Place", 140, TileType::PROPERTY, {0 * tileSize, 9 * tileSize}, Pink);
//     createTile("Electric Company", 150, TileType::UTILITY, {0 * tileSize, 8 * tileSize}, Grey);
//     createTile("States Ave", 140, TileType::PROPERTY, {0 * tileSize, 7 * tileSize}, Pink);
//     createTile("Virginia Ave", 160, TileType::PROPERTY, {0 * tileSize, 6 * tileSize}, Pink);
//     createTile("Pennsylvania Railroad", 200, TileType::RAILROAD, {0 * tileSize, 5 * tileSize}, Grey);
//     createTile("St. James Place", 180, TileType::PROPERTY, {0 * tileSize, 4 * tileSize}, Orange);
//     createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, {0 * tileSize, 3 * tileSize}, sf::Color::White);
//     createTile("Tennessee Ave", 180, TileType::PROPERTY, {0 * tileSize, 2 * tileSize}, Orange);
//     createTile("New York Ave", 200, TileType::PROPERTY, {0 * tileSize, 1 * tileSize}, Orange);
//     createTile("Free Parking", 0, TileType::FREE_PARKING, {0 * tileSize, 0 * tileSize}, Yellow);  // Corner

//     // Top row (left to right from Free Parking to Marvin Gardens)
//     createTile("Kentucky Ave", 220, TileType::PROPERTY, {1 * tileSize, 0 * tileSize}, sf::Color::Red);
//     createTile("Chance", 0, TileType::CHANCE, {2 * tileSize, 0 * tileSize}, sf::Color::White);
//     createTile("Indiana Ave", 220, TileType::PROPERTY, {3 * tileSize, 0 * tileSize}, sf::Color::Red);
//     createTile("Illinois Ave", 240, TileType::PROPERTY, {4 * tileSize, 0 * tileSize}, sf::Color::Red);
//     createTile("B. & O. Railroad", 200, TileType::RAILROAD, {5 * tileSize, 0 * tileSize}, Grey);
//     createTile("Atlantic Ave", 260, TileType::PROPERTY, {6 * tileSize, 0 * tileSize}, sf::Color::Yellow);
//     createTile("Ventnor Ave", 260, TileType::PROPERTY, {7 * tileSize, 0 * tileSize}, sf::Color::Yellow);
//     createTile("Water Works", 150, TileType::UTILITY, {8 * tileSize, 0 * tileSize}, Grey);
//     createTile("Marvin Gardens", 280, TileType::PROPERTY, {9 * tileSize, 0 * tileSize}, sf::Color::Yellow);
//     createTile("Go to Jail", 0, TileType::GO_TO_JAIL, {10 * tileSize, 0 * tileSize}, sf::Color::Magenta);  // Corner

//     // Right column (top to bottom from Go to Jail to Boardwalk)
//     createTile("Pacific Ave", 300, TileType::PROPERTY, {10 * tileSize, 1 * tileSize}, sf::Color::Green);
//     createTile("North Carolina Ave", 300, TileType::PROPERTY, {10 * tileSize, 2 * tileSize}, sf::Color::Green);
//     createTile("Community Chest", 0, TileType::COMMUNITY_CHEST, {10 * tileSize, 3 * tileSize}, sf::Color::White);
//     createTile("Pennsylvania Ave", 320, TileType::PROPERTY, {10 * tileSize, 4 * tileSize}, sf::Color::Green);
//     createTile("Short Line", 200, TileType::RAILROAD, {10 * tileSize, 5 * tileSize}, Grey);
//     createTile("Chance", 0, TileType::CHANCE, {10 * tileSize, 6 * tileSize}, sf::Color::White);
//     createTile("Park Place", 350, TileType::PROPERTY, {10 * tileSize, 7 * tileSize}, sf::Color::Blue);
//     createTile("Boardwalk", 400, TileType::PROPERTY, {10 * tileSize, 8 * tileSize}, sf::Color::Blue);
//     createTile("Luxury Tax", 100, TileType::TAX, {10 * tileSize, 9 * tileSize}, sf::Color::White);
//     createTile("GO", 0, TileType::GO, {10 * tileSize, 10 * tileSize}, sf::Color::Green);  // Corner
// }

// void Board::draw(sf::RenderWindow& window) {
//     // Draw each tile
//     for (auto& tile : tiles) {
//         tile.draw(window);  // Ensure the tiles are drawn properly
//     }

//     // Draw player tokens
//     for (auto& token : playerTokens) {
//         window.draw(token);
//     }

//     // Draw game messages
//     window.draw(gameText);
// }

// void Board::updatePlayerPosition(Player& player, int playerIndex) {
//     float tileSize = 60.0f;
//     int pos = player.position;
//     sf::Vector2f newPosition;

//     // Logic to update token position based on smaller tile size
//     if (pos >= 0 && pos < 10) {  // Bottom row
//         newPosition = { 10 * tileSize - (pos * tileSize), 10 * tileSize };
//     } else if (pos >= 10 && pos < 20) {  // Left column
//         newPosition = { 0, 10 * tileSize - ((pos - 10) * tileSize) };
//     } else if (pos >= 20 && pos < 30) {  // Top row
//         newPosition = { (pos - 20) * tileSize, 0 };
//     } else if (pos >= 30 && pos < 40) {  // Right column
//         newPosition = { 10 * tileSize, (pos - 30) * tileSize };
//     }

//     // Set the new position for the player's token
//     playerTokens[playerIndex].setPosition(newPosition);
// }

// void Board::setMessage(const std::string& message) {
//     gameText.setString(message);  // Update the game message
// }

// void Board::createTile(const std::string& name, int price, TileType type, sf::Vector2f position, sf::Color color) {
//     Tile tile(name, price, type, position, color, font);  // Create a new tile with smaller size
//     tiles.push_back(tile);  // Add it to the vector of tiles
// }
#include "Board.hpp"
#include <iostream>

Board::Board() {
    // Load the Arial font
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    initializeBoard();

    // Initialize player tokens
    for (int i = 0; i < 8; i++) {
        sf::CircleShape token(7.0f);  // Smaller tokens, radius reduced to 7
        token.setFillColor(sf::Color::Red);  // You can change colors for different players
        token.setPosition(10 * 60.0f + i * 5, 10 * 60.0f);  // Initial position on "GO"
        playerTokens.push_back(token);
    }

    // Initialize the text box
    gameText.setFont(font);
    gameText.setCharacterSize(20);  // Adjusted font size
    gameText.setFillColor(sf::Color::White);
    gameText.setPosition(50, 780);  // Position below the board
    gameText.setString("Welcome to Monopoly!");
}

void Board::initializeBoard() {
    const float tileSize = 60.0f;  // Tile size

    // Define custom colors using RGB values
    sf::Color Pink(255, 192, 203);
    sf::Color Orange(255, 165, 0);
    sf::Color Yellow(255, 255, 0);
    sf::Color Grey(169, 169, 169);

    // Bottom row (right to left from GO to Jail)
    createTile("GO", 0, TileType::GO, {10 * tileSize, 10 * tileSize}, sf::Color::Green);  // Corner
    createTile("Mediterranean\nAve", 60, TileType::PROPERTY, {9 * tileSize, 10 * tileSize}, sf::Color::Magenta);
    createTile("Community\nChest", 0, TileType::COMMUNITY_CHEST, {8 * tileSize, 10 * tileSize}, sf::Color::White);
    createTile("Baltic\nAve", 60, TileType::PROPERTY, {7 * tileSize, 10 * tileSize}, sf::Color::Magenta);
    createTile("Income\nTax", 200, TileType::TAX, {6 * tileSize, 10 * tileSize}, sf::Color::White);
    createTile("Reading\nRailroad", 200, TileType::RAILROAD, {5 * tileSize, 10 * tileSize}, Grey);
    createTile("Oriental\nAve", 100, TileType::PROPERTY, {4 * tileSize, 10 * tileSize}, sf::Color::Cyan);
    createTile("Chance", 0, TileType::CHANCE, {3 * tileSize, 10 * tileSize}, sf::Color::White);
    createTile("Vermont\nAve", 100, TileType::PROPERTY, {2 * tileSize, 10 * tileSize}, sf::Color::Cyan);
    createTile("Connecticut\nAve", 120, TileType::PROPERTY, {1 * tileSize, 10 * tileSize}, sf::Color::Cyan);
    createTile("Jail /\nJust Visiting", 0, TileType::JAIL, {0 * tileSize, 10 * tileSize}, sf::Color::Red);  // Corner

    // Left column (bottom to top from Jail to Free Parking)
    createTile("St.\nCharles\nPlace", 140, TileType::PROPERTY, {0 * tileSize, 9 * tileSize}, Pink);
    createTile("Electric\nCompany", 150, TileType::UTILITY, {0 * tileSize, 8 * tileSize}, Grey);
    createTile("States\nAve", 140, TileType::PROPERTY, {0 * tileSize, 7 * tileSize}, Pink);
    createTile("Virginia\nAve", 160, TileType::PROPERTY, {0 * tileSize, 6 * tileSize}, Pink);
    createTile("Pennsylvania\nRailroad", 200, TileType::RAILROAD, {0 * tileSize, 5 * tileSize}, Grey);
    createTile("St.\nJames\nPlace", 180, TileType::PROPERTY, {0 * tileSize, 4 * tileSize}, Orange);
    createTile("Community\nChest", 0, TileType::COMMUNITY_CHEST, {0 * tileSize, 3 * tileSize}, sf::Color::White);
    createTile("Tennessee\nAve", 180, TileType::PROPERTY, {0 * tileSize, 2 * tileSize}, Orange);
    createTile("New\nYork\nAve", 200, TileType::PROPERTY, {0 * tileSize, 1 * tileSize}, Orange);
    createTile("Free\nParking", 0, TileType::FREE_PARKING, {0 * tileSize, 0 * tileSize}, Yellow);  // Corner

    // Top row (left to right from Free Parking to Marvin Gardens)
    createTile("Kentucky\nAve", 220, TileType::PROPERTY, {1 * tileSize, 0 * tileSize}, sf::Color::Red);
    createTile("Chance", 0, TileType::CHANCE, {2 * tileSize, 0 * tileSize}, sf::Color::White);
    createTile("Indiana\nAve", 220, TileType::PROPERTY, {3 * tileSize, 0 * tileSize}, sf::Color::Red);
    createTile("Illinois\nAve", 240, TileType::PROPERTY, {4 * tileSize, 0 * tileSize}, sf::Color::Red);
    createTile("B. & O.\nRailroad", 200, TileType::RAILROAD, {5 * tileSize, 0 * tileSize}, Grey);
    createTile("Atlantic\nAve", 260, TileType::PROPERTY, {6 * tileSize, 0 * tileSize}, sf::Color::Yellow);
    createTile("Ventnor\nAve", 260, TileType::PROPERTY, {7 * tileSize, 0 * tileSize}, sf::Color::Yellow);
    createTile("Water\nWorks", 150, TileType::UTILITY, {8 * tileSize, 0 * tileSize}, Grey);
    createTile("Marvin\nGardens", 280, TileType::PROPERTY, {9 * tileSize, 0 * tileSize}, sf::Color::Yellow);
    createTile("Go to\nJail", 0, TileType::GO_TO_JAIL, {10 * tileSize, 0 * tileSize}, sf::Color::Magenta);  // Corner

    // Right column (top to bottom from Go to Jail to Boardwalk)
    createTile("Pacific\nAve", 300, TileType::PROPERTY, {10 * tileSize, 1 * tileSize}, sf::Color::Green);
    createTile("North\nCarolina\nAve", 300, TileType::PROPERTY, {10 * tileSize, 2 * tileSize}, sf::Color::Green);
    createTile("Community\nChest", 0, TileType::COMMUNITY_CHEST, {10 * tileSize, 3 * tileSize}, sf::Color::White);
    createTile("Pennsylvania\nAve", 320, TileType::PROPERTY, {10 * tileSize, 4 * tileSize}, sf::Color::Green);
    createTile("Short\nLine", 200, TileType::RAILROAD, {10 * tileSize, 5 * tileSize}, Grey);
    createTile("Chance", 0, TileType::CHANCE, {10 * tileSize, 6 * tileSize}, sf::Color::White);
    createTile("Park\nPlace", 350, TileType::PROPERTY, {10 * tileSize, 7 * tileSize}, sf::Color::Blue);
    createTile("Boardwalk", 400, TileType::PROPERTY, {10 * tileSize, 8 * tileSize}, sf::Color::Blue);
    createTile("Luxury\nTax", 100, TileType::TAX, {10 * tileSize, 9 * tileSize}, sf::Color::White);
    createTile("GO", 0, TileType::GO, {10 * tileSize, 10 * tileSize}, sf::Color::Green);
}

void Board::createTile(const std::string& name, int price, TileType type, sf::Vector2f position, sf::Color color) {
    Tile tile(name, price, type, position, color, font);
    tiles.push_back(tile);
}

void Board::draw(sf::RenderWindow& window) {
    for (auto& tile : tiles) {
        tile.draw(window);
    }

    for (auto& token : playerTokens) {
        window.draw(token);
    }

    window.draw(gameText);
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

void Board::setMessage(const std::string& message) {
    gameText.setString(message);
}
