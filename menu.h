#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
private:
    ///MENU INICIO
    sf::Text _text_inicio[5];
    int _seleccion_inicio;

    //Pausa
    sf::Text _text_pausa[3];
    int _seleccion_pausa;

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
    ///MENU INICIO
    void arriba_inicio();
    void abajo_inicio();
    int getSeleccion_inicio() const;
    void mostrar_inicio(sf::RenderWindow& window);
    ///PAUSA
    void arriba_pausa();
    void abajo_pausa();
    int getSeleccion_pausa() const;
    void mostrar_pausa(sf::RenderWindow& window);
    void posicion(int x, int y);
    ///PELEA
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
