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

void Aliado::guardar(FILE* p) const
{
    int id = getId();
    int vida = getVidaA();
    int energia = _energiaActual;

    fwrite(&id, sizeof(int), 1, p);
    fwrite(&vida, sizeof(int), 1, p);
    fwrite(&energia, sizeof(int), 1, p);
}

void Aliado::cargar(FILE* p)
{
    int id, vida, energia;

    fread(&id, sizeof(int), 1, p);
    fread(&vida, sizeof(int), 1, p);
    fread(&energia, sizeof(int), 1, p);

    // Catálogo
    Archivos arch("Aliados.dat","Enemigos.dat","Items.dat");
    *this = arch.LeerAliado(arch.BIA(id));

    // Estado de la partida
    setVida(vida);
    setEnergia(energia);
}
