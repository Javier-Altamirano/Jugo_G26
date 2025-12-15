#pragma once
#include "archivos.h"
#include "inventario.h"
#include "registro.h"
#include <string>

class GameData
{
private:
    Registros _reg;
    Aliado _equipo[3];
    Inventario _inv;

public:
    GameData();

    void setEquipo(Aliado* eq);
    void getEquipo(Aliado* eq) const;

    void setInventario(Inventario& inv);
    void setRegistros(Registros& reg);

    Inventario& getInventario();
    Registros& getRegistros();

    bool guardar(const std::string& archivo);
    bool cargar(const std::string& archivo);
};
