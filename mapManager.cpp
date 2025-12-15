#include <iostream>
#include "mapManager.h"
using namespace std;

MapManager::MapManager(EstadoJuego& eJuego, TiendaEstado& eTienda, Jugador& jugador,Sound& musica, Inventario& inv,MenuPausa& pausa,Combate& combate)
    :_eJuego(eJuego), _eTienda(eTienda), _jugador(jugador), _musica(musica), _inv(inv),_pausa(pausa), _combate(combate)
{
    _camp.pos(990,880);
    initEnemigos(15);
}

void MapManager::update()
{
    if (_eJuego != EstadoJuego::MAPA)
    {
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)&& _reloj.getElapsedTime().asSeconds() > _delay && !_pausa.estaActivo())
    {
        _reloj.restart();
        _pausa.activar();
        return;
    }

    if (_pausa.estaActivo())
    {
        _pausa.update(_inv, _eJuego, _musica);
        return;
    }

    _musica.ostPlay(2);
    _jugador.update(1);
    updateEnemigos(15);

    if (_jugador.isColision(_camp))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)
                && _reloj.getElapsedTime().asSeconds() > _delay)
        {
            _reloj.restart();
            _eJuego = EstadoJuego::TIENDA;
            _eTienda = TiendaEstado::DENTRO;
            _musica.ostPause(2);
            _jugador.pos(400, 500);
            return;
        }
    }

    for(int i=0; i<15; i++)
    {
        if(i >= 0 && i <6)
        {
            if (_jugador.isColision(_enemigos[i]))
            {
                _reloj.restart();
                _eJuego = EstadoJuego::PELEA;
                _combate.setPelea(1);
                _musica.ostPause(2);
                initEnemigos(15);
            }
        }
        if(i >= 7 && i <12)
        {
            if (_jugador.isColision(_enemigos[i]))
            {
                _reloj.restart();
                _eJuego = EstadoJuego::PELEA;
                _combate.setPelea(2);
                _musica.ostPause(2);
                initEnemigos(15);
            }
        }
        if(i >= 12 && i <15)
        {
            if (_jugador.isColision(_enemigos[i]))
            {
                _reloj.restart();
                _eJuego = EstadoJuego::PELEA;

                _combate.setPelea(3);
                _musica.ostPause(2);
                initEnemigos(15);
            }
        }

    }

}

void MapManager::draw(sf::RenderWindow& win)
{
    if (_eJuego != EstadoJuego::MAPA)
    {
        return;
    }

    sf::View view(sf::FloatRect(0, 0, 900, 700));
    sf::Vector2f mapSize(4000.f, 3200.f);

    _jugador.updateView(view, mapSize);
    win.setView(view);

    win.draw(_camp);
    win.draw(_jugador);
    drawEnemigos(win,15);

    if (_pausa.estaActivo())
    {
        _pausa.draw(win, _inv, _eJuego, _musica);
    }
}
