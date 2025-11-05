#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
private:
    ///menu tienda
    sf::Font _font;
    sf::Text _text[3];
    int _seleccion;
    ///menu pelea
    sf::Font _font_pelea;
    sf::Text _text_pelea[2][2];
    int _fila;
    int _columna;

public:
    ///tienda
    Menu();
    void arriba();
    void abajo();
    int getSeleccion() const;
    void mostrar(sf::RenderWindow& window);

    ///pelea
    ///movimiento
    void arriba_pelea();
    void abajo_pelea();
    void izquierda();
    void derecha();
    ///saber seleccion
    int getFila() const;
    int getColumna() const;
    ///dibujar y colorear
    void mostrar_pelea(sf::RenderWindow& window);
};
