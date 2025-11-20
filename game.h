#pragma once
#include <SFML/Graphics.hpp>
#include "aliados.h"
#include "enemigos.h"
#include "archivos.h"
#include "t_s.h"
#include "menu_pelea.h"
#include "inventario.h"
#include "inventarioView.h"


class Combate
{
private:
    sf::Clock reloj;
    float delay;
    int _seleccion;
    MenuPelea menuP;
    Aliado aliado;
    std::vector<Aliado> _equipoA;
    int _aliadoS;

    std::vector<Enemigos> _enemigos;
    int _objetivo;

    Enemigos enemigoBase;
    Enemigos enemigoCombate;

    Txt_Spt recursos;

    Archivos archivo;
    Inventario& _mochila;
    InventarioView _mVista;

    enum Estado {Facil, Medio, Dificil, GANASTE, PERDISTE,Huir ,NADA};
    Estado estado = NADA;
    enum EstadoInventario {Cerrado, Abierto};
    EstadoInventario invActual =  Cerrado;

    int _resultadoPelea = 0;
    int _dificultad;

    enum Turno {TURNO_JUGADOR, TURNO_ENEMIGO};
    Turno turnoActual;

    sf::Font _font;
    sf::Text _turno;

public:
    Combate(int dificultad,Inventario& mochila);
    void update(sf::RenderWindow& win);
    void draw(sf::RenderWindow& win);

    void iniciarPelea(int x);
    void finalizarPelea();

    int resultado();
};
