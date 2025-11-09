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
    _text.setFont(_font);
    _text.setCharacterSize(20);
    _text.setColor(sf::Color::White);
    _saldo = 50;
}
bool Inventario::agregarItem(const Item& item)
{
    int precio = item.getPrecioCompra();
    if(_saldo >= precio && _cantidad < _capacidad_maxima)
    {
        // Buscar si ya existe
        for (int i = 0; i < _cantidad; i++)
        {
            int saldo = _items[i].getPrecioCompra();
            if (_items[i].getId() == item.getId() && _saldo >= saldo)
            {
                int nuevaCantidad = _items[i].getCantidad() + item.getCantidad();
                _items[i].setCantidad(nuevaCantidad);
                std::cout << item.getNombre() << " ahora tiene " << nuevaCantidad << " unidades.\n";
                _text.setString(item.getNombre() + " ahora tiene " + std::to_string(nuevaCantidad) + " unidades");
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
    if (_cantidad >= _capacidad_maxima || precio > _saldo)
    {
        std::cout << "El inventario está lleno (" << _capacidad_maxima << " espacios).\n";
        return false;
    }
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
            int saldo = _items[i].getPrecioVenta();
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
        else
        {
            return false;
        }
    }
}
void Inventario::mostrar_saldo(sf::RenderWindow& window)
{
    _text.setPosition(80,415);
    _text.setColor(sf::Color::Green);
    _text.setString("Dinero $ " + std::to_string(_saldo));
    window.draw(_text);
}
void Inventario::mostrar(sf::RenderWindow& window)
{
    sf::Text mensaje;
    mensaje.setFont(_font);
    std::string mens1 = "VACIO...";
    mensaje.setString(mens1);
    if (_cantidad == 0)
    {
        mensaje.setPosition(575,340);
        window.draw(mensaje);
    }
    else
    {
        for (int i = 0; i < _cantidad; i++)
        {
            mensaje.setString(_items[i].getNombre() + " X (" + std::to_string(_items[i].getCantidad()) + ")");

            mensaje.setCharacterSize(20);
            mensaje.setPosition(570,280+i*30);
            window.draw(mensaje);
        }
    }
}
