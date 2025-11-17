#pragma once
#include "inventario.h"
#include <SFML/Graphics.hpp>

class InventarioView
{
private:
    Inventario& _inventario;
    sf::Text _text;
    sf::Font _font;

    sf::Texture _textura;
    sf::Sprite _sprite;

    sf::Texture _textura2;
    sf::Sprite _sprite2;
public:
    InventarioView(Inventario& inv);

    void MostrarInv(sf::RenderWindow& window);

    void mostrar_saldo(sf::RenderWindow& window, int x);

    void maletinC(sf::RenderWindow& window);
    void maletinO(sf::RenderWindow& window);
};
