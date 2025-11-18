#include "game.h"

GameWorld::GameWorld(int dificultad) :
    archivo("Aliados.dat", "Enemigos.dat", "Items.dat"), _dificultad(dificultad)
{
    aliado = archivo.LeerAliado(archivo.BIA(10));
    enemigoBase = archivo.LeerEnemigo(0);
    enemigoCombate = enemigoBase;

    switch(_dificultad)
    {
    case 1:
        estado = Facil;
        break;
    case 2:
        estado = Medio;
        break;
    case 3:
        estado = Dificil;
        break;
    }
    f = 0;
    c = 0;
    delay = 0.2f;
}
// ----------------------------------------------------------

void GameWorld::update(sf::RenderWindow& win)
{
    int danio = aliado.getAtaque() - enemigoCombate.getDefensa();
    int danio2 = (aliado.getAtaque() * 2) - enemigoCombate.getDefensa();
    switch (estado)
    {
    case Facil:
    {
        win.setView(win.getDefaultView());
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            menuP.arriba();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&& reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            menuP.abajo();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)&& reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            menuP.izquierda();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            menuP.derecha();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)&& reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            f = menuP.getFila();
            c = menuP.getColumna();
            if(f == 1 && c == 1)
            {
                std::cout << "huir...\n";
                resultadoPelea = 3;
            }
            if(f == 0 && c == 0)
            {
                std::cout << "Ataque...\n";
                enemigoCombate.Danio(danio);
                std::cout << "vida restante... " << enemigoCombate.getVidaA() << "\n";
            }
            if(f == 1 && c == 0)
            {
                std::cout << "Habilidad Especial...\n";
                enemigoCombate.Danio(danio2);
                std::cout << "vida restante... " << enemigoCombate.getVidaA() << "\n";
            }
            if(f == 0 && c == 1)
            {
                std::cout << "Inventario...\n";
            }
        }
        if (enemigoCombate.getVidaA() <= 0)
        {
            estado = GANASTE;
            std::cout << "Ganaste la pelea!\n";
        }
    }
    break;
    case Medio:
        break;
    case Dificil:
        break;
    case GANASTE:
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)&& reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            resultadoPelea = 4;
        }
        break;

    }
    if (resultadoPelea == 3) return;
}

void GameWorld::draw(sf::RenderWindow& win)
{
    switch (estado)
    {
    case Facil:
        recursos.fondos(win,1);
        recursos.dibujarBarras(
            win,
            aliado.getVidaA(),           // Vida Actual del Jugador
            aliado.getVidaM(),           // Vida Máxima del Jugador
            enemigoCombate.getVidaA(),   // Vida Actual del Enemigo
            enemigoCombate.getVidaM());   // Vida Máxima del Enemigo
        recursos.alien(win, 0);
        menuP.mostrarPelea(win);
        break;
    case Medio:
        break;
    case Dificil:
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
    // dejar estado interno en algo neutro que no rompa draw/update si no se llama iniciarPelea
    estado = Facil;
}
