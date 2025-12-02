#include <iostream>
#include <string>
#include <cstring>
#include "personajes.h"
using namespace std;

Personajes::Personajes(int id, const char* nombre, int vidaM, int vidaA, int ataque, int defensa, bool vivo)
{
    _idPersonaje = id;
    // copiar nombre al char array asegurando terminación nula
    ///strncpy(destino, origen, n)
    strncpy(_nombre, nombre, sizeof(_nombre) - 1);
    ///Se asegura de que la cadena esté terminada correctamente con el carácter nulo '\0'
    _nombre[sizeof(_nombre) - 1] = '\0';
    _vidaMax = vidaM;
    _vidaActual = vidaA;
    _ataque = ataque;
    _defensa = defensa;
    _vivo = vivo;
}

bool Personajes::estaVivo() const
{
    if(_vidaActual > 0)
        return _vivo;
}
const char* Personajes::getNombre() const
{
    return _nombre;
}

int Personajes::getVidaA() const
{
    return _vidaActual;
}

int Personajes::getVidaM() const
{
    return _vidaMax;
}
int Personajes::getAtaque() const
{
    return _ataque;
}

int Personajes::getId() const
{
    return _idPersonaje;
}

int Personajes::getDefensa() const
{
    return _defensa;
}

void Personajes::info() const
{
    cout << _idPersonaje << "  " << _nombre << endl;
    cout << "Atk: " << _ataque << "  Def: " << _defensa << endl;
    cout << "HP:  " << _vidaMax << endl;
}
