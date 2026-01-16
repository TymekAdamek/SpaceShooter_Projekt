#include "Enemy.h"
#include <cstdlib> 
#include <iostream>

Enemy::Enemy() {
    fallSpeed = 3.0f;

    
    if (!texture.loadFromFile("assets/enemy.png")) {
        std::cout << "Error: assets/enemy.png not found!" << std::endl;
    }
    sprite.setTexture(texture);

    sprite.setScale(0.1f, 0.1f);//rowniez skalujemy jak w player.cpp


    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    
    float randomX = static_cast<float>(rand() % 750 + 25); 
    sprite.setPosition(randomX, -50.0f); 
}

void Enemy::update() {
    sprite.move(0.0f, fallSpeed); 
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() {
    return sprite.getGlobalBounds();
}

bool Enemy::isOffScreen() {
    return (sprite.getPosition().y > 650.0f);
}
