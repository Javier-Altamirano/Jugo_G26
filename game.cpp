#include "game.h"

GameWorld::GameWorld(int dificultad,Inventario& mochila) :
    archivo("Aliados.dat", "Enemigos.dat", "Items.dat"), _dificultad(dificultad),_mochila(mochila)
{
    _equipoA.push_back(archivo.LeerAliado(archivo.BIA(1)));
    _equipoA.push_back(archivo.LeerAliado(archivo.BIA(1)));
    _equipoA.push_back(archivo.LeerAliado(archivo.BIA(2)));

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

void GameWorld::update(sf::RenderWindow& win)
{
    if (resultadoPelea == 3 || resultadoPelea == 4)
    {
        return;
    }
    Aliado& aliadoActual = _equipoA[_aliadoS];
    win.setView(win.getDefaultView());

    recursos.setNombreAliado(0, _equipoA[0].getNombre());
    recursos.setStatsAliado(0, _equipoA[0].getVidaA(), _equipoA[0].getVidaM());
    recursos.setEnergiaAliado(0,_equipoA[0].getEA(),_equipoA[0].getEM());

    recursos.setNombreAliado(1, _equipoA[1].getNombre());
    recursos.setStatsAliado(1, _equipoA[1].getVidaA(), _equipoA[1].getVidaM());
    recursos.setEnergiaAliado(1,_equipoA[1].getEA(),_equipoA[1].getEM());

    recursos.setNombreAliado(2, _equipoA[2].getNombre());
    recursos.setStatsAliado(2, _equipoA[2].getVidaA(), _equipoA[2].getVidaM());
    recursos.setEnergiaAliado(2,_equipoA[2].getEA(),_equipoA[2].getEM());
    /////////////////////////////////////////////////////////////////////////////////
    recursos.setStatsEnemigo(0, _enemigos[0].getVidaA(), _enemigos[0].getVidaM());
    recursos.setStatsEnemigo(0, _enemigos[1].getVidaA(), _enemigos[1].getVidaM());
    recursos.setStatsEnemigo(0, _enemigos[2].getVidaA(), _enemigos[2].getVidaM());

    switch (estado)
    {
    case Facil:
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
            turnoActual = TURNO_ENEMIGO;

            int danio  = aliadoActual.getAtaque() - _enemigos[_objetivo].getDefensa();
            int danio2 = (aliadoActual.getAtaque() * 2) - _enemigos[_objetivo].getDefensa();

            if (_seleccion == 3)
            {
                std::cout << "huir...\n";
                resultadoPelea = 3;
                return;
            }

            // ATAQUE NORMAL
            if (_seleccion == 0)
            {
                std::cout << "Ataque...\n";
                _enemigos[_objetivo].Danio(danio);
                std::cout << "Vida restante del enemigo: "
                          << _enemigos[_objetivo].getVidaA() << "\n";
            }

            // HABILIDAD ESPECIAL
            if (_seleccion == 1)
            {
                std::cout << "Habilidad especial...\n";
                _enemigos[_objetivo].Danio(danio2);
                std::cout << "Vida restante del enemigo: "
                          << _enemigos[_objetivo].getVidaA() << "\n";
            }

            if (_seleccion == 2)
            {
                std::cout << "Inventario...\n";
            }

            // --- ELIMINAR ENEMIGO MUERTO ---
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
            // Elegir un aliado vivo al azar
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
            // Selecciona uno al azar
            int indiceObjetivo = aliadosVivos[rand() % aliadosVivos.size()];
            Aliado& objetivo = _equipoA[indiceObjetivo];
            // Enemigo objetivo (primer enemigo vivo)
            int danioEnemigo = (enemigoCombate.getAtaque()*1.5) - objetivo.getDefensa();
            if (danioEnemigo < 0) danioEnemigo = 0;

            objetivo.Danio(danioEnemigo);

            std::cout << "El enemigo ataca a " << objetivo.getNombre()
                      << " y hace " << danioEnemigo << " de daño.\n";
            if (objetivo.getVidaA() <= 0)
            {
                std::cout << objetivo.getNombre() << " ha caído!\n";

                // Revisar si todos murieron
                bool hayVivos = false;
                for (auto& a : _equipoA)
                    if (a.getVidaA() > 0)
                        hayVivos = true;

                if (!hayVivos)
                {
                    estado = PERDISTE;
                    return;
                }
            }
            turnoActual = TURNO_JUGADOR;
            return;
        }
    }
    break;
    case Medio:
        break;
    case Dificil:
        break;
    }
    if (estado == GANASTE || estado == PERDISTE)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            resultadoPelea = 3;
        }
        return;
    }
}

void GameWorld::draw(sf::RenderWindow& win)
{
    switch (estado)
    {
    case Facil:
    {
        recursos.fondos(win, 1);

        recursos.dibujarAliados(win);
        recursos.dibujarEnemigos(win);
        recursos.drawBarras(win);

        menuP.mostrarPelea(win);
    }
    break;
    case Medio:
    {
        recursos.fondos(win, 1);

        recursos.dibujarAliados(win);
        recursos.dibujarEnemigos(win);
        recursos.drawBarras(win);

        menuP.mostrarPelea(win);
    }
    break;
    case Dificil:
    {
        recursos.fondos(win, 1);

        recursos.dibujarAliados(win);
        recursos.dibujarEnemigos(win);
        recursos.drawBarras(win);

        menuP.mostrarPelea(win);
    }
    break;
    case GANASTE:
    {
        menuP.resultadoP(win);
        break;
    }
    case PERDISTE:
    {
        menuP.resultadoP(win);
        break;
    }
    }
}

int GameWorld::resultado()
{
    return resultadoPelea;
}
void GameWorld::iniciarPelea(int x)
{
    _enemigos.clear();

    // Turno aleatorio
    if (rand() % 2 == 0)
        turnoActual = TURNO_JUGADOR;
    else
        turnoActual = TURNO_ENEMIGO;

    for(int i = 0; i < 3; ++i)
    {
        _enemigos.push_back(archivo.LeerEnemigo(0));
    }

    if(x == 1) estado = Facil;
    if(x == 2) estado = Medio;
    if(x == 3) estado = Dificil;

    menuP.reset();
    resultadoPelea = 0;
}
void GameWorld::finalizarPelea()
{
}
