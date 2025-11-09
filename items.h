#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Item
{
private:
    int _idItem;
    std::string _nombre;
    int _compra;
    int _venta;
    int _cantidad;
public:
    Item();
    Item(int id, const std::string& nombre, int compra , int venta, int cantidad);
    ///Crear personajes para usar
    int getId() const { return _idItem; }
    std::string getNombre() const { return _nombre; }
    int getPrecioCompra() const { return _compra; }
    int getPrecioVenta() const { return _venta; }
    int getCantidad() const {return _cantidad;}
    void setCantidad(int cantidad);

};
