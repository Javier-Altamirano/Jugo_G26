#pragma once
#include <string>
#include "aliados.h"
#include "enemigos.h"
#include "items.h"
class Archivos
{
private:
    std::string _aliados;
    std::string _enemigos;
    std::string _items;
public:
    Archivos(const std::string aliados,const std::string enemigos,const std::string items)
        :_aliados(aliados), _enemigos(enemigos),_items(items){}

    ///-----------> ITEMS <-----------///
    bool GuardarItem(const Item& reg);
    bool ReGuardarItem(const Item& reg, int pos);
    Item LeerItem(int pos);
    int CantItemsG();
    int BII(int id);
    void LeerIT(Item* v, int cantidad);
    //-----------> JUGABLES <-----------///
    bool GuardarAliados(const Aliado& reg);
    bool ReGuardarAliados(const Aliado& reg, int pos);
    Aliado LeerAliado(int pos);
    int CantAliadoG();
    int BIA(int id);
    void LeerAT(Aliado* v, int cantidad);
    //-----------> ENEMIGOS <-----------///
    bool GuardarEnemigo(const Enemigos& reg);
    bool ReGuardarEnemigo(const Enemigos& reg, int pos);
    Enemigos LeerEnemigo(int pos);
    int CantEnemigoG();
    int BIE(int id);
    void LeerET(Enemigos* v, int cantidad);
};
