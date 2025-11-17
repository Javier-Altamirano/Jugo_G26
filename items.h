#pragma once
#include <iostream>

class Item
{
private:
    int _idItem;
    char _nombre[30];
    int _compra;
    int _venta;
    int _cantidad;
public:
    Item(int id = 0, const char* nombre = "", int compra = 0, int venta = 0, int cantidad = 0);
    ///Crear personajes para usar
    int getId() const;
    const char* getNombre() const;
    int getPrecioCompra() const;
    int getPrecioVenta() const;
    int getCantidad() const;
    void setCantidad(int cantidad);
};
