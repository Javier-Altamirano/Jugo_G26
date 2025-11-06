#include <iostream>
#include "inventario.h"
using namespace std;


Inventario::Inventario(int capacidad)
{
    _capacidad_maxima = capacidad;
    _cantidad = 0;
    _items = new Item[_capacidad_maxima]; /// reserva memoria dinámica
    if(!_font.loadFromFile("Font/square.ttf"))
    {
        //error
    }
    std::string opciones [] {"P. Vida X", "P. Energia X"};
    for(int i=0; i<2; i++)
    {
        _text[i].setFont(_font);
        _text[i].setString(opciones[i]);
        _text[i].setCharacterSize(28);
        _text[i].setPosition(280, 180 + i * 70);
    }
    for(int i=0; i<2; i++)
    {
        _disponible[i].setFont(_font);
        _disponible[i].setCharacterSize(28);
        _disponible[i].setPosition(280, 180 + i * 70);
    }
}
bool Inventario::agregarItem(const Item& item)
{
    // Buscar si ya existe
    for (int i = 0; i < _cantidad; i++)
    {
        if (_items[i].getId() == item.getId())
        {
            int nuevaCantidad = _items[i].getCantidad() + item.getCantidad();
            _items[i].setCantidad(nuevaCantidad);
            std::cout << item.getNombre() << " ahora tiene " << nuevaCantidad << " unidades.\n";
            return true;
        }
    }

    // Si no existe, agregar como nuevo
    if (_cantidad >= _capacidad_maxima)
    {
        std::cout << "El inventario está lleno (" << _capacidad_maxima << " espacios).\n";
        return false;
    }

    _items[_cantidad] = item;
    _cantidad++;
    std::cout << item.getNombre() << " agregado al inventario.\n";
    return true;
}

bool Inventario::quitarItem(int id)
{
    for (int i = 0; i < _cantidad; i++)
    {
        if (_items[i].getId() == id)
        {
            std::cout << " " << _items[i].getNombre() << " eliminado del inventario.\n";
            /// Desplazar los ítems hacia la izquierda
            for (int x = i; x < _cantidad - 1; x++)
            {
                _items[x] = _items[x + 1];
            }
            _cantidad--;
            return true;
        }
    }
    std::cout << " No se encontro un item con ID " << id << ".\n";
    return false;
}

/// CONTENIDO
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
        std::cout << "ID: " << _items[i].getId() << " | " << _items[i].getNombre() << " | Compra: " << _items[i].getPrecioCompra() << " | Venta: " << _items[i].getPrecioVenta() << "\n";
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
/// Verificar si tiene un item
bool Inventario::tieneItem(int id) const
{
    for (int i = 0; i < _cantidad; i++)
    {
        if (_items[i].getId() == id)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Inventario::mostrar(sf::RenderWindow& window)
{
    sf::Text mensaje;
    mensaje.setFont(_font);
    std::string mens1 = "Esta vacio";
    mensaje.setString(mens1);
    if (_cantidad == 0)
    {
        mensaje.setPosition(400,300);
        window.draw(mensaje);
    }
    else
    {
        for (int i = 0; i < _cantidad; i++)
        {
            mensaje.setString(_items[i].getNombre());
            mensaje.setCharacterSize(20);
            mensaje.setPosition(400,50+i*70);
            window.draw(mensaje);
        }
    }
}
