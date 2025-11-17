#include <iostream>
#include "inventarioView.h"
using namespace std;


InventarioView::InventarioView(Inventario& inv)
    :_inventario(inv)
{
    if(!_textura.loadFromFile("Texture/mClose.png"))
    {
        ///error
    }
    _sprite.setTexture(_textura);
    _sprite.setPosition(360,250);
    if(!_textura2.loadFromFile("Texture/mOpen.png"))
    {
        ///error
    }
    _sprite2.setTexture(_textura2);
    _sprite2.setPosition(360,250);
    if(!_font.loadFromFile("Font/square.ttf"))
    {
        ///error
    }
    _text.setFont(_font);
    _text.setCharacterSize(20);
}
void InventarioView::mostrar_saldo(sf::RenderWindow& window, int x)
{
    if(x == 1)
    {
        _text.setPosition(80,415);
    }
    else if(x == 2)
    {
        _text.setPosition(220,370);
    }
    _text.setColor(sf::Color::Green);
    _text.setString("Dinero $ " + std::to_string(_inventario.getsaldo()));
    window.draw(_text);
}

void InventarioView::MostrarInv(sf::RenderWindow& window)
{
    _text.setFillColor(sf::Color::White);
    int y = 340;
    if(_inventario.getCantidad() == 0)
    {
        _text.setString("VACIO...");
        _text.setPosition(575,340);
        window.draw(_text);
    }
    else
    {
        for(int i=0; i<_inventario.getCantidad(); i++)
        {
            Item it = _inventario.getItem(i);
            _text.setString(
                std::string(it.getNombre()) +
                " x" +
                std::to_string(it.getCantidad())
            );

            _text.setPosition(527, y);
            y += 25;
            window.draw(_text);
        }
    }
}
void InventarioView::maletinC(sf::RenderWindow& window)
{
    window.draw(_sprite);
}
void InventarioView::maletinO(sf::RenderWindow& window)
{
    window.draw(_sprite2);
}
