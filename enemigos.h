#pragma once
#include "personajes.h"

class Enemigos : public Personajes
{
public:
    Enemigos() = default;
    Enemigos(int id, const char* nombre, int vidaM, int vidaA, int ataque, int defensa,int energiaM, int energiaA, bool vivo);
};
