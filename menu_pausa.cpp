#include <iostream>
#include "menu_pausa.h"
using namespace std;


MenuPausa::MenuPausa()
{
    if(!_font.loadFromFile("Font/square.ttf"))
    {
        ///error
    }
    std::string opciones [] {"CONTINUAR","INVENTARIO","SALIAR AL INICIO"};
    for(int i=0; i<3; i++)
    {
        _text[i].setFont(_font);
        _text[i].setString(opciones[i]);
        _text[i].setCharacterSize(20);
        _text[i].setPosition(70,130 + i * 70);
    }
    if(!_textura.loadFromFile("Texture/menu1.png"));
    _sprite.setTexture(_textura);
    _sprite.setPosition(50,50);
    _seleccion = 0;
}
///Move
void MenuPausa::arriva()
{
    if(_seleccion > 0)
    {
        _seleccion--;
    }
}
void MenuPausa::abajo()
{
    if(_seleccion < 2)
    {
        _seleccion++;
    }
}
///
int MenuPausa::getseleccion()
{
    return _seleccion;
}
///texto
void MenuPausa::mostrarPausa(sf::RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        _text[i].setFillColor(i == _seleccion ? sf::Color::Red : sf::Color::White);
        window.draw(_text[i]);
    }
}

///fodo
void MenuPausa::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    target.draw(_sprite, states);
}
