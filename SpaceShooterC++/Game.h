#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "Menu.h"
#include "Bullet.h"

class Game {
private:
    sf::RenderWindow* window;

    // T£O
    sf::Texture bgTexture;
    sf::Sprite bgSprite1;
    sf::Sprite bgSprite2;
    float bgSpeed;

    // GUI i AUDIO
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Music bgMusic;

    // OBIEKTY
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Bullet> bullets;
    Menu* menu;

    // LOGIKA
    float spawnTimer;
    float spawnTimerMax;

    // Cooldown strzelania
    float attackCooldown;
    float attackCooldownMax;

    int points;
    bool isGameOver;
    bool inMenu;

    // Funkcje inicjalizuj¹ce
    void initWindow();
    void initTextures();
    void initGUI();
    void initPlayer();
    void initEnemies();
    void initMenu();
    void saveScore();

public:
    Game();
    virtual ~Game();

    void run();
    void update();
    void render();
    void updatePollEvents();
    void updateGame();
    void updateMenu();
    void endGame();
};