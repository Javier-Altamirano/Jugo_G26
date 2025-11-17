#pragma once
#include <SFML/Graphics.hpp>

class MenuPelea
{
private:
    sf::Font _font;
    sf::Text _text[2][2];
    sf::Text _resultado;
    int _fila;
    int _columna;

public:
    MenuPelea();
    void arriba();
    void abajo();
    void izquierda();
    void derecha();

    int getFila();
    int getColumna();

    void reset();

    void mostrarPelea(sf::RenderWindow& window);

    void resultadoP(sf::RenderWindow& window);
};
