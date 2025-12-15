#include <iostream>
#include <fstream>
#include "game_data.h"

GameData::GameData(){}

void GameData::setEquipo(Aliado* eq)
{
    for(int i = 0; i < 3; i++)
        _equipo[i] = eq[i];
}

void GameData::getEquipo(Aliado* eq) const
{
    for(int i = 0; i < 3; i++)
        eq[i] = _equipo[i];
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
     std::ofstream out(archivo, std::ios::binary);
    if(!out) return false;

    for(int i = 0; i < 3; i++)
        _equipo[i].guardar(out);

    _inv.guardar(out);
    _reg.guardar(out);

    return true;
}

bool GameData::cargar(const std::string& archivo)
{

    std::ifstream in(archivo, std::ios::binary);
    if(!in) return false;

    for(int i = 0; i < 3; i++)
        _equipo[i].cargar(in);

    _inv.cargar(in);
    _reg.cargar(in);

    return true;
}

