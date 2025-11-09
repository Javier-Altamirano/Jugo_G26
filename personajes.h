#pragma once
#include <iostream>

class Personajes
{
protected:
    int _idPersonaje;
    std::string _nombre;
    int _vidaMax;
    int _vidaActual;
    bool _vivo;
    int _ataque;
    int _defensa;
public:
    Personajes(int id, const std::string& nombre, int vidaM, int vidaA, int ataque, int defensa, bool vivo);
    ///destruye la derivada - limpia - {};
    virtual ~Personajes() = default;
    ///Acciones
    virtual void recibirDanio(int danio);

    bool estaVivo() const;

    const std::string getNombre() const;

    int getVida() const;

    int getAtaque() const;

    //virtual void mostrarInfo() const;
};
