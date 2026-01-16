#include "Game.h"

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "PIRATE SHOOTER - BITWA MORSKA");
    this->window->setFramerateLimit(60);
}

void Game::initTextures() {
    // Wczytanie t³a
    if (!this->bgTexture.loadFromFile("assets/background.jpg")) {
        std::cout << "BLAD: Nie znaleziono assets/background.jpg" << std::endl;
    }

    //NAPRAWA ROZJECHANEGO T£A
    // pobieramy rozmiar obrazka z pliku
    sf::Vector2u textureSize = this->bgTexture.getSize();

    float scaleX = 800.0f / textureSize.x;
    float scaleY = 600.0f / textureSize.y;

    this->bgSprite1.setTexture(this->bgTexture);
    this->bgSprite2.setTexture(this->bgTexture);

    // tlo wypelnia ekran
    this->bgSprite1.setScale(scaleX, scaleY);
    this->bgSprite2.setScale(scaleX, scaleY);

    // Ustawienie drugiego t³a nad pierwszym
    this->bgSprite2.setPosition(0, -600.f);

    this->bgSpeed = 2.0f; // Prêdkoœæ nurtu
}

void Game::initPlayer() {
    this->player = new Player(); // konstruktor Wiktora

    // Inicjalizacja cooldownu strzelania (¿eby nie strzelaæ ci¹giem)
    this->attackCooldownMax = 15.f;
    this->attackCooldown = this->attackCooldownMax;
}

void Game::initEnemies() {
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}

void Game::initMenu() {
    this->menu = new Menu(this->window->getSize().x, this->window->getSize().y); // Kod Mi³osza
}

// konstruktor/destruktor

Game::Game() {
    this->initWindow();
    this->initTextures();
    this->initPlayer();
    this->initEnemies();
    this->initMenu();

    this->points = 0;
    this->isGameOver = false;
    this->inMenu = true;
}

Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->menu;
    for (auto* i : this->enemies) delete i;
    // Wektor bullets czyœci siê sam, bo nie przechowuje wskaŸników
}

// --- PÊTLA ---

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
    else if (!this->isGameOver) {
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
    // obs³uga menu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        this->inMenu = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        this->window->close();
    }
}

void Game::updateGame() {
    // 1. RUCH WODY
    this->bgSprite1.move(0, this->bgSpeed);
    this->bgSprite2.move(0, this->bgSpeed);

    if (this->bgSprite1.getPosition().y >= 600) this->bgSprite1.setPosition(0, -600);
    if (this->bgSprite2.getPosition().y >= 600) this->bgSprite2.setPosition(0, -600);

    // 2. GRACZ
    this->player->update();

    // INTEGRACJA KODU WIKTORA
    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->attackCooldown >= this->attackCooldownMax) {
        // Pobieramy kulê od gracza i wrzucamy do naszego wektora w Game
        this->bullets.push_back(this->player->shoot());
        this->attackCooldown = 0.f; // Reset licznika
    }

    // 3. AKTUALIZACJA POCISKÓW
    for (size_t i = 0; i < this->bullets.size(); ++i) {
        this->bullets[i].update(); // Metoda z Bullet.cpp

        // Usuwanie kul poza ekranem
        if (this->bullets[i].isOffScreen()) {
            this->bullets.erase(this->bullets.begin() + i);
            i--;
        }
    }

    // 4. WROGOWIE
    this->spawnTimer += 1.f;
    if (this->spawnTimer >= this->spawnTimerMax) {
        this->enemies.push_back(new Enemy()); // Konstruktor Enemy sam losuje pozycjê
        this->spawnTimer = 0.f;
    }

    for (size_t i = 0; i < this->enemies.size(); ++i) {
        this->enemies[i]->update();

        // A) Kolizja Gracz vs Wróg
        if (this->player->getBounds().intersects(this->enemies[i]->getBounds())) {
            this->endGame(); // Koniec gry
        }

        // B) Kolizja Kula vs Wróg
        bool enemyHit = false;
        for (size_t k = 0; k < this->bullets.size(); ++k) {
            if (this->bullets[k].getBounds().intersects(this->enemies[i]->getBounds())) {

                this->points += 10;

                if (this->spawnTimerMax > 15.f)//przyspieszenie gry
                    this->spawnTimerMax -= 0.5f;

                // Usuwamy kulê i wroga
                this->bullets.erase(this->bullets.begin() + k);
                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                enemyHit = true;
                i--; // Cofamy licznik wrogów
                break;
            }
        }
        if (enemyHit) continue;

        // C) Usuwanie wroga poza ekranem
        if (this->enemies[i]->isOffScreen()) {
            delete this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
            i--;
        }
    }
}

void Game::endGame() {
    std::cout << "GAME OVER! Wynik: " << this->points << std::endl;
    // Wywo³anie funkcji globalnej z pliku Menu.cpp
    zapiszWynik(this->points);
    this->isGameOver = true;
    this->window->close();
}

void Game::render() {
    this->window->clear();

    // Rysowanie t³a
    this->window->draw(this->bgSprite1);
    this->window->draw(this->bgSprite2);

    if (this->inMenu) {
        this->menu->draw(*this->window); // draw() od Mi³osza
    }
    else {
        this->player->draw(*this->window); // draw() od Wiktora

        for (auto& bullet : this->bullets) {
            bullet.draw(*this->window); // draw() od Wiktora (Bullet)
        }

        for (auto* enemy : this->enemies) {
            enemy->draw(*this->window); // draw() od Wiktora (Enemy)
        }
    }

    this->window->display();
}

void Game::saveScore() {
    // Otwieramy plik
    std::ofstream file("wyniki.txt", std::ios::app);

    if (file.is_open()) {
        std::string s = "PIRAT - WYNIK: " + std::to_string(this->points);

        // Proste szyfrowanie
        // Przesuwamy ka¿dy znak o +1
        for (size_t i = 0; i < s.length(); i++) {
            s[i] += 1;
        }

        file << s << std::endl;
        file.close();
    }
}