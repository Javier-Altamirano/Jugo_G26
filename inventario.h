#pragma once
#include <istream>
#include "items.h"

class Inventario
{
private:
    Item _items[10];
    int _cantidad;
    const int _capacidad_maxima = 10;
    int _saldo;
public:
    Inventario();
    /// Destructor
    ~Inventario(){}

    bool agregarItem(const Item& item);

    bool quitarItem(int id);

    void setSaldo(int saldo);
    int getsaldo();

    /// CONTENIDO
    void mostrarContenido() const;

    /// Espacio disponible
    int getCantidad() const;

    /// Espacio total
    int getCapacidadMax() const;

    /// Verificar si tiene un item
    bool tieneItem(int id) const;

    const Item& getItem(int index) const { return _items[index]; }

};
