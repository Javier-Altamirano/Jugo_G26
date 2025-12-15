#include <iostream>
#include "tiendaManager.h"
using namespace std;

TiendaManager::TiendaManager(Inventario& inv,EstadoJuego& eJuego,TiendaEstado& eTienda,Jugador& jugador,Sound& musica,Aliado* equipo,MenuPausa& pausa)
    :_inv(inv), _eJuego(eJuego), _eTienda(eTienda), _jugador(jugador), _musica(musica),_equipo(equipo), _pausa(pausa)
{
    _camp.pos(400,560);
    _comprando = Comprando::NADA;
}

void TiendaManager::setItems(std::vector<Item> items)
{
    _items = items;
}

void TiendaManager::update()
{
    int costo;
    if(_eJuego == EstadoJuego::TIENDA)
    {
        _musica.ostPlay(1);
        if(_eTienda == TiendaEstado::DENTRO && _comprando == Comprando::NADA)
        {
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

            _jugador.update(2);

            if(_jugador.isColision(_vendedor))
            {
                if(_reloj.getElapsedTime().asSeconds() > _delay)
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                    {
                        _reloj.restart();
                        _eTienda = TiendaEstado::INTERACTUANDO;
                        _comprando = Comprando::MENU;
                        _musica.efectos(4);
                    }
                }
            }
            if(_jugador.isColision(_camp))
            {
                if(_reloj.getElapsedTime().asSeconds() > _delay)
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                    {
                        _reloj.restart();
                        _musica.ostPause(1);
                        _eJuego = EstadoJuego::MAPA;
                        _eTienda = TiendaEstado::FUERA;
                        _jugador.pos(1100,800);
                    }
                }
            }
        }

        if(_eTienda == TiendaEstado::INTERACTUANDO && _comprando == Comprando::MENU)
        {

            if(_reloj.getElapsedTime().asSeconds() > _delay)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    _reloj.restart();
                    _menu.arriba(1);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    _reloj.restart();
                    _menu.abajo(1);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                {
                    _reloj.restart();
                    switch(_menu.getseleccion(1))
                    {
                    case 0:
                        ///COMPRAR
                        _comprando = Comprando::COMPRA;
                        break;
                    case 1:
                        ///VENDER
                        _comprando = Comprando::VENTA;
                        break;
                    case 2:
                        ///RECUPERAR EQUIPO
                        if(_inv.getsaldo() >= 100)
                        {
                            costo = _inv.getsaldo() - 100;
                            _inv.setSaldo(costo);
                            for(int i=0; i<3; i++)
                                _equipo[i].Revivir();
                            _musica.efectos(5);
                        }
                        else
                        {
                            _musica.efectos(1);
                        }
                        break;
                    case 3:
                        ///SALIR
                        _comprando = Comprando::NADA;
                        _eTienda = TiendaEstado::DENTRO;
                        break;
                    }
                }
            }
        }

        if(_eTienda == TiendaEstado::INTERACTUANDO && _comprando == Comprando::COMPRA)
        {
            if(_reloj.getElapsedTime().asSeconds() > _delay)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    _reloj.restart();
                    _menu.arriba(2);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    _reloj.restart();
                    _menu.abajo(2);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                {
                    _reloj.restart();
                    switch(_menu.getseleccion(2))
                    {
                    case 0:
                        if(_inv.agregarItem(_items[0]) == true, true)
                        {
                            _musica.efectos(5);
                        }
                        else
                        {
                            _musica.efectos(1);
                        }
                        break;
                    case 1:
                        if(_inv.agregarItem(_items[1]) == true, true)
                        {
                            _musica.efectos(5);
                        }
                        else
                        {
                            _musica.efectos(1);
                        }
                        break;
                    case 2:
                        ///ATRAS
                        _comprando = Comprando::MENU;
                        break;
                    }
                }
            }
        }

        if(_eTienda == TiendaEstado::INTERACTUANDO && _comprando == Comprando::VENTA)
        {
            if(_reloj.getElapsedTime().asSeconds() > _delay)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    _reloj.restart();
                    _menu.arriba(3);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    _reloj.restart();
                    _menu.abajo(3);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                {
                    _reloj.restart();

                    switch(_menu.getseleccion(3))
                    {
                    case 0:
                        if(_inv.quitarItem(_items[0].getId(), true) == true)
                        {
                            _musica.efectos(5);
                        }
                        else
                        {
                            _musica.efectos(1);
                        }
                        break;
                    case 1:
                        if(_inv.quitarItem(_items[1].getId(), true) == true)
                        {
                            _musica.efectos(5);
                        }
                        else
                        {
                            _musica.efectos(1);
                        }
                        break;
                    case 2:
                        ///ATRAS
                        _comprando = Comprando::MENU;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        return;
    }
}

void TiendaManager::draw(sf::RenderWindow& win)
{
    InventarioView view(_inv);
    if(_eJuego == EstadoJuego::TIENDA)
    {
        win.setView(win.getDefaultView());

        if(_eTienda == TiendaEstado::DENTRO && _comprando == Comprando::NADA)
        {
            win.draw(_vendedor);
            win.draw(_jugador);
            win.draw(_camp);

            if (_pausa.estaActivo())
            {
                _pausa.draw(win, _inv, _eJuego, _musica);
            }
        }
        if(_eTienda == TiendaEstado::INTERACTUANDO)
        {
            _menu.draw(win);
            if(_comprando == Comprando::MENU)
            {
                _menu.mostrar(win);
                view.mostrar_saldo(win,2);
            }
            if(_comprando == Comprando::COMPRA)
            {
                _menu.mostrarCompra(win);
                view.mostrar_saldo(win,2);
            }
            if(_comprando == Comprando::VENTA)
            {
                _menu.mostrarVenta(win);
                view.mostrar_saldo(win,2);
            }
        }
    }
}
