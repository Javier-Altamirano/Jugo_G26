#pragma once
#include <SFML/Graphics.hpp>
#include "personaje_jugador.h"
#include "enemigo.h"
#include "campamento.h"
#include "sound.h"
#include "estados.h"
#include "menu_pausa.h"
#include "inventarioView.h"
#include "recursos_pelea.h"
#include "combate_back.h"

class MapManager
{
private:
    sf::Clock _reloj;
    float _delay = 0.2f;

    EstadoJuego& _eJuego;
    TiendaEstado& _eTienda;
    Jugador& _jugador;
    Sound& _musica;
    Inventario& _inv;
    MenuPausa& _pausa;
    Combate& _combate;

    Campamento _camp;
    Enemigo _enemigos[15];

    Pausa _ePausa;

public:
    MapManager(
    EstadoJuego& eJuego, TiendaEstado& eTienda,
    Jugador& jugador,Sound& musica, Inventario& inv,
    MenuPausa& pausa,Combate& combate);

    void update();

    void draw(sf::RenderWindow& win);

    void initEnemigos(int n)
    {
        for(int i = 0; i < n; i++)
            _enemigos[i].respawn();
    }

    void updateEnemigos(int n)
    {
        for(int i = 0; i < n; i++)
            _enemigos[i].update();
    }

    void drawEnemigos(sf::RenderTarget& target, int n)
    {
        for(int i = 0; i < n; i++)
            target.draw(_enemigos[i]);
    }

};
