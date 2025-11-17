#pragma once
#include <SFML/Graphics.hpp>
#include "aliados.h"
#include "enemigos.h"
#include "archivos.h"
#include "pelea.h"
#include "personaje_jugador.h"
#include "t_s.h"
#include "menu_pelea.h"


class GameWorld
{
private:
    sf::Clock reloj;
    float delay;
    int f,c;
    MenuPelea menuP;
    Jugador jugador;
    Aliado aliado;
    Enemigos enemigoDatos;    // el del archivo .dat

    Enemigos enemigoBase;        // Del archivo .dat
    Enemigos enemigoCombate;

    Txt_Spt recursos;

    Pelea combate;

    Archivos archivo;

    enum Estado {Facil, Medio, Dificil, GANASTE, PERDISTE,NADA};
    Estado estado = NADA;

    int resultadoPelea = 0; // 1=ganó, 2=perdió, 3=huyó
    int _dificultad;

public:
    GameWorld(int dificultad);
    void update(sf::RenderWindow& win);
    void draw(sf::RenderWindow& win);

    void iniciarPelea();
    void finalizarPelea();

    int resultado();
};
