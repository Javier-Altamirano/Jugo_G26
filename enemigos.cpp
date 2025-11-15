#include <iostream>
#include "enemigos.h"
#include <string>
#include <cstring>
using namespace std;
/*
Enemigos::Enemigos(int id, const char* nombre, int vidaM, int vidaA, int ataque, int defensa, bool vivo)
    : Personajes(id, nombre, vidaM, vidaA, ataque, defensa, vivo)
{
}*/
Enemigos::Enemigos(int id, const char* nombre, int vidaM, int vidaA, int ataque, int defensa, bool vivo)
{
    _idPersonaje = id;
    strncpy(_nombre, nombre, sizeof(_nombre) -1);
    _nombre[sizeof(_nombre)-1] = '\0';
    _vidaMax = vidaM;
    _vidaActual = vidaA;
    _ataque = ataque;
    _defensa = defensa;
    _vivo = vivo;
}
