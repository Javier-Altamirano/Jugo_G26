#pragma once
#include <SFML/Graphics.hpp>
#include "aliados.h"
#include "enemigos.h"
#include "archivos.h"
#include "t_s.h"
#include "menu_pelea.h"


class GameWorld
{
private:
    sf::Clock reloj;
    float delay;
    int f,c;
    MenuPelea menuP;
    Aliado aliado;

    Enemigos enemigoBase;        // Del archivo .dat
    Enemigos enemigoCombate;

    Txt_Spt recursos;

    Archivos archivo;

    enum Estado {Facil, Medio, Dificil, GANASTE, PERDISTE,Huir ,NADA};
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
