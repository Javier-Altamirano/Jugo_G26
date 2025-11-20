#pragma once
#include <SFML/Graphics.hpp>

class MenuPelea
{
private:
    sf::Font _font;
    sf::Text _text[4];
    sf::Text _resultado;
    int _seleccion;

    sf::Texture _texture;
    sf::Sprite _sprite;

public:
    MenuPelea();
    void arriba();
    void abajo();
    void izquierda();
    void derecha();

    int getSeleccion();

    void reset();

    void mostrarPelea(sf::RenderWindow& window);

    void resultadoP(sf::RenderWindow& window,int x);
};
