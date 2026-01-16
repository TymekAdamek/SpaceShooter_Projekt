#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

class Menu {
public:
    // Konstruktor przyjmujący wymiary okna do centrowania napisów
    Menu(float width, float height);
    
    // Metoda rysująca napisy w oknie
    void draw(sf::RenderWindow &window);

private:
    sf::Font font;
    sf::Text playText;
    sf::Text exitText;
};

// Funkcja zapisująca zaszyfrowany wynik
void zapiszWynik(int punkty);

#endif
