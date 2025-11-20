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
    int _energiaMax;
    int _energiaActual;
public:

    Personajes(int id = 0, const char* nombre = "", int vidaM = 0, int vidaA = 0,
               int ataque = 0, int defensa = 0,int energiaM = 0,int energiaA = 0, bool vivo = true);
    ///destruye la derivada - limpia - {};
    ~Personajes() = default;
    ///Acciones
    void Danio(int x)
    {
        if(_vidaActual > x)
        {
            _vidaActual -= x;
        }
        else
        {
            _vidaActual = 0;
        }
    }
    void setEnergia(int e)
    {
        if(e < 0 || e > _energiaMax)
        {
            return;
        }
        else if(e <= _energiaMax)
            _energiaActual = e;
    }
    void Cura(int c)
    {
        int x = _vidaActual + c;
        if(x < _vidaMax)
        {
            _vidaActual = x;
        }
        else
        {
            _vidaActual = _vidaMax;
        }
    }
    void Revivir()
    {
        _vidaActual = _vidaMax;
    }

    bool estaVivo() const;

    const char* getNombre() const;

    int getVidaA() const;

    int getId() const;

    int getVidaM() const;

    int getEM() const;

    int getEA() const;

    int getAtaque() const;

    int getDefensa() const;
};
