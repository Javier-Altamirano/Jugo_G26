#pragma once
#include "aliados.h"
#include "enemigos.h"

class Pelea
{
private:
    Aliado* p_jugador;     // CAMBIAMOS A PUNTEROS
    Enemigos* p_enemigo;

    bool turnoJugador = true;
    bool finalizada = false;
    int resultado = 0;  // 1 = gano jugador, 2 = perdio

    // UI muy simple
    sf::Font font;
    sf::Text info;

public:
    Pelea() : p_jugador(nullptr), p_enemigo(nullptr) {}

    Pelea(Aliado& j, Enemigos& e)
        : p_jugador(&j), p_enemigo(&e), turnoJugador(true)
    {
        turnoJugador = true;
        finalizada = false;
        resultado = 0;

        font.loadFromFile("Font/square.ttf");
        info.setFont(font);
        info.setCharacterSize(24);
        info.setFillColor(sf::Color::White);
        info.setPosition(50, 50);
    }

    bool valida() const
    {
        return p_jugador != nullptr && p_enemigo != nullptr;
    }
    bool termino() const
    {
        return finalizada;
    }
    int getResultado() const
    {
        return resultado;
    }

    bool getTurnoJugador() const
    {
        return turnoJugador;
    }

    bool combateTerminado() const
    {
        return !p_jugador->estaVivo() || !p_enemigo->estaVivo();
    }

    void accionJugador(int opcion)
    {
        if (!valida()) return;

        int ataque = p_jugador->getAtaque();
        int defensa = p_enemigo->getDefensa();
        int danio = ataque - defensa;

        if (opcion == 0)      p_enemigo->Danio(danio);
        else if (opcion == 1) p_enemigo->Danio(danio + 10);

        turnoJugador = false;
    }

    void accionEnemigo()
    {
        if (!valida()) return;

        int ataque = p_enemigo->getAtaque();
        int defensa = p_jugador->getDefensa();
        int danio = ataque - defensa;

        p_jugador->Danio(danio);
        turnoJugador = true;
    }

    void draw(sf::RenderWindow& win)
    {
        win.draw(info);
    }

    void update(sf::RenderWindow& win)
    {
        if (finalizada) return;

        // turno jugador (ejemplo simple)
        if (turnoJugador)
        {
            info.setString("Turno del jugador - A para atacar");

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                accionJugador(0);
            }
        }
        else
        {
            accionEnemigo();
        }

        // verificar fin
        if (p_jugador->estaVivo() == false)
        {
            finalizada = true;
            resultado = 2;
        }
        if (p_enemigo->estaVivo() == false)
        {
            finalizada = true;
            resultado = 1;
        }
    }
};
