#include <iostream>
#include "combate_back.h"
using namespace std;


Combate::Combate(EstadoJuego& eJuego,Inventario& mochila,Registros* r,EstadoCombate& combat,TiendaEstado& eTienda,Jugador& jugador,Sound& musica,GameData& save)
    :_archivo("Aliados.dat", "Enemigos.dat", "Items.dat"),
     _mochila(mochila),_registro(r),_invView(mochila),_combate(combat),
     _eTienda(eTienda),_jugador(jugador),_eJuego(eJuego),_musica(musica), _save(save)
{
    _delay = 0.2f;
    _fLiberada = true;
    cout << "Combate creado: " << this << endl;
}

void Combate::setPelea(int dificultad)
{
    _cantEnemigos = 3;
    _enemigoActual = 0;
    _aliadoActual = 0;
    _objetivo = 0;
    _registro->sumarCombates();
    _invActual = Cerrado;

    _combate = EstadoCombate::LUCHANDO;
    if (rand() % 2 == 0)
    {
        _turno = TurnoCombate::JUGADOR;
    }
    else
    {
        _turno = TurnoCombate::ENEMIGO;
        _relojTurnoEnemigo.restart();
    }


    if(dificultad == 1)
    {
        _bonus = 1.5;
        _dificultad = Facil;
        for(int i=0; i<3; i++)
        {
            _enemigos[i] = _archivo.LeerEnemigo(_archivo.BIE(1));
        }
        _recursos.configurarEnemigos(3,0,0,0);
    }
    if(dificultad == 2)
    {
        _bonus = 2.1;
        _dificultad = Medio;
        _enemigos[0] = _archivo.LeerEnemigo(_archivo.BIE(1));
        _enemigos[1] = _archivo.LeerEnemigo(_archivo.BIE(2));
        _enemigos[2] = _archivo.LeerEnemigo(_archivo.BIE(1));
        _recursos.configurarEnemigos(3,0,1,0);
    }
    if(dificultad == 3)
    {
        _bonus = 2.6;
        _dificultad = Dificil;
        _enemigos[0] = _archivo.LeerEnemigo(_archivo.BIE(2));
        _enemigos[1] = _archivo.LeerEnemigo(_archivo.BIE(3));
        _enemigos[2] = _archivo.LeerEnemigo(_archivo.BIE(2));
        _recursos.configurarEnemigos(3,1,2,1);
    }

}

void Combate::update(sf::RenderWindow& win, Inventario& inv,Aliado* equipo,int cantidadA)
{

    if(_eJuego != EstadoJuego::PELEA)
    {
        return;
    }

    if (_combate == EstadoCombate::LUCHANDO)
    {
        _musica.ostPlay(0);
        _recursos.configurarAliados(equipo, cantidadA);

        switch (_turno)
        {
        case TurnoCombate::JUGADOR:

            turnoAliado(inv, equipo, _enemigos);
            break;

        case TurnoCombate::ESPERANDO_ENEMIGO:

            if (_relojTurnoEnemigo.getElapsedTime().asSeconds() >= 2.f)
            {
                _turno = TurnoCombate::ENEMIGO;
            }
            break;

        case TurnoCombate::ENEMIGO:

            turnoEnemigo(_enemigos, equipo,cantidadA);

            _turno = TurnoCombate::ESPERANDO_JUGADOR;
            _reloj.restart();
            break;

        case TurnoCombate::ESPERANDO_JUGADOR:

            if (_reloj.getElapsedTime().asSeconds() >= _delay)
            {
                _turno = TurnoCombate::JUGADOR;
            }
            break;
        }
    }
    if(_combate == EstadoCombate::PERDISTE)
    {
        _musica.ostPause(0);
        if(_reloj.getElapsedTime().asSeconds() > _delay && sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            _jugador.pos(500,200);
            _combate = EstadoCombate::FUERA;
            _eTienda = TiendaEstado::DENTRO;
            _eJuego = EstadoJuego::TIENDA;
            _registro->sumarDerrota();
        }
    }
    if(_combate == EstadoCombate::HUIR)
    {
        _musica.ostPause(0);
        _eJuego = EstadoJuego::MAPA;
        _combate = EstadoCombate::FUERA;
        _registro->sumarNulas();
    }
    if(_combate == EstadoCombate::GANASTE)
    {
        cout << "GANASTE" <<endl;
        _musica.ostPause(0);
        if(_reloj.getElapsedTime().asSeconds() > _delay && sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            _eJuego = EstadoJuego::MAPA;
            _combate = EstadoCombate::FUERA;
            int ganancia = inv.getsaldo() + (35 * _bonus);
            inv.setSaldo(ganancia);
            _registro->sumarVictoria();
        }
    }
    if(_combate == EstadoCombate::GANASTE ||
        _combate == EstadoCombate::PERDISTE ||
        _combate == EstadoCombate::HUIR)
    {
        _save.setEquipo(equipo);
        _save.setInventario(_mochila);
        _save.setRegistros(*_registro);
        _save.guardar("save.dat");
    }
    /// ==================================================
    _recursos.setObjetivo(_objetivo);
    _recursos.draw(win, equipo, cantidadA, _enemigos,_cantEnemigos);
    _menuP.mostrarPelea(win);
    _recursos.mostrarTextoAtaque(win);
    _recursos.updateTextoAtaque();
    if(_invActual == Abierto)
    {
        _invView.MostrarxPela(win);
    }
}

