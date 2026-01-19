#include "Game.h"

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "PIRATE SHOOTER - BITWA MORSKA");
    this->window->setFramerateLimit(60);
}

void Game::initTextures() {
    if (!this->bgTexture.loadFromFile("assets/background.jpg")) {
        std::cout << "BLAD: Nie znaleziono assets/background.jpg" << std::endl;
    }

    sf::Vector2u textureSize = this->bgTexture.getSize();

    float scaleX = 800.0f / textureSize.x;
    float scaleY = 600.0f / textureSize.y;

    this->bgSprite1.setTexture(this->bgTexture);
    this->bgSprite2.setTexture(this->bgTexture);

    this->bgSprite1.setScale(scaleX, scaleY);
    this->bgSprite2.setScale(scaleX, scaleY);

    this->bgSprite2.setPosition(0, -600.f);

    this->bgSpeed = 2.0f;
}

void Game::initGUI() {
    if (!this->font.loadFromFile("assets/font.ttf")) {
        std::cout << "BLAD: Nie znaleziono assets/font.ttf" << std::endl;
    }

    // Punkty
    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(24);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setPosition(10.f, 10.f);
    this->scoreText.setString("PUNKTY: 0");

    // Game Over
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("GAME OVER");

    sf::FloatRect textRect = this->gameOverText.getLocalBounds();
    this->gameOverText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    this->gameOverText.setPosition(400.f, 300.f);
}

void Game::initPlayer() {
    this->player = new Player();
    this->attackCooldownMax = 15.f;
    this->attackCooldown = this->attackCooldownMax;
}

void Game::initEnemies() {
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}

void Game::initMenu() {
    this->menu = new Menu(this->window->getSize().x, this->window->getSize().y);
}

Game::Game() {
    this->initWindow();
    this->initTextures();
    this->initPlayer();
    this->initEnemies();
    this->initMenu();
    this->initGUI();

    if (this->bgMusic.openFromFile("assets/music.ogg")) {
        this->bgMusic.setLoop(true);
        this->bgMusic.setVolume(20.f);
        this->bgMusic.play();
    }

    this->points = 0;
    this->isGameOver = false;
    this->inMenu = true;
}

Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->menu;
    for (auto* i : this->enemies) delete i;
}

void Game::run() {
    while (this->window->isOpen()) {
        this->update();
        this->render();
    }
}

void Game::update() {
    this->updatePollEvents();

    if (this->inMenu) {
        this->updateMenu();
    }
    else if (this->isGameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            this->window->close();
        }
    }
    else {
        this->updateGame();
    }
}

void Game::updatePollEvents() {
    sf::Event e;
    while (this->window->pollEvent(e)) {
        if (e.type == sf::Event::Closed) this->window->close();
    }
}

void Game::updateMenu() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        this->inMenu = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        this->window->close();
    }
}

void Game::updateGame() {
    this->scoreText.setString("PUNKTY: " + std::to_string(this->points));

    this->bgSprite1.move(0, this->bgSpeed);
    this->bgSprite2.move(0, this->bgSpeed);

    if (this->bgSprite1.getPosition().y >= 600) this->bgSprite1.setPosition(0, -600);
    if (this->bgSprite2.getPosition().y >= 600) this->bgSprite2.setPosition(0, -600);

    this->player->update();

    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->attackCooldown >= this->attackCooldownMax) {
        this->bullets.push_back(this->player->shoot());
        this->attackCooldown = 0.f;
    }

    for (size_t i = 0; i < this->bullets.size(); ++i) {
        this->bullets[i].update();

        if (this->bullets[i].isOffScreen()) {
            this->bullets.erase(this->bullets.begin() + i);
            i--;
        }
    }

    this->spawnTimer += 1.f;
    if (this->spawnTimer >= this->spawnTimerMax) {
        this->enemies.push_back(new Enemy());
        this->spawnTimer = 0.f;
    }

    for (size_t i = 0; i < this->enemies.size(); ++i) {
        this->enemies[i]->update();

        sf::FloatRect playerBounds = this->player->getBounds();
        sf::FloatRect enemyBounds = this->enemies[i]->getBounds();

        //Zmniejszamy hitbox gracza dla lepszej rozgrywki
        playerBounds.left += playerBounds.width * 0.25f;
        playerBounds.width *= 0.5f;
        playerBounds.top += playerBounds.height * 0.25f;
        playerBounds.height *= 0.5f;

        // zmniejszamy hitbox wroga
        enemyBounds.left += enemyBounds.width * 0.1f;
        enemyBounds.width *= 0.8f;
        enemyBounds.top += enemyBounds.height * 0.1f;
        enemyBounds.height *= 0.8f;

        // Sprawdzamy kolizjê mniejszych prostok¹tów
        if (playerBounds.intersects(enemyBounds)) {
            this->endGame();
        }

        bool enemyHit = false;
        for (size_t k = 0; k < this->bullets.size(); ++k) {
            // tutaj te¿ u¿ywamy zmniejszonego hitboxa wroga, ¿eby ³atwiej by³o trafiæ
            if (this->bullets[k].getBounds().intersects(enemyBounds)) {

                this->points += 10;

                if (this->spawnTimerMax > 15.f)
                    this->spawnTimerMax -= 0.5f;

                this->bullets.erase(this->bullets.begin() + k);
                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                enemyHit = true;
                i--;
                break;
            }
        }
        if (enemyHit) continue;

        if (this->enemies[i]->isOffScreen()) {
            delete this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
            i--;
        }
    }
}

void Game::endGame() {
    std::cout << "GAME OVER! Wynik: " << this->points << std::endl;
    this->saveScore();
    this->isGameOver = true;
}

void Game::render() {
    this->window->clear();

    this->window->draw(this->bgSprite1);
    this->window->draw(this->bgSprite2);

    if (this->inMenu) {
        this->menu->draw(*this->window);
    }
    else {
        this->player->draw(*this->window);

        for (auto& bullet : this->bullets) {
            bullet.draw(*this->window);
        }

        for (auto* enemy : this->enemies) {
            enemy->draw(*this->window);
        }

        this->window->draw(this->scoreText);

        if (this->isGameOver) {
            this->window->draw(this->gameOverText);
        }
    }

    this->window->display();
}

void Game::saveScore() {
    std::ofstream file("wyniki.txt", std::ios::app);

    if (file.is_open()) {
        std::string s = "PIRAT - WYNIK: " + std::to_string(this->points);

        for (size_t i = 0; i < s.length(); i++) {
            s[i] += 1;
        }

        file << s << std::endl;
        file.close();
    }
}