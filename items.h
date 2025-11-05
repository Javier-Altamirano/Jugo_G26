#pragma once
#include <SFML/Graphics.hpp>

class Item
{
private:
    int _idItem;
    const char _nombreItem[30];
    int _compra;
    int _venta;
    sf::Texture _textura;
    sf::Sprite _sprite:

public::
    Item();

    void comprar_Item();
    void vender_Item();

    ///Crear personajes para usar
    void usar_Item();
};
