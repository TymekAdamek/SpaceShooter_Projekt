#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// Prosty stan gry, żeby wykładowca widział architekturę
enum GameState { MENU, GAME };

int main() {
    // 1. Okno
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Shooter - PROTOTYP v0.1");
    window.setFramerateLimit(60);

    // 2. Ładowanie czcionki (Systemowej, żeby nie szukać plików)
    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        // Jakby nie znalazł ariala, spróbujmy inną, ale arial jest wszędzie
        std::cerr << "Blad czcionki" << std::endl;
        return -1;
    }

    // 3. Setup Menu
    sf::Text title("SPACE SHOOTER", font, 50);
    title.setPosition(200, 100);
    title.setFillColor(sf::Color::Cyan);

    sf::Text playText("1. GRAJ (Wcisnij Enter)", font, 30);
    playText.setPosition(250, 300);
    
    sf::Text exitText("2. WYJSCIE (Wcisnij Esc)", font, 30);
    exitText.setPosition(250, 350);

    sf::Text authorText("Build: Alpha 0.1", font, 15);
    authorText.setPosition(10, 570);
    authorText.setFillColor(sf::Color(100, 100, 100));

    // 4. Setup Gracza (Zastepczy kwadrat)
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(400, 500);
    float playerSpeed = 5.f;

    // Pociski
    struct Bullet { sf::RectangleShape shape; };
    std::vector<Bullet> bullets;

    GameState state = MENU;

    // --- PĘTLA GRY ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // Obsługa Menu
            if (state == MENU) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) state = GAME;
                    if (event.key.code == sf::Keyboard::Escape) window.close();
                }
            }
            // Obsługa Gry (Wyjście do menu)
            else if (state == GAME) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    state = MENU;
                }
                // Strzelanie
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                    Bullet b;
                    b.shape.setSize(sf::Vector2f(5.f, 15.f));
                    b.shape.setFillColor(sf::Color::Red);
                    b.shape.setPosition(player.getPosition().x + 22, player.getPosition().y);
                    bullets.push_back(b);
                }
            }
        }

        // --- LOGIKA ---
        if (state == GAME) {
            // Ruch gracza
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x > 0)
                player.move(-playerSpeed, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x < 750)
                player.move(playerSpeed, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y > 0)
                player.move(0, -playerSpeed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y < 550)
                player.move(0, playerSpeed);

            // Ruch pocisków
            for (size_t i = 0; i < bullets.size();) {
                bullets[i].shape.move(0, -10.f);
                if (bullets[i].shape.getPosition().y < 0) bullets.erase(bullets.begin() + i);
                else i++;
            }
        }

        // --- RYSOWANIE ---
        window.clear(sf::Color::Black);

        if (state == MENU) {
            window.draw(title);
            window.draw(playText);
            window.draw(exitText);
            window.draw(authorText);
        }
        else if (state == GAME) {
            window.draw(player);
            for (auto& b : bullets) window.draw(b.shape);
        }

        window.display();
    }

    return 0;
}
