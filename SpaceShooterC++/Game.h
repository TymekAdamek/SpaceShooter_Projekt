#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

//dodaje pliki Wiktora i Milosza
#include "Player.h"
#include "Enemy.h"
#include "Menu.h"
#include "Bullet.h"

class Game {
private:
    sf::RenderWindow* window;

    // T£O (Ruszaj¹ce siê morze)
    sf::Texture bgTexture;
    sf::Sprite bgSprite1;
    sf::Sprite bgSprite2;
    float bgSpeed;

    //OBIEKTy
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Bullet> bullets; // TU PRZECHOWUJEMY KULE
    Menu* menu;

    //LOGIKA
    float spawnTimer;
    float spawnTimerMax;

    // Cooldown strzelania
    float attackCooldown;
    float attackCooldownMax;

    int points;
    bool isGameOver;
    bool inMenu;

    void initWindow();
    void initTextures();
    void initPlayer();
    void initEnemies();
    void initMenu();

public:
    Game();
    virtual ~Game();

    void run();
    void update();
    void render();
    void updatePollEvents();
    void updateGame();
    void updateMenu();
    void endGame(); // Funkcja koñcz¹ca grê
};