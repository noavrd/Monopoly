#include <SFML/Graphics.hpp>
#include "Board.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1100, 1100), "Monopoly Game");

    Board board;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        board.draw(window);
        window.display();
    }

    return 0;
}
