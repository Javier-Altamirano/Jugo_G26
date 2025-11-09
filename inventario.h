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
    sf::Text _text;
    int _saldo;
public:
    Inventario(int capacidad);
    /// Destructor
    ~Inventario()
    {
        delete[] _items; /// libera memoria
    }

    bool agregarItem(const Item& item);

    bool quitarItem(int id);

    int getsaldo();
    void mostrar_saldo(sf::RenderWindow& window);

    /// CONTENIDO
    void mostrarContenido() const;
    /// Espacio disponible
    int getCantidad() const;

    /// Espacio total
    int getCapacidadMax() const;

    /// Verificar si tiene un item
    bool tieneItem(int id) const;

    void mensajes(sf::RenderWindow& window);

    void mostrar(sf::RenderWindow& window);
};
