#include <SFML/Graphics.hpp>
<<<<<<< HEAD
=======
#include <vector>
#include <iostream>

enum GameState { MENU, GAME };
>>>>>>> 84dc2a7 (...)

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Shooter - TEST");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}