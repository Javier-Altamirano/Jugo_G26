#pragma once
#include <istream>
#include "items.h"
#include <fstream>
#include "archivos.h"

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
    ~Inventario() {}

    bool agregarItem(const Item& item);

    bool quitarItem(int id, bool vender);

    void setSaldo(int saldo);

    int getsaldo();

    /// CONTENIDO
    void mostrarContenido() const;

    /// Espacio disponible
    int getCantidad() const;

    /// Espacio total
    int getCapacidadMax() const;

    const Item& getItem(int index) const
    {
        return _items[index];
    }

    void copiar(const Inventario& otro);


    void cargarItems(const Item& item);

    void guardar(FILE* p) const;
    void cargar(FILE* p);


};
