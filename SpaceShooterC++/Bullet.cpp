#include "Bullet.h"

Bullet::Bullet(sf::Texture& tex, float startX, float startY) {
    sprite.setTexture(tex);
    speed = 10.0f;

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    sprite.setPosition(startX, startY);
}

void Bullet::update() {
    sprite.move(0.0f, -speed);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Bullet::getBounds() {
    return sprite.getGlobalBounds();
}

bool Bullet::isOffScreen() {
    return (sprite.getPosition().y < -50.0f);
}