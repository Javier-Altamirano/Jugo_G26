#pragma once
#include <string>
#include "personajes.h"

class Aliado : public Personajes
{
private:
    int _energiaMax;
    int _energiaActual;
public:
    Aliado() = default;
    Aliado(int id, const char* nombre, int vidaM, int vidaA, int ataque, int defensa,int energiaM, int energiaA, bool vivo);

    int getEnergiaActual();

    void setEnergiaActual(int energia);

    void setEnergia(int energia);

    int getEnergiaMax();

    void guardar(std::ofstream& out) const;

    void cargar(std::ifstream& in);
};

