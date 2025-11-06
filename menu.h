#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
private:
    ///MENU INICIO
    sf::Text _text_inicio[4];
    //Pausa
    sf::Text _text_pausa[3];
    ///menu tienda
    sf::Font _font;
    sf::Text _text[3];
    sf::Text _text_items[3];
    int _seleccion;

    ///menu pelea
    sf::Font _font_pelea;
    sf::Text _text_pelea[2][2];
    int _fila;
    int _columna;
    ///General
    sf::Text _text_G[10];

public:
    ///tienda
    Menu();
    int getSeleccion() const;
    void mostrar(sf::RenderWindow& window);
    ///MENU INICIO
    int getSeleccion_inicio() const;
    void mostrar_inicio(sf::RenderWindow& window);
    ///PAUSA
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
    void mostrar_items(sf::RenderWindow& window);

    void arribaG(int x);
    void abajoG(int x);
};
