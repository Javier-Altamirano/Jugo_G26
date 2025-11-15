#include <iostream>
#include <string>
#include <cstring>
#include "items.h"
using namespace std;


Item::Item(int id, const char* nombre, int compra , int venta, int cantidad)
{
    _idItem = id;
    strncpy(_nombre, nombre, sizeof(_nombre) - 1);
    ///Se asegura de que la cadena esté terminada correctamente con el carácter nulo '\0'
    _nombre[sizeof(_nombre) - 1] = '\0';
    _compra = compra;
    _venta = venta;
    _cantidad = cantidad;
}

void Item::setCantidad(int cantidad)
{
    _cantidad = cantidad;
}
int Item::getId() const
{
    return _idItem;
}
const char* Item::getNombre() const
{
    return _nombre;
}
int Item::getPrecioCompra() const
{
    return _compra;
}
int Item::getPrecioVenta() const
{
    return _venta;
}
int Item::getCantidad() const
{
    return _cantidad;
}
