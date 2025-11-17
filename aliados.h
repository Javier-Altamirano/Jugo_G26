#pragma once
#include "personajes.h"
#include <SFML/Graphics.hpp>

class Aliado : public Personajes
{
private:
public:
    Aliado() = default;
    Aliado(int id, const char* nombre, int vidaM, int vidaA, int ataque, int defensa,int energiaM, int energiaA, bool vivo);

};

