#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("assets/font.ttf")) {
        std::cout << "BLAD: Nie znaleziono czcionki!" << std::endl;
    }

    // --- TYTUŁ: PIRATE SHOOTER ---
    titleText.setFont(font);
    titleText.setString("PIRATE SHOOTER");
    titleText.setCharacterSize(50); // Trochę mniejszy, żeby się zmieścił
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setStyle(sf::Text::Bold);

    // Centrowanie tytułu
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
        titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 150));

    // --- PRZYCISK: PLAY ---
    playText.setFont(font);
    playText.setString("PLAY - Wcisnij Enter");
    playText.setCharacterSize(30); // Dopasowany rozmiar
    playText.setFillColor(sf::Color::White);

    sf::FloatRect playBounds = playText.getLocalBounds();
    playText.setOrigin(playBounds.left + playBounds.width / 2.0f,
        playBounds.top + playBounds.height / 2.0f);
    playText.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));

    // --- PRZYCISK: EXIT ---
    exitText.setFont(font);
    exitText.setString("EXIT - Wcisnij Esc");
    exitText.setCharacterSize(30);
    exitText.setFillColor(sf::Color::White);

    sf::FloatRect exitBounds = exitText.getLocalBounds();
    exitText.setOrigin(exitBounds.left + exitBounds.width / 2.0f,
        exitBounds.top + exitBounds.height / 2.0f);
    exitText.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 60));
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(titleText); //tytuł
    window.draw(playText);
    window.draw(exitText);
}

void zapiszWynik(int punkty) {
    std::ofstream plik("wyniki.txt", std::ios::app);
    if (plik.is_open()) {
        std::string s = std::to_string(punkty);
        for (size_t i = 0; i < s.length(); i++) s[i] += 1;
        plik << s << std::endl;
        plik.close();
    }
}