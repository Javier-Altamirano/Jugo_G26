#pragma once
#include <string>
#include <cstdio>
#include "aliados.h"
#include "inventario.h"
#include "registro.h"

class GameData {
private:
    Aliado _equipo[3];
    Inventario _inv;
    Registros _reg;

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