void Combate::turnoEnemigo(Enemigos* enemigos, Aliado* aliados, int cantidadAliados)
{
    int objetivo = rand() % cantidadAliados;

    int intentos = 0;
    while (aliados[objetivo].getVidaA() <= 0 && intentos < cantidadAliados)
    {
        objetivo = rand() % cantidadAliados;
        intentos++;
    }

    if (aliados[objetivo].getVidaA() <= 0)
    {
        return;
    }

    int danio = enemigos[_enemigoActual].getAtaque() - aliados[objetivo].getDefensa();

    if (danio < 0) danio = 0;

    aliados[objetivo].Danio(danio);

    _recursos.activarTextoAtaque("- " + to_string(danio), 1);

    cout << enemigos[_enemigoActual].getNombre()<< " atacó a "<< aliados[objetivo].getNombre()<< " por " << danio << endl;

    switch(aliados[objetivo].getId())
    {
    case 1:
        _musica.combatePlay(5);
        break;
    case 2:
        _musica.combatePlay(5);
        break;
    case 3:
        _musica.combatePlay(2);
        break;
    }
    _enemigoActual++;

    if (_enemigoActual >= _cantEnemigos)
    {
        _enemigoActual = 0;
        _turno = TurnoCombate::JUGADOR;
    }
}


