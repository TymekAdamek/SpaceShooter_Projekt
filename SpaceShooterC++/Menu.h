#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text titleText;//tytul
    sf::Text playText;
    sf::Text exitText;
};

void zapiszWynik(int punkty);

#endif