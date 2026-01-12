#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture bulletTexture; 
    float speed;

public:
    Player(); 

    void update(); 
    void draw(sf::RenderWindow& window);

    
    Bullet shoot();

    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
};

#endif
