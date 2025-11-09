#include <iostream>
#include "items.h"
using namespace std;

Item::Item()
{
    _idItem = 0;
    _nombre = "Desconocido";
    _compra = 0;
    _venta  = 0;
    _cantidad = 0;
}

Item::Item(int id, const std::string& nombre, int compra, int venta, int cantidad)
{
    _idItem = id;
    _nombre = nombre;
    _compra = compra;
    _venta  = venta;
    _cantidad = cantidad;
}

void Item::setCantidad(int cantidad)
{
    _cantidad = cantidad;
}
