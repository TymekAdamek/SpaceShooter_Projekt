#include "Menu.h"

Menu::Menu(float width, float height) {
    // Ładowanie czcionki z określonej ścieżki
    if (!font.loadFromFile("assets/font.ttf")) {
        // W przypadku błędu SFML wypisze komunikat w konsoli
    }

    // Konfiguracja napisu PLAY
    playText.setFont(font);
    playText.setString("PLAY - Wcisnij Enter");
    playText.setCharacterSize(40);
    playText.setFillColor(sf::Color::White);
    
    // Centrowanie tekstu PLAY
    sf::FloatRect playBounds = playText.getLocalBounds();
    playText.setOrigin(playBounds.left + playBounds.width / 2.0f, 
                       playBounds.top + playBounds.height / 2.0f);
    playText.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 50));

    // Konfiguracja napisu EXIT
    exitText.setFont(font);
    exitText.setString("EXIT - Wcisnij Esc");
    exitText.setCharacterSize(40);
    exitText.setFillColor(sf::Color::White);
    
    // Centrowanie tekstu EXIT
    sf::FloatRect exitBounds = exitText.getLocalBounds();
    exitText.setOrigin(exitBounds.left + exitBounds.width / 2.0f, 
                       exitBounds.top + exitBounds.height / 2.0f);
    exitText.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 50));
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(playText);
    window.draw(exitText);
}

void zapiszWynik(int punkty) {
    std::ofstream plik("wyniki.txt", std::ios::app);
    if (plik.is_open()) {
        std::string s = std::to_string(punkty);
        
        // Szyfrowanie: dodanie +1 do wartości ASCII każdego znaku
        for (int i = 0; i < s.length(); i++) {
            s[i] += 1;
        }
        
        plik << s << std::endl;
        plik.close();
    }
}
