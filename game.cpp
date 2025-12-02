#include "game.h"

Combate::Combate(int dificultad,Inventario& mochila) :
    archivo("Aliados.dat", "Enemigos.dat", "Items.dat"), _dificultad(dificultad),_mochila(mochila), _mVista(mochila)
{
    _equipoA.push_back(archivo.LeerAliado(archivo.BIA(1)));
    _equipoA.push_back(archivo.LeerAliado(archivo.BIA(2)));
    _equipoA.push_back(archivo.LeerAliado(archivo.BIA(3)));

    if(!_font.loadFromFile("Font/square.ttf"))
    {
        ///error
    }
    _turno.setFont(_font);
    _turno.setCharacterSize(20);
    _turno.setPosition(50,50);


    enemigoBase = archivo.LeerEnemigo(0);
    enemigoCombate = enemigoBase;
    turnoActual = TURNO_JUGADOR;

    if(_dificultad == 1) estado = Facil;
    if(_dificultad == 2) estado = Medio;
    if(_dificultad == 3) estado = Dificil;

    _aliadoS = 0;
    _objetivo = 0;
    _seleccion = 0;
    delay = 0.2f;
}
// ----------------------------------------------------------

void Combate::update(sf::RenderWindow& win)
{
    if (_resultadoPelea != 2) return;
    if (_resultadoPelea == 0) return;
    Aliado& aliadoActual = _equipoA[_aliadoS];
    std::string turno("Turno de " + std::string(_equipoA[_aliadoS].getNombre()));
    _turno.setString(turno);
    win.setView(win.getDefaultView());

    recursos.setNombreAliado(0, _equipoA[0].getNombre());
    recursos.setStatsAliado(0, _equipoA[0].getVidaA(), _equipoA[0].getVidaM());
    recursos.setEnergiaAliado(0,_equipoA[0].getEnergiaActual(),_equipoA[0].getEnergiaMax());

    recursos.setNombreAliado(1, _equipoA[1].getNombre());
    recursos.setStatsAliado(1, _equipoA[1].getVidaA(), _equipoA[1].getVidaM());
    recursos.setEnergiaAliado(1,_equipoA[1].getEnergiaActual(),_equipoA[1].getEnergiaMax());

    recursos.setNombreAliado(2, _equipoA[2].getNombre());
    recursos.setStatsAliado(2, _equipoA[2].getVidaA(), _equipoA[2].getVidaM());
    recursos.setEnergiaAliado(2,_equipoA[2].getEnergiaActual(),_equipoA[2].getEnergiaMax());
    /////////////////////////////////////////////////////////////////////////////////
    recursos.setStatsEnemigo(0, _enemigos[0].getVidaA(), _enemigos[0].getVidaM());
    recursos.setStatsEnemigo(0, _enemigos[1].getVidaA(), _enemigos[1].getVidaM());
    recursos.setStatsEnemigo(0, _enemigos[2].getVidaA(), _enemigos[2].getVidaM());
    int energia = _equipoA[_aliadoS].getEnergiaActual();

    int coste = 20;
    if(estado == Facil && invActual == Cerrado)
    {

        if (reloj.getElapsedTime().asSeconds() > delay)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                reloj.restart();
                menuP.arriba();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                reloj.restart();
                menuP.abajo();
            }
        }
        if (reloj.getElapsedTime().asSeconds() > delay)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                reloj.restart();
                _objetivo = (_objetivo - 1 + _enemigos.size()) % _enemigos.size();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                reloj.restart();
                _objetivo = (_objetivo + 1) % _enemigos.size();
            }
        }

        // --- ACCIONES ---
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            _seleccion = menuP.getSeleccion();

            int danio  = aliadoActual.getAtaque() - _enemigos[_objetivo].getDefensa();
            int danio2 = (aliadoActual.getAtaque() * 2) - _enemigos[_objetivo].getDefensa();

            if (_seleccion == 3)
            {
                std::cout << "huir...\n";
                _resultadoPelea = 0;
                return;
            }

            // ATAQUE NORMAL
            if (_seleccion == 0)
            {
                turnoActual = TURNO_ENEMIGO;
                std::cout << "Ataque...\n";
                _enemigos[_objetivo].Danio(danio);
                std::cout << "Vida restante del enemigo: "
                          << _enemigos[_objetivo].getVidaA() << "\n";
            }

            // HABILIDAD ESPECIAL
            if (_seleccion == 1 && energia >= coste)
            {
                turnoActual = TURNO_ENEMIGO;
                energia -= coste;
                _equipoA[_aliadoS].setEnergiaActual(energia);
                std::cout << "Habilidad especial...\n";
                _enemigos[_objetivo].Danio(danio2);
                std::cout << "Vida restante del enemigo: "
                          << _enemigos[_objetivo].getVidaA() << "\n";
            }

            if (_seleccion == 2)
            {
                invActual = Abierto;
                std::cout << "Inventario...\n";
            }

            /////////////
            if (_enemigos[_objetivo].getVidaA() <= 0)
            {
                _enemigos.erase(_enemigos.begin() + _objetivo);

                if (_enemigos.empty())
                {
                    estado = GANASTE;
                    return;
                }
                _objetivo %= _enemigos.size();
            }
        }
        if (turnoActual == TURNO_ENEMIGO)
        {

            std::vector<int> aliadosVivos;
            for (int i = 0; i < _equipoA.size(); i++)
            {
                if (_equipoA[i].getVidaA() > 0)
                    aliadosVivos.push_back(i);
            }

            if (aliadosVivos.empty())
            {
                estado = PERDISTE;
                return;
            }

            int indiceObjetivo = aliadosVivos[rand() % aliadosVivos.size()];
            Aliado& objetivo = _equipoA[indiceObjetivo];

            int danioEnemigo = (enemigoCombate.getAtaque() * 2) - objetivo.getDefensa();
            if (danioEnemigo < 0) danioEnemigo = 0;

            objetivo.Danio(danioEnemigo);

            std::cout << "El enemigo ataca a " << objetivo.getNombre()
                      << " y hace " << danioEnemigo << " de daño.\n";
            if (objetivo.getVidaA() <= 0)
            {
                std::cout << objetivo.getNombre() << " ha caído!\n";

                bool hayVivos = false;

                for (int i = 0; i < _equipoA.size(); i++)
                {
                    if (_equipoA[i].getVidaA() > 0)
                    {
                        hayVivos = true;
                        break;
                    }
                }
                if (!hayVivos)
                {
                    estado = PERDISTE;
                    return;
                }
            }
            turnoActual = TURNO_JUGADOR;
            _aliadoS++;
            if(_aliadoS == 3) _aliadoS = 0;
            return;
        }
    }
    if(estado == Facil && invActual == Abierto || estado == Medio && invActual == Abierto || estado == Dificil && invActual == Abierto)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            invActual = Cerrado;
        }
        if(reloj.getElapsedTime().asSeconds() > delay)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) _mVista.arriba(),reloj.restart();;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) _mVista.abajo(),reloj.restart();;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                reloj.restart();
                if(_mVista.getSeleccion() == 0)
                {
                    _mochila.quitarItem(1);
                    _equipoA[_aliadoS].Cura(30);
                }
                if(_mVista.getSeleccion() == 1)
                {
                    _mochila.quitarItem(2);
                    _equipoA[_aliadoS].setEnergiaActual(energia + 20);
                }
            }
        }
    }
    if(estado == Medio)
    {
        if (reloj.getElapsedTime().asSeconds() > delay)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                reloj.restart();
                menuP.arriba();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                reloj.restart();
                menuP.abajo();
            }
        }
        if (reloj.getElapsedTime().asSeconds() > delay)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                reloj.restart();
                _objetivo = (_objetivo - 1 + _enemigos.size()) % _enemigos.size();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                reloj.restart();
                _objetivo = (_objetivo + 1) % _enemigos.size();
            }
        }

        // --- ACCIONES ---
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            _seleccion = menuP.getSeleccion();

            int danio  = aliadoActual.getAtaque() - _enemigos[_objetivo].getDefensa();
            int danio2 = (aliadoActual.getAtaque() * 2) - _enemigos[_objetivo].getDefensa();

            if (_seleccion == 3)
            {
                std::cout << "huir...\n";
                _resultadoPelea = 0;
                return;
            }

            // ATAQUE NORMAL
            if (_seleccion == 0)
            {
                turnoActual = TURNO_ENEMIGO;
                std::cout << "Ataque...\n";
                _enemigos[_objetivo].Danio(danio);
                std::cout << "Vida restante del enemigo: "
                          << _enemigos[_objetivo].getVidaA() << "\n";
            }

            // HABILIDAD ESPECIAL
            if (_seleccion == 1 && energia >= coste)
            {
                turnoActual = TURNO_ENEMIGO;
                energia -= coste;
                _equipoA[_aliadoS].setEnergiaActual(energia);
                std::cout << "Habilidad especial...\n";
                _enemigos[_objetivo].Danio(danio2);
                std::cout << "Vida restante del enemigo: "
                          << _enemigos[_objetivo].getVidaA() << "\n";
            }

            if (_seleccion == 2)
            {
                invActual = Abierto;
                std::cout << "Inventario...\n";
            }

            /////////////
            if (_enemigos[_objetivo].getVidaA() <= 0)
            {
                _enemigos.erase(_enemigos.begin() + _objetivo);

                if (_enemigos.empty())
                {
                    estado = GANASTE;
                    return;
                }
                _objetivo %= _enemigos.size();
            }
        }
        if (turnoActual == TURNO_ENEMIGO)
        {

            std::vector<int> aliadosVivos;
            for (int i = 0; i < _equipoA.size(); i++)
            {
                if (_equipoA[i].getVidaA() > 0)
                    aliadosVivos.push_back(i);
            }

            if (aliadosVivos.empty())
            {
                estado = PERDISTE;
                return;
            }

            int indiceObjetivo = aliadosVivos[rand() % aliadosVivos.size()];
            Aliado& objetivo = _equipoA[indiceObjetivo];

            int danioEnemigo = (enemigoCombate.getAtaque() *2) - objetivo.getDefensa();
            if (danioEnemigo < 0) danioEnemigo = 0;

            objetivo.Danio(danioEnemigo);

            std::cout << "El enemigo ataca a " << objetivo.getNombre()
                      << " y hace " << danioEnemigo << " de daño.\n";
            if (objetivo.getVidaA() <= 0)
            {
                std::cout << objetivo.getNombre() << " ha caído!\n";

                bool hayVivos = false;

                for (int i = 0; i < _equipoA.size(); i++)
                {
                    if (_equipoA[i].getVidaA() > 0)
                    {
                        hayVivos = true;
                        break;
                    }
                }
                if (!hayVivos)
                {
                    estado = PERDISTE;
                    return;
                }
            }
            turnoActual = TURNO_JUGADOR;
            _aliadoS++;
            if(_aliadoS == 3) _aliadoS = 0;
            return;
        }
    }
    if(estado == Dificil)
    {
        if (reloj.getElapsedTime().asSeconds() > delay)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                reloj.restart();
                menuP.arriba();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                reloj.restart();
                menuP.abajo();
            }
        }
        if (reloj.getElapsedTime().asSeconds() > delay)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                reloj.restart();
                _objetivo = (_objetivo - 1 + _enemigos.size()) % _enemigos.size();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                reloj.restart();
                _objetivo = (_objetivo + 1) % _enemigos.size();
            }
        }

        // --- ACCIONES ---
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            _seleccion = menuP.getSeleccion();

            int danio  = aliadoActual.getAtaque() - _enemigos[_objetivo].getDefensa();
            int danio2 = (aliadoActual.getAtaque() * 2) - _enemigos[_objetivo].getDefensa();

            if (_seleccion == 3)
            {
                std::cout << "huir...\n";
                _resultadoPelea = 0;
                return;
            }

            // ATAQUE NORMAL
            if (_seleccion == 0)
            {
                turnoActual = TURNO_ENEMIGO;
                std::cout << "Ataque...\n";
                _enemigos[_objetivo].Danio(danio);
                std::cout << "Vida restante del enemigo: "
                          << _enemigos[_objetivo].getVidaA() << "\n";
            }

            // HABILIDAD ESPECIAL
            if (_seleccion == 1 && energia >= coste)
            {
                turnoActual = TURNO_ENEMIGO;
                energia -= coste;
                _equipoA[_aliadoS].setEnergiaActual(energia);
                std::cout << "Habilidad especial...\n";
                _enemigos[_objetivo].Danio(danio2);
                std::cout << "Vida restante del enemigo: "
                          << _enemigos[_objetivo].getVidaA() << "\n";
            }

            if (_seleccion == 2)
            {
                invActual = Abierto;
                std::cout << "Inventario...\n";
            }

            /////////////
            if (_enemigos[_objetivo].getVidaA() <= 0)
            {
                _enemigos.erase(_enemigos.begin() + _objetivo);

                if (_enemigos.empty())
                {
                    estado = GANASTE;
                    return;
                }
                _objetivo %= _enemigos.size();
            }
        }
        if (turnoActual == TURNO_ENEMIGO)
        {

            std::vector<int> aliadosVivos;
            for (int i = 0; i < _equipoA.size(); i++)
            {
                if (_equipoA[i].getVidaA() > 0)
                    aliadosVivos.push_back(i);
            }

            if (aliadosVivos.empty())
            {
                estado = PERDISTE;
                return;
            }

            int indiceObjetivo = aliadosVivos[rand() % aliadosVivos.size()];
            Aliado& objetivo = _equipoA[indiceObjetivo];

            int danioEnemigo = enemigoCombate.getAtaque() - objetivo.getDefensa();
            if (danioEnemigo < 0) danioEnemigo = 0;

            objetivo.Danio(danioEnemigo);

            std::cout << "El enemigo ataca a " << objetivo.getNombre()
                      << " y hace " << danioEnemigo << " de daño.\n";
            if (objetivo.getVidaA() <= 0)
            {
                std::cout << objetivo.getNombre() << " ha caído!\n";

                bool hayVivos = false;

                for (int i = 0; i < _equipoA.size(); i++)
                {
                    if (_equipoA[i].getVidaA() > 0)
                    {
                        hayVivos = true;
                        break;
                    }
                }
                if (!hayVivos)
                {
                    estado = PERDISTE;
                    return;
                }
            }
            turnoActual = TURNO_JUGADOR;
            _aliadoS++;
            if(_aliadoS == 3) _aliadoS = 0;
            return;
        }
    }
    if (estado == PERDISTE)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            int recompensa = 50;
            _resultadoPelea = -1;
            _mochila.setSaldo(recompensa);
            _equipoA[0].Revivir();
            _equipoA[1].Revivir();
            _equipoA[2].Revivir();
        }
        return;
    }
    if (estado == GANASTE)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            int recompensa = _mochila.getsaldo() + (25 * _dificultad);
            _mochila.setSaldo(recompensa);
            _resultadoPelea = 1;
        }
        return;
    }
}

