#pragma once
#include "inventario.h"
#include "archivos.h"
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
    int _cantidadItems;
    int  _seleccion;
public:
    InventarioView(Inventario& inv);

    void arriba();
    void abajo();
    int getSeleccion();

    void MostrarInv(sf::RenderWindow& window);

    void mostrar_saldo(sf::RenderWindow& window, int x);

    void maletinC(sf::RenderWindow& window);
    void maletinO(sf::RenderWindow& window);
    void MostrarxPela(sf::RenderWindow& window);
};
