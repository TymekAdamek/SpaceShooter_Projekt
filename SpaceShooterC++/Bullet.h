#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::Sprite sprite;
    float speed;

public:
    
    Bullet(sf::Texture& tex, float startX, float startY);

    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    bool isOffScreen();
};

#endif#pragma once

