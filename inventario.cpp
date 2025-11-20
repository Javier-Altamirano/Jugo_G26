#include <iostream>
#include "inventario.h"
using namespace std;

Inventario::Inventario()
{
    _cantidad = 0;
    _saldo = 500;
}
bool Inventario::agregarItem(const Item& item)
{
    int precio = item.getPrecioCompra();

    if (_cantidad >= _capacidad_maxima || precio > _saldo)
    {
        std::cout << "El inventario está lleno (" << _capacidad_maxima << " espacios).\n";
        return false;
    }
    // Buscar si ya existe
    for (int i = 0; i < _cantidad; i++)
    {
        if (_items[i].getId() == item.getId())
        {
            int nuevaCantidad = _items[i].getCantidad() + item.getCantidad();
            _items[i].setCantidad(nuevaCantidad);
            _saldo -= precio;
            std::cout << item.getNombre() << " ahora tiene " << nuevaCantidad << " unidades.\n";
            return true;
        }
    }
    // Si no existe, agregar como nuevo
    _items[_cantidad] = item;
    _cantidad++;
    _saldo -= precio;
    std::cout << item.getNombre() << " agregado al inventario.\n";
    return true;
}

bool Inventario::quitarItem(int id)
{
    for (int i = 0; i < _cantidad; i++)
    {
        if (_items[i].getId() == id)
        {
            int saldo = _items[i].getPrecioVenta();
            std::cout << " " << _items[i].getNombre() << " eliminado del inventario.\n";
            /// Desplazar los ítems hacia la izquierda
            for (int x = i; x < _cantidad - 1; x++)
            {
                _items[x] = _items[x + 1];
            }
            _saldo += saldo;
            _cantidad--;
            return true;
        }
    }
    std::cout << " No se encontro un item con ID " << id << ".\n";
    return false;
}

/// CONTENIDO /// TEXTO
void Inventario::mostrarContenido() const
{
    std::cout << "\n Contenido del inventario (" << _cantidad << "/" << _capacidad_maxima << "):\n";
    std::cout << "----------------------------------\n";

    if (_cantidad == 0)
    {
        std::cout << "Vacia.\n";
        return;
    }

    for (int i = 0; i < _cantidad; i++)
    {
        std::cout << _items[i].getNombre() << " x " << _items[i].getCantidad() << "\n";
    }
}
/// Espacio disponible
int Inventario::getCantidad() const
{
    return _cantidad;
}
/// Espacio total
int Inventario::getCapacidadMax() const
{
    return _capacidad_maxima;
}
///
int Inventario::getsaldo()
{
    return _saldo;
}
/// Verificar si tiene un item
bool Inventario::tieneItem(int id) const
{
    for (int i = 0; i < _cantidad; i++)
    {
        if (_items[i].getId() == id)
        {
            return true;
        }
        return false;
    }
}
void Inventario::setSaldo(int saldo)
{
    _saldo = saldo;
}
