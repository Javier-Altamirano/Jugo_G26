#include <iostream>
#include "t_s.h"
using namespace std;

Txt_Spt::Txt_Spt()
{
    if (!_font.loadFromFile("Font/square.ttf"))
    {
        cout << "Error al cargar fuente\n";
    }

    // ========
    string aliados[] = {"Texture/cj.png", "Texture/banana.png", "Texture/cloud.png"};
    for(int i=0; i<3; i++)
    {
        _aliadoTexture[i].loadFromFile(aliados[i]);
        _aliadoSprite[i].setTexture(_aliadoTexture[i]);
    }

    // ========
    string enemigos[] = {"Texture/gordo.png", "Texture/e1.png", "Texture/alien.png"};
    for(int i=0; i<3; i++)
    {
        _enemigoTexture[i].loadFromFile(enemigos[i]);
        _enemigoSprite[i].setTexture(_enemigoTexture[i]);
    }

    // -------------------
    std::string direccion[] =
    {
        "Texture/piso.png",
        "Texture/pelea.png",
        "Texture/portada.png",
        "Texture/mapa.png"
    };

    for (int i = 0; i < 4; i++)
    {
        if (!_texture[i].loadFromFile(direccion[i]))
            cout << "Error cargando " << direccion[i] << endl;

        _sprite[i].setTexture(_texture[i]);
    }

    // ================================
    for (int i = 0; i < 3; i++)
    {
        barraFondo[i].setSize(sf::Vector2f(204, 20));
        barraFondo[i].setFillColor(sf::Color(50, 50, 50));
        barraFondo[i].setPosition(48, 448 + (i * 40));

        barraVida[i].setSize(sf::Vector2f(200, 14));
        barraVida[i].setFillColor(sf::Color::Green);
        barraVida[i].setPosition(50, 450 + (i * 40));

        // Nombres
        nombreAliado[i].setFont(_font);
        nombreAliado[i].setString("Aliado");
        nombreAliado[i].setCharacterSize(18);
        nombreAliado[i].setFillColor(sf::Color::White);
        nombreAliado[i].setPosition(50, 425 + (i * 40));

        vidaTexto[i].setFont(_font);
        vidaTexto[i].setCharacterSize(16);
        vidaTexto[i].setFillColor(sf::Color::White);
        vidaTexto[i].setPosition(60, 446 + (i * 40));

        energiaTexto[i].setFont(_font);
        energiaTexto[i].setCharacterSize(16);
        energiaTexto[i].setFillColor(sf::Color::White);
        energiaTexto[i].setPosition(260, 446 + (i * 40));

        vida[i] = 100;
        vidaMax[i] = 100;

        energia[i] = 50;
        energiaMax[i] = 50;
    }
}

void Txt_Spt::fondos(sf::RenderWindow& window, int x)
{
    window.draw(_sprite[x]);
}

void Txt_Spt::aliens(sf::RenderWindow& window, int i)
{
    window.draw(_enemigoSprite[i]);
}

void Txt_Spt::campeon(sf::RenderWindow& window, int i)
{
    window.draw(_aliadoSprite[i]);
}

void Txt_Spt::setStatsAliado(int indice, int vidaActual, int vidaMaxima)
{
    if (indice < 0 || indice > 2) return;

    vida[indice] = vidaActual;
    vidaMax[indice] = vidaMaxima;

    if (vida[indice] > vidaMax[indice])
        vida[indice] = vidaMax[indice];

    float pct = (float)vida[indice] / vidaMax[indice];
    barraVida[indice].setSize(sf::Vector2f(200 * pct, 16));
    vidaTexto[indice].setString( to_string(vida[indice]) + " / " + to_string(vidaMax[indice]));
}
void Txt_Spt::setEnergiaAliado(int indice, int enerActual, int enerMaxima)
{
    if (indice < 0 || indice > 2) return;

    energia[indice] = enerActual;
    energiaMax[indice] = enerMaxima;

    energiaTexto[indice].setString(
        "ENERGIA: " + to_string(energia[indice]) + " / " + to_string(energiaMax[indice])
    );
}
void Txt_Spt::setNombreAliado(int indice, const std::string& nombre)
{
    if (indice < 0 || indice > 2) return;
    nombreAliado[indice].setString(nombre);
}
//////////////////////////////////////////////////////
void Txt_Spt::drawBarras(sf::RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        window.draw(barraFondo[i]);
        window.draw(barraVida[i]);
        window.draw(nombreAliado[i]);

        window.draw(vidaTexto[i]);
        window.draw(energiaTexto[i]);
    }
}

void Txt_Spt::dibujarAliados(sf::RenderWindow& window)
{
    // posiciones finales para los 3 aliados
    sf::Vector2f posiciones[3] =
    {
        {90, 150},
        {40, 200},
        {190, 190}
    };

    for (int i = 0; i < 3; i++)
    {
        if (vida[i] <= 0)
            continue;
        _aliadoSprite[i].setPosition(posiciones[i]);
        window.draw(_aliadoSprite[i]);
    }
}
void Txt_Spt::setStatsEnemigo(int id, int vidaA, int vidaM)
{
    vidaEnemigo[id] = vidaA;
    vidaMaxEnemigo[id] = vidaM;
}
void Txt_Spt::dibujarEnemigos(sf::RenderWindow& window)
{
    sf::Vector2f posiciones[3] =
    {
        {650, 250},
        {650, 350},
        {650, 450}
    };

    for (int i = 0; i < 3; i++)
    {
        if (vidaEnemigo[i] <= 0)
            continue;

        _enemigoSprite[i].setPosition(posiciones[i]);
        window.draw(_enemigoSprite[i]);
    }
}
