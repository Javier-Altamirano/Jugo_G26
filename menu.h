#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
private:
    ///MENU INICIO
    sf::Text _text_inicio[4];
    sf::Font _font;
    int _seleccion;
public:
    Menu();
    int getSeleccion() const;
    ///MENU INICIO
    void mostrar_inicio(sf::RenderWindow& window);

    void arriba();
    void abajo();
};
