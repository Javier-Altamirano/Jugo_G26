#pragma once
#include <SFML/Graphics.hpp>

class Fondos
{
private:
    sf::Texture _texture[7];
    sf::Sprite  _sprite[7];
public:
    Fondos();
    void fondos(sf::RenderWindow& window, int x);
};
