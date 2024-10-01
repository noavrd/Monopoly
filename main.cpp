#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>

using namespace std;

int main() {
    int numPlayers;
    cout << "Enter number of players (2-8): ";
    cin >> numPlayers;

    if (numPlayers < 2 || numPlayers > 8) {
        cout << "Invalid number of players!" << endl;
        return 1;
    }

    Game game(numPlayers);
    bool turnTaken = false;  

    // Create the window for the game
    sf::RenderWindow window(sf::VideoMode(700, 700), "Monopoly Game");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle spacebar input for rolling dice and taking turns
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !turnTaken) {
            game.takeTurn();  // Only the current player will take their turn
            turnTaken = true;  // Mark that the turn has been taken
        }

        // Reset the flag when the spacebar is released
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            turnTaken = false;  // Allow another turn when spacebar is pressed again
        }

        // Update the graphics after each turn
        game.updateGraphics(window);

        // Check for the game over condition
        if (game.isGameOver()) {
            cout << "Game Over!" << endl;
            window.close();
        }
    }

    return 0;
}