void Combate::draw(sf::RenderWindow& win)
{
    switch (estado)
    {
    case Facil:
    {
        recursos.fondos(win, 1);

        recursos.dibujarAliados(win);
        recursos.dibujarEnemigos(win);
        recursos.drawBarras(win);
        win.draw(_turno);

        if(invActual == Abierto)
            _mVista.MostrarxPela(win);

        menuP.mostrarPelea(win);
    }
    break;
    case Medio:
    {
        recursos.fondos(win, 1);

        recursos.dibujarAliados(win);
        recursos.dibujarEnemigos(win);
        recursos.drawBarras(win);
        win.draw(_turno);

        if(invActual == Abierto)
            _mVista.MostrarxPela(win);

        menuP.mostrarPelea(win);
    }
    break;
    case Dificil:
    {
        recursos.fondos(win, 1);

        recursos.dibujarAliados(win);
        recursos.dibujarEnemigos(win);
        recursos.drawBarras(win);
        win.draw(_turno);

        if(invActual == Abierto)
            _mVista.MostrarxPela(win);

        menuP.mostrarPelea(win);
    }
    break;
    case GANASTE:
    {
        menuP.resultadoP(win, 1);
        break;
    }
    case PERDISTE:
    {
        recursos.fondos(win,4);
        menuP.resultadoP(win, 0);
        break;
    }
    }
}

