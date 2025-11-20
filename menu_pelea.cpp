#include <iostream>
#include "menu_pelea.h"
using namespace std;


MenuPelea::MenuPelea()
{
    if(!_font.loadFromFile("Font/square.ttf"))
    {
        ///error
    }
    std::string acciones[]{"Atacar","Hab. Especial","Inventario","Huir"};
    for(int x=0; x<4; x++)
    {
        _text[x].setFont(_font);
        _text[x].setString(acciones[x]);
        _text[x].setCharacterSize(20);
        _text[x].setPosition(590, 415 + x * 40);
    }
    _resultado.setFont(_font);
    _resultado.setPosition(300,300);
    _resultado.setString("");
    _seleccion = 0;
    if(!_texture.loadFromFile("Texture/espada.png"))
    {
        ///error
    }
    _sprite.setTexture(_texture);

}
void MenuPelea::arriba()
{
    if(_seleccion > 0)
        _seleccion--;
}
void MenuPelea::abajo()
{
    if(_seleccion < 3)
        _seleccion++;
}
int MenuPelea::getSeleccion()
{
    return _seleccion;
}
void MenuPelea::mostrarPelea(sf::RenderWindow& window)
{
    for(int x=0; x<4; x++)
    {
        _text[x].setFillColor(x == _seleccion ? sf::Color::Blue : sf::Color::White);
        sf::Vector2f pos = _text[_seleccion].getPosition();
        _sprite.setPosition(pos.x - 100, pos.y);
        window.draw(_sprite);
        window.draw(_text[x]);
    }
}
void MenuPelea::reset()
{
    _seleccion = 0;
}

void MenuPelea::resultadoP(sf::RenderWindow& window, int x)
{
    if(x == 1)
    {
        _resultado.setString("GANASTE!");
    }
    else if(x == 0)
    {
        _resultado.setString("PERDISTE!");
    }
    window.draw(_resultado);
}
