#include <iostream>
#include "aliados.h"
#include <string>
#include <cstring>
using namespace std;

Aliado::Aliado(int id, const char* nombre, int vidaM, int vidaA, int ataque, int defensa,int energiaM, int energiaA, bool vivo)
{
    _idPersonaje = id;
    strncpy(_nombre, nombre, sizeof(_nombre) -1);
    _nombre[sizeof(_nombre)-1] = '\0';
    _vidaMax = vidaM;
    _vidaActual = vidaA;
    _ataque = ataque;
    _defensa = defensa;
    _energiaMax = energiaM;
    _energiaActual = energiaA;
    _vivo = vivo;
}
/*Aliado::Aliado(int id, const char* nombre, int vidaM, int vidaA, int ataque, int defensa, bool vivo)
    : Personajes(id, nombre, vidaM, vidaA, ataque, defensa, vivo)
{}
*/
int Aliado::getEnergiaActual()
{
    return _energiaActual;
}

void Aliado::setEnergiaActual(int energia)
{
    _energiaActual = energia;
}

int Aliado::getEnergiaMax()
{
    return _energiaMax;
}
