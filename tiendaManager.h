#pragma once
#include <SFML/Graphics.hpp>
#include "personaje_jugador.h"
#include "vendedor.h"
#include "campamento.h"
#include "tienda_menu.h"
#include "items.h"
#include "inventario.h"
#include "inventarioView.h"
#include "sound.h"
#include "estados.h"
#include "menu_pausa.h"

class TiendaManager
{
private:
    sf::Clock _reloj;
    float _delay = 0.2f;

    Vendedor _vendedor;
    Campamento _camp;

    TiendaMenu _menu;
    MenuPausa& _pausa;

    Inventario& _inv;
    EstadoJuego& _eJuego;
    TiendaEstado& _eTienda;
    Jugador& _jugador;
    Sound& _musica;
    Aliado* _equipo;
    sf::Vector2f _spawnPos;

    std::vector<Item> _items;

    Comprando _comprando;
public:
    TiendaManager(Inventario& inv,EstadoJuego& eJuego,TiendaEstado& eTienda,Jugador& jugador,Sound& musica,Aliado* equipo,MenuPausa& pausa);

    void setItems(std::vector<Item> items);

    void update();

    void draw(sf::RenderWindow& win);

};
