#include <iostream>
#include "inventario.h"
#include "archivos.h"
#include <fstream>
using namespace std;

Inventario::Inventario()
{
    _cantidad = 0;
    _saldo = 50;
}
bool Inventario::agregarItem(const Item& item)
{
    int precio = item.getPrecioCompra();

    if (_cantidad >= _capacidad_maxima || precio > _saldo)
    {
        std::cout << "El inventario lleno (" << _capacidad_maxima << " espacios).\n";
        return false;
    }

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

    _items[_cantidad] = item;
    _cantidad++;
    _saldo -= precio;
    std::cout << item.getNombre() << " agregado al inventario.\n";
    return true;
}

bool Inventario::quitarItem(int id, bool vender)
{
    for (int i = 0; i < _cantidad; i++)
    {
        if (_items[i].getId() == id)
        {
            int cant = _items[i].getCantidad();
            if (cant > 1)
            {
                _items[i].setCantidad(cant - 1);

                if (vender)
                {
                    _saldo += _items[i].getPrecioVenta();
                }

                std::cout << "Usado 1 de " << _items[i].getNombre()
                          << " Quedan: " << _items[i].getCantidad() << "\n";
                return true;
            }

            int precioVenta = _items[i].getPrecioVenta();
            std::cout << _items[i].getNombre() << " eliminado del inventario\n";

            /// mueve
            for (int x = i; x < _cantidad - 1; x++)
            {
                _items[x] = _items[x + 1];
            }
            _cantidad--;


            if (vender)
            {
                _saldo += precioVenta;
            }

            return true;
        }
    }

    std::cout << " No se encontro un item con ID " << id << "\n";
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

int Inventario::getCantidad() const
{
    return _cantidad;
}

int Inventario::getCapacidadMax() const
{
    return _capacidad_maxima;
}

int Inventario::getsaldo()
{
    return _saldo;
}

void Inventario::setSaldo(int saldo)
{
    _saldo = saldo;
}
void Inventario::copiar(const Inventario& o)
{
    _saldo = o._saldo;
    _cantidad = o._cantidad;

    for(int i = 0; i < _cantidad; i++)
        _items[i] = o._items[i];
}

void Inventario::cargarItems(const Item& item)
{
    for(int i = 0; i < _cantidad; i++)
    {
        if(_items[i].getId() == item.getId())
        {
            _items[i].setCantidad(_items[i].getCantidad() + item.getCantidad());
            return;
        }
    }

    if(_cantidad < _capacidad_maxima)
    {
        _items[_cantidad] = item;
        _cantidad++;
    }
}
void Inventario::guardar(std::ofstream& out) const
{
    // Saldo
    out.write((char*)&_saldo, sizeof(int));

    // Cantidad de items
    out.write((char*)&_cantidad, sizeof(int));

    // Items
    for(int i = 0; i < _cantidad; i++)
    {
        int id = _items[i].getId();
        int cant = _items[i].getCantidad();

        out.write((char*)&id, sizeof(int));
        out.write((char*)&cant, sizeof(int));
    }
}
void Inventario::cargar(std::ifstream& in)
{
    // Limpio inventario
    _cantidad = 0;

    // Saldo
    in.read((char*)&_saldo, sizeof(int));

    int cantItems;
    in.read((char*)&cantItems, sizeof(int));

    Archivos arch("Aliados.dat","Enemigos.dat","Items.dat");

    for(int i = 0; i < cantItems; i++)
    {
        int id, cantidad;
        in.read((char*)&id, sizeof(int));
        in.read((char*)&cantidad, sizeof(int));

        // Traigo item base del catálogo
        Item it = arch.LeerItem(arch.BII(id));
        it.setCantidad(cantidad);

        cargarItems(it);
    }
}
