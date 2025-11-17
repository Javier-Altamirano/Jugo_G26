#pragma once
#include <SFML/Graphics.hpp>
#include "items.h"
#include "archivos.h"
#include "inventario.h"
class TiendaMenu:  public sf::Drawable
{
private:
    Inventario* inv;
    ///
    sf::Font _font;
    sf::Text _text1[3];
    int _seleccion;
    ///COMPRA
    Item* _itemsTotalse;
    int _cantidadItems;
    std::vector<sf::Text> _textItems;
    std::vector<sf::Text> _textItemsV;
    int _tam;
    int _seleccionCompra;
    int _seleccionVenta;

    sf::Texture _textura;
    sf::Sprite _sprite;
public:
    TiendaMenu();
    ~TiendaMenu();

    int getseleccion(int x);
    void arriba(int x);
    void abajo(int x);

    void mostrar(sf::RenderWindow& window);
    void mostrarCompra(sf::RenderWindow& window);
    void mostrarVenta(sf::RenderWindow& window);

    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};
