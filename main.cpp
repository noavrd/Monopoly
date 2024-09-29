#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>

int main() {
    int numPlayers;
    std::cout << "Enter number of players (2-8): ";
    std::cin >> numPlayers;

    if (numPlayers < 2 || numPlayers > 8) {
        std::cout << "Invalid number of players!" << std::endl;
        return 1;
    }

    Game game(numPlayers);

    // Create the window for the game with smaller dimensions
    sf::RenderWindow window(sf::VideoMode(900, 1000), "Monopoly Game");  // Adjusted window size to fit board and message

    bool gameInProgress = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle game logic
        if (gameInProgress && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            game.takeTurn();  // Roll dice and process the player's turn
            gameInProgress = !game.isGameOver();
        }

        // Clear the window with a white background
        window.clear(sf::Color::White);  // Set the background to white

        // Draw the game elements (board, tiles, players, etc.)
        game.updateGraphics(window);

        // Display the window contents
        window.display();
    }

    if (game.isGameOver()) {
        std::cout << "Game Over!" << std::endl;
    }

    return 0;
}
