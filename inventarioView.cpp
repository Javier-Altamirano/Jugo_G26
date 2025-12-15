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

    Archivos arch("Aliados.dat","Enemigos.dat","Items.dat");
    _cantidadItems = arch.CantItemsG();
}
void InventarioView::mostrar_saldo(sf::RenderWindow& window, int x)
{
    if(x == 1)
    {
        _text.setPosition(80,415);
    }
    else if(x == 2)
    {
        _text.setPosition(490,345);
    }
    _text.setColor(sf::Color::Green);
    _text.setString("Dinero $ " + std::to_string(_inventario.getsaldo()));
    window.draw(_text);
    _seleccion = 0;
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
void InventarioView::arriba()
{
    if(_inventario.getCantidad() > 0 && _seleccion > 0)
        _seleccion--;
}
void InventarioView::abajo()
{
    int cant = _inventario.getCantidad();
    if(cant > 0 && _seleccion < cant - 1)
        _seleccion++;
}

int InventarioView::getSeleccion()
{
    return _seleccion;
}
void InventarioView::MostrarxPela(sf::RenderWindow& window)
{
    int y = 340;
    _sprite2.setPosition(140,200);
    window.draw(_sprite2);
    if(_inventario.getCantidad() == 0)
    {
        _text.setFillColor(sf::Color::White);
        _text.setPosition(360,300);
        _text.setString("VACIO..");
        window.draw(_text);
        return;
    }

    for (int i = 0; i < _inventario.getCantidad(); i++)
    {
        Item it = _inventario.getItem(i);

        _text.setString(
            std::string(it.getNombre()) +
            " x" +
            std::to_string(it.getCantidad())
        );

        _text.setFillColor(i == _seleccion ? sf::Color::Red : sf::Color::White);

        _text.setPosition(360, y);
        y += 25;

        window.draw(_text);
    }
}

