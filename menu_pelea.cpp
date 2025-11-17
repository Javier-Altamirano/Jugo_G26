#include <iostream>
#include "menu_pelea.h"
using namespace std;


MenuPelea::MenuPelea()
{
    if(!_font.loadFromFile("Font/square.ttf"))
    {
        ///error
    }
    std::string acciones[2][2] =
    {
        {"Atacar","Hab. Especial"},
        {"Inventario","Huir"}
    };
    for(int x=0; x<2; x++)
    {
        for(int y=0; y<2; y++)
        {
            _text[x][y].setFont(_font);
            _text[x][y].setString(acciones[x][y]);
            _text[x][y].setCharacterSize(20);
            _text[x][y].setPosition(400 + x * 200, 458 + y * 80);
        }
    }
    _resultado.setFont(_font);
    _resultado.setPosition(300,300);
    _resultado.setString("GANASTE");
    _fila = 0;
    _columna = 0;
}
void MenuPelea::arriba()
{
    if(_fila > 0)
        _fila--;
}
void MenuPelea::abajo()
{
    if(_fila < 1)
        _fila++;
}
void MenuPelea::izquierda()
{
    if(_columna > 0)
        _columna--;
}
void MenuPelea::derecha()
{
    if(_columna < 1)
        _columna++;
}

int MenuPelea::getFila()
{
    return _fila;
}
int MenuPelea::getColumna()
{
    return _columna;
}

void MenuPelea::mostrarPelea(sf::RenderWindow& window)
{
    for(int x=0; x<2; x++)
    {
        for(int y=0; y<2; y++)
        {
            _text[x][y].setFillColor((x == _columna && y == _fila) ? sf::Color::Red : sf::Color::Black);
            window.draw(_text[x][y]);
        }
    }
}
void MenuPelea::reset()
{
    _fila = 0;
    _columna = 0;
}

void MenuPelea::resultadoP(sf::RenderWindow& window)
{
    window.draw(_resultado);
}
