#include <iostream>
#include "items.h"
using namespace std;

Item::Item()
{
    _idItem = 0;
    _nombre = "Desconocido";
    _compra = 0;
    _venta  = 0;
}

Item::Item(int id, const std::string& nombre, int compra, int venta)
{
    _idItem = id;
    _nombre = nombre;
    _compra = compra;
    _venta  = venta;
}

void Item::setCantidad(int cantidad)
{
    _cantidad = cantidad;
}
