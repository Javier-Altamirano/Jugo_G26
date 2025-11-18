#include "game.h"

GameWorld::GameWorld(int dificultad) :
    archivo("Aliados.dat", "Enemigos.dat", "Items.dat"), _dificultad(dificultad)
{
    aliado = archivo.LeerAliado(archivo.BIA(10));
    _equipoA.push_back(archivo.LeerAliado(archivo.BIA(10)));
    _equipoA.push_back(archivo.LeerAliado(archivo.BIA(1)));
    _equipoA.push_back(archivo.LeerAliado(archivo.BIA(2)));
    enemigoBase = archivo.LeerEnemigo(0);
    enemigoCombate = enemigoBase;

    switch(_dificultad)
    {
    case 1:
        estado = Facil;
        for(int i = 0; i < 3; ++i)
        {
            _enemigos.push_back(archivo.LeerEnemigo(0));
        }
        break;
    case 2:
        estado = Medio;
        break;
    case 3:
        estado = Dificil;
        break;
    }
    _aliadoS = 0;
    _objetivo = 0;
    f = 0;
    c = 0;
    delay = 0.2f;
}
// ----------------------------------------------------------

void GameWorld::update(sf::RenderWindow& win)
{
    if (resultadoPelea == 3 || estado == GANASTE || resultadoPelea == 4)
    {
        return;
    }
    Aliado& aliadoActual = _equipoA[_aliadoS];
    win.setView(win.getDefaultView());

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                reloj.restart();
                menuP.izquierda();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                reloj.restart();
                menuP.derecha();
            }
        }
        if (reloj.getElapsedTime().asSeconds() > delay)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                reloj.restart();
                _objetivo = (_objetivo - 1 + _enemigos.size()) % _enemigos.size();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                reloj.restart();
                _objetivo = (_objetivo + 1) % _enemigos.size();
            }
        }

        // --- ACCIONES (F) ---
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            f = menuP.getFila();
            c = menuP.getColumna();

            int danio  = aliadoActual.getAtaque() - _enemigos[_objetivo].getDefensa();
            int danio2 = (aliadoActual.getAtaque() * 2) - _enemigos[_objetivo].getDefensa();

            if (f == 1 && c == 1)
            {
                std::cout << "huir...\n";
                resultadoPelea = 3;
                return;
            }

            // ATAQUE NORMAL
            if (f == 0 && c == 0)
            {
                std::cout << "Ataque...\n";
                _enemigos[_objetivo].Danio(danio);
                std::cout << "Vida restante del enemigo: "
                          << _enemigos[_objetivo].getVidaA() << "\n";
            }

            // HABILIDAD ESPECIAL
            if (f == 1 && c == 0)
            {
                std::cout << "Habilidad especial...\n";
                _enemigos[_objetivo].Danio(danio2);
                std::cout << "Vida restante del enemigo: "
                          << _enemigos[_objetivo].getVidaA() << "\n";
            }

            if (f == 0 && c == 1)
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
    }
    break;
    case Medio:
        break;
    case Dificil:
        break;
    case GANASTE:
        if(reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            resultadoPelea = 4;
            return;
        }
        break;
    }
}

void GameWorld::draw(sf::RenderWindow& win)
{
    switch (estado)
    {
    case Facil:
    {
        recursos.fondos(win, 1);

        // DIBUJAR HUD DE 3 ALIADOS + 3 ENEMIGOS
        recursos.drawCombatUnits(win, _equipoA, _enemigos);
        //recursos.status(win, _equipoA, _enemigos);

        // Menu de combate
        menuP.mostrarPelea(win);
    }
    break;

    case GANASTE:
        menuP.resultadoP(win);
        break;
    }
}

int GameWorld::resultado()
{
    return resultadoPelea;
}
void GameWorld::iniciarPelea()
{
    enemigoCombate = enemigoBase;
    resultadoPelea = 0;
    menuP.reset();
    estado = Facil;
}
void GameWorld::finalizarPelea()
{
    resultadoPelea = 0;
    menuP.reset();
    estado = Facil;
}
