#include <iostream>
#include "menu.h"
using namespace std;


Menu::Menu()
{
    if(!_font_pelea.loadFromFile("Font/square.ttf"))
    {
        ///error
        std::cout << "error\n";
    }
    ///TIENDA------------------------------------------------------------
    if(!_font.loadFromFile("Font/moab.ttf"))
    {
        ///error
    }
    std::string opciones[] = {"Comprar","Vender","Atras"};
    for(int i=0; i<3; i++)
    {
        _text[i].setFont(_font);
        _text[i].setString(opciones[i]);
        _text[i].setCharacterSize(28);
        _text[i].setPosition(280, 180 + i * 70);
    }
    _seleccion = 0;
    ///PELEA-------------------------------------------------------------
    std::string acciones[2][2] =
    {
        {"Atacar","Defender"},
        {"Mochila","Huir"}
    };
    for(int i=0; i<2; i++)
    {
        for(int l=0; l<2; l++)
        {
            _text_pelea[i][l].setFont(_font_pelea);
            _text_pelea[i][l].setString(acciones[i][l]);
            _text_pelea[i][l].setCharacterSize(30);
            _text_pelea[i][l].setPosition(400 + i * 200, 458 + l * 80);
        }
    }
    _fila = 0;
    _columna = 0;
}
///PELEA-------------------------------------------------------------
void Menu::arriba_pelea()
{
    if (_fila > 0) _fila--;
}
void Menu::abajo_pelea()
{
    if (_fila < 1) _fila++;
}
void Menu::izquierda()
{
    if (_columna > 0) _columna--;
}
void Menu::derecha()
{
    if (_columna < 1) _columna++;
}

int Menu::getFila() const
{
    return _fila;
}
int Menu::getColumna() const
{
    return _columna;
}

void Menu::mostrar_pelea(sf::RenderWindow& window)
{
    for(int i=0; i<2; i++)
    {
        for(int l=0; l<2; l++)
        {
            _text_pelea[i][l].setFillColor((i == _columna && l == _fila) ? sf::Color::Yellow : sf::Color::White);
            window.draw(_text_pelea[i][l]);
        }
    }
}
///TIENDA---------------------------------------------------
void Menu::arriba()
{
    _seleccion --;
    if(_seleccion < 0)
    {
        _seleccion = 2;
    }
}
void Menu::abajo()
{
    _seleccion ++;
    if(_seleccion > 2)
    {
        _seleccion = 0;
    }
}
int Menu::getSeleccion() const
{
    return _seleccion;
}
void Menu::mostrar(sf::RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        _text[i].setFillColor(i == _seleccion ? sf::Color::Red : sf::Color::Black);
        window.draw(_text[i]);
    }
}
