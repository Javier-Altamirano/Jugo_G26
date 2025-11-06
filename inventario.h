#pragma once
#include <istream>
#include "items.h"
#include <SFML/Graphics.hpp>

class Inventario
{
private:
    Item* _items;
    int _cantidad;
    int _capacidad_maxima;
    sf::Font _font;
    sf::Text _text[2];
    sf::Text _disponible[2];
    sf::Text _items_tienda;
public:
    Inventario(int capacidad);
    /// Destructor
    ~Inventario()
    {
        delete[] _items; /// libera memoria
    }

    bool agregarItem(const Item& item);

    bool quitarItem(int id);

    /// CONTENIDO
    void mostrarContenido() const;
    /// Espacio disponible
    int getCantidad() const;

    /// Espacio total
    int getCapacidadMax() const;

    /// Verificar si tiene un item
    bool tieneItem(int id) const;
    int contar1();
    int contar2();

    void mostrar(sf::RenderWindow& window);
};
