#include "Player.h"
#include <iostream> 

Player::Player() {
    speed = 6.0f;

    
    if (!texture.loadFromFile("assets/player.png")) {
        
        std::cout << "Error: assets/player.png not found!" << std::endl;
    }
    sprite.setTexture(texture);

    sprite.setScale(0.1f, 0.1f);//skalowanie bo statek jest za du¿y

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    sprite.setPosition(400.0f, 550.0f);

    
    if (!bulletTexture.loadFromFile("assets/bullet.png")) {
        std::cout << "Error: assets/bullet.png not found!" << std::endl;
    }
}

void Player::update() {
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-speed, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(speed, 0.0f);
    }

    
    if (sprite.getPosition().x < 0) sprite.setPosition(0, sprite.getPosition().y);
    if (sprite.getPosition().x > 800) sprite.setPosition(800, sprite.getPosition().y);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}


Bullet Player::shoot() {
    
    return Bullet(bulletTexture, sprite.getPosition().x, sprite.getPosition().y);
}

sf::Vector2f Player::getPosition() {
    return sprite.getPosition();
}

sf::FloatRect Player::getBounds() {
    return sprite.getGlobalBounds();
}