void Combate::turnoAliado(Inventario& inv,Aliado* aliadoActual,Enemigos* enemgoActual)
{
    if(_turno != TurnoCombate::JUGADOR)
    {
        return;
    }

    if (todosAliadosMuertos(aliadoActual, 3))
    {
        _combate = EstadoCombate::PERDISTE;
        _reloj.restart();
        return;
    }
    if (aliadoActual[_aliadoActual].getVidaA() <= 0)
    {
        avanzarAliado(aliadoActual, 3);
        return;
    }


    if (_objetivo >= _cantEnemigos) _objetivo = 0;


    if(_invActual == Abierto)
    {
        usarItem(aliadoActual);
    }
    else
    {
        if (_reloj.getElapsedTime().asSeconds() > _delay)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && _adLiberada)
            {
                avanzarObjetivo(-1, enemgoActual);
                _adLiberada = false;
                _reloj.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && _adLiberada)
            {
                avanzarObjetivo(+1, enemgoActual);
                _adLiberada = false;
                _reloj.restart();
            }

            int danio1 = aliadoActual[_aliadoActual].getAtaque() - enemgoActual[_objetivo].getDefensa();
            int danio2 = (aliadoActual[_aliadoActual].getAtaque() * 1.5) - enemgoActual[_objetivo].getDefensa();
            int costo = 35;

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                _adLiberada = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                _reloj.restart();
                _menuP.arriba();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                _reloj.restart();
                _menuP.abajo();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && _fLiberada == true)
            {
                _fLiberada = false;
                _reloj.restart();
                avanzarAliado(aliadoActual, 3);

                if(_menuP.getSeleccion() == 0)
                {
                    switch(aliadoActual[_aliadoActual].getId())
                    {
                    case 1:
                        _musica.combatePlay(3);
                        break;
                    case 2:
                        _musica.combatePlay(6);
                        break;
                    case 3:
                        _musica.combatePlay(0);
                        break;
                    }
                    int vidaAntes = enemgoActual[_objetivo].getVidaA();

                    enemgoActual[_objetivo].Danio(danio1);

                    int vidaDespues = enemgoActual[_objetivo].getVidaA();


                    if (vidaAntes > 0 && vidaDespues <= 0)
                    {
                        int id = enemgoActual[_objetivo].getId();

                        if(id == 1) _registro->derrotarColeccionistas();
                        if(id == 2) _registro->derrotarCazadores();
                        if(id == 3) _registro->derrotarJefe();
                    }

                    _registro->agregarDanio(danio1);
                    if (todosEnemigosMuertos())
                    {
                        _combate = EstadoCombate::GANASTE;
                        return;
                    }

                    _recursos.activarTextoAtaque(std::string(aliadoActual[_aliadoActual].getNombre()) + "ataco -" + to_string(danio1),0);
                    cout << aliadoActual[_aliadoActual].getNombre() << " " << danio1 << endl;
                    cout << aliadoActual[_aliadoActual].getAtaque() << endl;
                    cout << _objetivo << " "<< enemgoActual[_objetivo].getNombre() << "  "<<enemgoActual[_objetivo].getVidaA() << endl;

                    _turno = TurnoCombate::ESPERANDO_ENEMIGO;
                    _relojTurnoEnemigo.restart();
                    return;
                }
                if(_menuP.getSeleccion() == 1)
                {
                    if(aliadoActual[_aliadoActual].getEnergiaActual() >= costo)
                    {
                        switch(aliadoActual[_aliadoActual].getId())
                        {
                        case 1:
                            _musica.combatePlay(4);
                            break;
                        case 2:
                            _musica.combatePlay(6);
                            break;
                        case 3:
                            _musica.combatePlay(1);
                            break;
                        }
                        aliadoActual[_aliadoActual].setEnergiaActual(-costo);
                        cout << aliadoActual[_aliadoActual].getEnergiaActual() << endl;
                        int vidaAntes = enemgoActual[_objetivo].getVidaA();

                        enemgoActual[_objetivo].Danio(danio2);

                        int vidaDespues = enemgoActual[_objetivo].getVidaA();


                        if (vidaAntes > 0 && vidaDespues <= 0)
                        {
                            int id = enemgoActual[_objetivo].getId();

                            if(id == 1) _registro->derrotarColeccionistas();
                            if(id == 2) _registro->derrotarCazadores();
                            if(id == 3) _registro->derrotarJefe();
                        }

                        _registro->agregarDanio(danio2);

                        if (todosEnemigosMuertos())
                        {
                            _combate = EstadoCombate::GANASTE;
                            return;
                        }

                        cout << aliadoActual[_aliadoActual].getNombre() << " " << danio2 << endl;
                        _recursos.activarTextoAtaque("-" + to_string(danio2),0);

                        _turno = TurnoCombate::ESPERANDO_ENEMIGO;
                        _relojTurnoEnemigo.restart();
                        return;
                    }
                    else
                    {
                        _recursos.activarTextoAtaque("Energia insuficiente",0);
                    }
                }
                if(_menuP.getSeleccion() == 2)
                {
                    _invActual = Abierto;
                }
                if(_menuP.getSeleccion() == 3)
                {
                    _combate = EstadoCombate::HUIR;
                }
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                _fLiberada = true;
            }
        }
    }
}
bool Combate::todosEnemigosMuertos()
{
    for (int i = 0; i < _cantEnemigos; i++)
    {
        if (_enemigos[i].getVidaA() > 0) return false;
    }
    return true;
}
bool Combate::todosAliadosMuertos(Aliado* aliados, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (aliados[i].getVidaA() > 0) return false;
    }
    return true;
}
void Combate::avanzarObjetivo(int dir, Enemigos* enemigos)
{
    if (todosEnemigosMuertos()) return;

    int intentos = 0;
    do
    {
        _objetivo += dir;

        if (_objetivo < 0)
        {
            _objetivo = _cantEnemigos - 1;
        }
        else if (_objetivo >= _cantEnemigos)
        {
            _objetivo = 0;
        }

        intentos++;
    }
    while (enemigos[_objetivo].getVidaA() <= 0 && intentos < _cantEnemigos);
}

void Combate::avanzarAliado(Aliado* aliados, int cantidad)
{
    int intentos = 0;

    do
    {
        _aliadoActual++;

        if (_aliadoActual >= cantidad) _aliadoActual = 0;

        intentos++;
    }
    while (aliados[_aliadoActual].getVidaA() <= 0 && intentos < cantidad);
}

void Combate::usarItem(Aliado* aliadoActual)
{
    if(_reloj.getElapsedTime().asSeconds() > _delay)
    {
        if (_mochila.getCantidad() == 0)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                _reloj.restart();
                _invActual = Cerrado;
            }
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                _reloj.restart();
                _invView.arriba();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                _reloj.restart();
                _invView.abajo();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                _reloj.restart();
                _invActual = Cerrado;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                _reloj.restart();
                switch(_invView.getSeleccion())
                {
                case 0:
                    if(_mochila.quitarItem(1,false) == true)
                    {
                        aliadoActual[_aliadoActual].Cura(50);
                        _recursos.activarTextoAtaque("+ 50 HP",0);
                        _turno = TurnoCombate::ESPERANDO_ENEMIGO;
                    }
                    break;
                case 1:
                    if(_mochila.quitarItem(2,false) == true)
                    {
                        aliadoActual[_aliadoActual].setEnergiaActual(80);
                        _recursos.activarTextoAtaque("+ 80 EN",0);
                        _turno = TurnoCombate::ESPERANDO_ENEMIGO;
                    }
                    break;
                }
            }
        }
    }
}