int Combate::resultado()
{
    return _resultadoPelea;
}
void Combate::iniciarPelea(int x)
{
    _enemigos.clear();


    if (rand() % 2 == 0)
    {
        turnoActual = TURNO_JUGADOR;
    }
    else
    {
        turnoActual = TURNO_ENEMIGO;
    }
    if (x == 1)
    {
        _enemigos.push_back(archivo.LeerEnemigo(0));
        _enemigos.push_back(archivo.LeerEnemigo(0));
        _enemigos.push_back(archivo.LeerEnemigo(0));
        recursos.configurarEnemigos(3, 0, 0, 0);
        estado = Facil;
    }
    else if (x == 2)
    {
        _enemigos.push_back(archivo.LeerEnemigo(0));
        _enemigos.push_back(archivo.LeerEnemigo(0));
        _enemigos.push_back(archivo.LeerEnemigo(1));
        recursos.configurarEnemigos(3, 1, 1, 2);
        estado = Medio;
    }
    else if (x == 3)
    {
        _enemigos.push_back(archivo.LeerEnemigo(2));
        recursos.configurarEnemigos(1, 2, 0, 0);
        estado = Dificil;
    }

    for (int i = 0; i < 3; i++)
    {
        if (i < _enemigos.size())
            recursos.setStatsEnemigo(i, _enemigos[i].getVidaA(), _enemigos[i].getVidaM());
        else
            recursos.setStatsEnemigo(i, 0, 1);
    }

    menuP.reset();
    _resultadoPelea = 2;
}
void Combate::finalizarPelea()
{
}
