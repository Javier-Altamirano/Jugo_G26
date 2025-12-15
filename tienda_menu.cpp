#include <iostream>
#include "tienda_menu.h"
using namespace std;


TiendaMenu::TiendaMenu()
{
    if(!_textura.loadFromFile("Texture/fondomenu.png"))
    {
        ///error
    }
    _sprite.setTexture(_textura);
    _sprite.setPosition(480,75);
    ///---------------------------------------///
    if(!_font.loadFromFile("Font/square.ttf"))
    {
        ///error
    }
    ///INICIO DE TIENDA
    std::string opciones[] {"COMPRAR","VENDER","RECUPERAR EQ.","SALIR"};
    for(int i=0; i<4; i++)
    {
        _text1[i].setString(opciones[i]);
        _text1[i].setFont(_font);
        _text1[i].setCharacterSize(25);
        _text1[i].setPosition(500, 130 + i * 60);
    }
    ///COMPRA
    Archivos arch("Aliados.dat","Enemigos.dat","Items.dat");
    _itemsTotalse = nullptr;
    _cantidadItems = arch.CantItemsG();
    if(_cantidadItems > 0)
    {
        _itemsTotalse = new Item[_cantidadItems];
        arch.LeerIT(_itemsTotalse, _cantidadItems);
    }
    _tam = _cantidadItems + 1;
    _textItems.resize(_tam);
    _textItemsV.resize(_tam);
    std::string nombre;
    int compra;
    int venta;
    std::string mens1, mens2;
    for(int i=0; i<_cantidadItems; i++)
    {
        nombre = _itemsTotalse[i].getNombre();
        compra = _itemsTotalse[i].getPrecioCompra();
        venta = _itemsTotalse[i].getPrecioVenta();
        mens1 = nombre + " <> $" + std::to_string(compra);
        mens2 = nombre + " <> $" + std::to_string(venta);
        ///
        _textItems[i].setFont(_font);
        _textItems[i].setString(mens1);
        _textItems[i].setCharacterSize(20);
        _textItems[i].setPosition(500, 130 + i * 60);
        ///
        _textItemsV[i].setFont(_font);
        _textItemsV[i].setString(mens2);
        _textItemsV[i].setCharacterSize(20);
        _textItemsV[i].setPosition(500, 130 + i * 60);
    }
    _textItems[_cantidadItems].setFont(_font);
    _textItems[_cantidadItems].setString("ATRAS");
    _textItems[_cantidadItems].setCharacterSize(20);
    _textItems[_cantidadItems].setPosition(500, 130 + _cantidadItems * 60);
    ///
    _textItemsV[_cantidadItems].setFont(_font);
    _textItemsV[_cantidadItems].setString("ATRAS");
    _textItemsV[_cantidadItems].setCharacterSize(20);
    _textItemsV[_cantidadItems].setPosition(500, 130 + _cantidadItems * 60);

    _seleccion = 0;
    _seleccionCompra = 0;
    _seleccionVenta = 0;

    if(!_buhoT.loadFromFile("Texture/buhoneroxd.png"))
    {
        //error
    }
    _buhoS.setTexture(_buhoT);
}
TiendaMenu::~TiendaMenu()
{
    delete[] _itemsTotalse;
}
void TiendaMenu::arriba(int x)
{
    if(x == 1)
    {
        if(_seleccion > 0)
            _seleccion--;
    }
    else if(x == 2)
    {
        if(_cantidadItems == 0)
        {
            return;
        }
        else
        {
            if(_seleccionCompra > 0)
            _seleccionCompra--;
        }
    }
    else if(x == 3)
    {
        if(_cantidadItems == 0)
        {
            return;
        }
        else
        {
            if(_seleccionVenta > 0)
            _seleccionVenta--;
        }
    }

}
void TiendaMenu::abajo(int x)
{
    ///INICIO
    if(x == 1)
    {
        if(_seleccion < 3)
            _seleccion++;
    }
    ///COMPRA
    else if(x == 2)
    {
        if(_seleccionCompra < _cantidadItems)
            _seleccionCompra++;
    }
    else if(x == 3)
    {
        if(_seleccionVenta < _cantidadItems)
            _seleccionVenta++;
    }
}
int TiendaMenu::getseleccion(int x)
{
    if(x == 1)
    {
        return _seleccion;
    }
    else if(x == 2)
    {
        return _seleccionCompra;
    }
    else if(x == 3)
    {
        return _seleccionVenta;
    }
}
void TiendaMenu::mostrar(sf::RenderWindow& window)
{
    ///colores
    sf::Color verdeSemiOscuro(34, 139, 34, 255);
    sf::Color grisTransparente(128, 128, 128, 100);
    ///
    for (int i = 0; i < 4; i++)
    {
        _text1[i].setFillColor(i == _seleccion ? verdeSemiOscuro : grisTransparente);
        window.draw(_text1[i]);
    }
}
///COMPRA
void TiendaMenu::mostrarCompra(sf::RenderWindow& window)
{
    ///colores
    sf::Color verdeSemiOscuro(34, 139, 34, 255);
    sf::Color grisTransparente(128, 128, 128, 100);
    //
    for(int i=0; i<_tam; i++)
    {
        _textItems[i].setFillColor(i == _seleccionCompra ? verdeSemiOscuro : grisTransparente);
        window.draw(_textItems[i]);
    }
}

void TiendaMenu::mostrarVenta(sf::RenderWindow& window)
{
    ///colores
    sf::Color verdeSemiOscuro(34, 139, 34, 255);
    sf::Color grisTransparente(128, 128, 128, 100);
    //
    for(int i=0; i<_tam; i++)
    {
        _textItemsV[i].setFillColor(i == _seleccionVenta ? verdeSemiOscuro : grisTransparente);
        window.draw(_textItemsV[i]);
    }
}

void TiendaMenu::draw(sf::RenderWindow& win)
{
    win.draw(_buhoS);
    win.draw(_sprite);
}
