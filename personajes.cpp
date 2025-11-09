#include <iostream>
#include "personajes.h"
using namespace std;

Personajes::Personajes(int id, const std::string& nombre, int vidaM, int vidaA, int ataque, int defensa, bool vivo)
    :_idPersonaje(id),_vidaMax(vidaM),_vidaActual(vidaA),
    _ataque(ataque),_defensa(defensa),_vivo(vivo){}

void Personajes::recibirDanio(int danio)
{
    _vidaActual -= danio;
    if (_vidaActual <= 0)
    {
        _vidaActual = 0;
        _vivo = false;
    }
}

bool Personajes::estaVivo() const
{
    return _vivo;
}

const std::string Personajes::getNombre() const
{
    return _nombre;
}

int Personajes::getVida() const
{
    return _vidaActual;
}

int Personajes::getAtaque() const
{
    return _ataque;
}
