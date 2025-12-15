#pragma once
#include <SFML/Graphics.hpp>
#include "registro.h"

class Texto
{
private:
    sf::Font _font;
    sf::Text _text;
    sf::Text _text2;
    std::string _mens1;
    std::string _mens2;
public:
    Texto();

    void acercade(sf::RenderWindow& win);

    void updateR(Registros& reg);

    void registros(sf::RenderWindow& win);
};
