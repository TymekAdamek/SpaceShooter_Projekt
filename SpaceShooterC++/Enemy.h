#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float fallSpeed;

public:
    Enemy(); 

    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    bool isOffScreen();
};

#endif
