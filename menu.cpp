#include <iostream>
#include "menu.h"
using namespace std;


Menu::Menu()
{
    if(!_font.loadFromFile("Font/square.ttf"))
    {
        ///error
        std::cout << "error\n";
    }
    ///INICIO------------------------------------------------------------
    std::string opciones_ini[] = {"NUEVA PARTIDA","CONTINUAR","ACERCA DE","REGISTROS","SALIR"};
    for(int i=0; i<5; i++)
    {
        _text_inicio[i].setFont(_font);
        _text_inicio[i].setString(opciones_ini[i]);
        _text_inicio[i].setCharacterSize(28);
        _text_inicio[i].setPosition(280, 180 + i * 70);
    }
    _seleccion = 0;
}
///INICIO---------------------------------------------------
void Menu::mostrar_inicio(sf::RenderWindow& window)
{
    for (int i = 0; i < 5; i++)
    {
        _text_inicio[i].setFillColor(i == _seleccion ? sf::Color::Red : sf::Color::White);
        window.draw(_text_inicio[i]);
    }
}
///MOVIMIENTO
void Menu::arriba()
{
    if(_seleccion > 0)
    {
        _seleccion--;
    }
    else
    {
        _seleccion = 4;
    }
}
void Menu::abajo()
{
    if(_seleccion < 4)
    {
        _seleccion++;
    }
    else
    {
        _seleccion = 0;
    }
}
int Menu::getSeleccion() const
{
    return _seleccion;
}
