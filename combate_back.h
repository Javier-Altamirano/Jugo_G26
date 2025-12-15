#pragma once
#include "aliados.h"
#include "enemigos.h"
#include "archivos.h"
#include "menu_pelea.h"
#include "inventario.h"
#include "sound.h"
#include "registro.h"
#include "estados.h"
#include "recursos_pelea.h"
#include "inventarioView.h"
#include "tiendaManager.h"
#include "personaje_jugador.h"
#include "game_data.h"

class Combate
{
private:
    ///REGISTROS / ARCHIVOS
    GameData& _save;
    Archivos _archivo;
    Registros* _registro;
    Inventario& _mochila;
    Jugador& _jugador;
    InventarioView _invView;
    ///personajes
    int _aliadoActual;
    bool _adLiberada = true;
    bool _fLiberada;

    Enemigos _enemigos[3];
    int _cantEnemigos;
    int _enemigoActual;
    int _objetivo = 0;

    ///OTROS
    Sound& _musica;
    RecursoPelea _recursos;
    MenuPelea _menuP;
    float _bonus;

    sf::Clock _reloj;
    float _delay;

    sf::Clock _relojTurnoEnemigo;
    TurnoCombate _turno;
    EstadoCombate _combate;
    TiendaEstado& _eTienda;
    EstadoJuego& _eJuego;

    enum Dificultad {Facil, Medio, Dificil, NADA};
    Dificultad _dificultad = NADA;

    enum EstadoInventario {Cerrado, Abierto};
    EstadoInventario _invActual =  Cerrado;

public:
    Combate(
    EstadoJuego& eJuego,Inventario& mochila,Registros* r,EstadoCombate& eCombat,
    TiendaEstado& eTienda,Jugador& jugador,Sound& musica,GameData& save);

    void setPelea(int dificultad);

    void update(sf::RenderWindow& win,Inventario& inv,Aliado* equipo,int cantidadA);

    void turnoEnemigo(Enemigos* enemigos, Aliado* aliados, int cantidadAliados);

    void turnoAliado(Inventario& inv,Aliado* aliadoActual,Enemigos* enemgoActual);

    void usarItem(Aliado* aliadoActual);

    bool todosEnemigosMuertos();

    void avanzarObjetivo(int direccion, Enemigos* enemigos);

    bool todosAliadosMuertos(Aliado* aliados, int cantidad);

    void avanzarAliado(Aliado* aliados, int cantidad);
};
