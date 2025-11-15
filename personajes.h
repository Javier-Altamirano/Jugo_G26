#pragma once
#include <iostream>

class Personajes
{
protected:
    int _idPersonaje;
    char _nombre[30];
    int _vidaMax;
    int _vidaActual;
    bool _vivo;
    int _ataque;
    int _defensa;
public:

    Personajes(int id = 0, const char* nombre = "", int vidaM = 0, int vidaA = 0,
         int ataque = 0, int defensa = 0, bool vivo = true);
    ///destruye la derivada - limpia - {};
    virtual ~Personajes() = default;
    ///Acciones
    virtual void recibirDanio(int danio);

    bool estaVivo() const;

    const char* getNombre() const;

    int getVidaA() const;

    int getId() const;

    int getVidaM() const;

    int getAtaque() const;
};
