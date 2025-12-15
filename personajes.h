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
    void setVida(int v)
    {
        if(v >= _vidaMax)
            _vidaActual = _vidaMax;
        else
        {
            _vidaActual = v;
        }
    }

    bool estaVivo() const;

    const char* getNombre() const;

    int getVidaA() const;

    int getId() const;

    int getVidaM() const;

    int getAtaque() const;

    int getDefensa() const;

    void info() const;
};
