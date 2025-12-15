#include <iostream>
#include <cstdio>
#include "game_data.h"

GameData::GameData(){}

void GameData::setEquipo(Aliado* eq)
{
    for(int i = 0; i < 3; i++)
    {
        _equipo[i] = eq[i];
    }
}

void GameData::getEquipo(Aliado* eq) const
{
    for(int i = 0; i < 3; i++)
    {
        eq[i] = _equipo[i];
    }
}

void GameData::setInventario(Inventario& inv)
{
    _inv.copiar(inv);
}

void GameData::setRegistros(Registros& reg)
{
    _reg = reg;
}

Inventario& GameData::getInventario()
{
    return _inv;
}

Registros& GameData::getRegistros()
{
    return _reg;
}

bool GameData::guardar(const std::string& archivo)
{
    FILE* p = fopen(archivo.c_str(), "wb");
    if(p == NULL) return false;

    // Equipo
    for(int i = 0; i < 3; i++)
    {
        _equipo[i].guardar(p);
    }

    // Inventario
    _inv.guardar(p);

    // Registros
    _reg.guardar(p);

    fclose(p);
    return true;
}

bool GameData::cargar(const std::string& archivo)
{
    FILE* p = fopen(archivo.c_str(), "rb");
    if(p == NULL) return false;

    // Equipo
    for(int i = 0; i < 3; i++)
    {
        _equipo[i].cargar(p);
    }

    // Inventario
    _inv.cargar(p);

    // Registros
    _reg.cargar(p);

    fclose(p);
    return true;
}
