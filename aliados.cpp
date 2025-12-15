#include "aliados.h"
#include "archivos.h"
#include <fstream>
#include <stdio.h>
#include <string.h>
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

int Aliado::getEnergiaActual()
{
    return _energiaActual;
}

void Aliado::setEnergiaActual(int energia)
{
    int x = _energiaActual + energia;
    if(x < _energiaMax)
    {
        _energiaActual = x;
    }
    else
    {
        _energiaActual = _energiaMax;
    }
}
void Aliado::setEnergia(int energia)
{
    if(energia < 0) energia = 0;
    if(energia > _energiaMax) energia = _energiaMax;
    _energiaActual = energia;
}

int Aliado::getEnergiaMax()
{
    return _energiaMax;
}

void Aliado::guardar(std::ofstream& out) const
{
    int id = getId();
    int vida = getVidaA();
    int energia = _energiaActual;

    out.write((char*)&id, sizeof(int));
    out.write((char*)&vida, sizeof(int));
    out.write((char*)&energia, sizeof(int));
}

void Aliado::cargar(std::ifstream& in)
{
    int id, vida, energia;

    in.read((char*)&id, sizeof(int));
    in.read((char*)&vida, sizeof(int));
    in.read((char*)&energia, sizeof(int));

    // CATÁLOGO
    Archivos arch("Aliados.dat","Enemigos.dat","Items.dat");
    *this = arch.LeerAliado(arch.BIA(id));

    // ESTADO DE PARTIDA
    setVida(vida);
    setEnergia(energia);
}
