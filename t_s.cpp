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
    string aliados[] = {"Texture/messi.png", "Texture/banana.png", "Texture/cloud.png"};
    for(int i=0; i<3; i++)
    {
        _aliadoTexture[i].loadFromFile(aliados[i]);
        _aliadoSprite[i].setTexture(_aliadoTexture[i]);
    }

    // ========
    string enemigos[] = {"Texture/gordo.png", "Texture/e1.png", "Texture/t1.png"};
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
        _barraFondo[i].setSize(sf::Vector2f(204, 20));
        _barraFondo[i].setFillColor(sf::Color(50, 50, 50));
        _barraFondo[i].setPosition(48, 448 + (i * 40));

        _barraVida[i].setSize(sf::Vector2f(200, 14));
        _barraVida[i].setFillColor(sf::Color::Green);
        _barraVida[i].setPosition(50, 450 + (i * 40));

        _nombreAliado[i].setFont(_font);
        _nombreAliado[i].setString("Aliado");
        _nombreAliado[i].setCharacterSize(18);
        _nombreAliado[i].setFillColor(sf::Color::White);
        _nombreAliado[i].setPosition(50, 425 + (i * 40));

        _vidaTexto[i].setFont(_font);
        _vidaTexto[i].setCharacterSize(16);
        _vidaTexto[i].setFillColor(sf::Color::White);
        _vidaTexto[i].setPosition(60, 446 + (i * 40));

        _energiaTexto[i].setFont(_font);
        _energiaTexto[i].setCharacterSize(16);
        _energiaTexto[i].setFillColor(sf::Color::White);
        _energiaTexto[i].setPosition(260, 446 + (i * 40));

        _vida[i] = 100;
        _vidaMax[i] = 100;

        _energia[i] = 50;
        _energiaMax[i] = 50;
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

    _vida[indice] = vidaActual;
    _vidaMax[indice] = vidaMaxima;

    if (_vida[indice] > _vidaMax[indice])
        _vida[indice] = _vidaMax[indice];

    float pct = (float)_vida[indice] / _vidaMax[indice];
    _barraVida[indice].setSize(sf::Vector2f(200 * pct, 16));
    _vidaTexto[indice].setString( to_string(_vida[indice]) + " / " + to_string(_vidaMax[indice]));
}
void Txt_Spt::setEnergiaAliado(int indice, int enerActual, int enerMaxima)
{
    if (indice < 0 || indice > 2) return;

    _energia[indice] = enerActual;
    _energiaMax[indice] = enerMaxima;

    _energiaTexto[indice].setString(
        "ENERGIA: " + to_string(_energia[indice]) + " / " + to_string(_energiaMax[indice])
    );
}
void Txt_Spt::setNombreAliado(int indice, const std::string& nombre)
{
    if (indice < 0) return;
    _nombreAliado[indice].setString(nombre);
}
//////////////////////////////////////////////////////
void Txt_Spt::drawBarras(sf::RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        window.draw(_barraFondo[i]);
        window.draw(_barraVida[i]);
        window.draw(_nombreAliado[i]);

        window.draw(_vidaTexto[i]);
        window.draw(_energiaTexto[i]);
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
        if (_vida[i] <= 0)
            continue;
        _aliadoSprite[i].setPosition(posiciones[i]);
        window.draw(_aliadoSprite[i]);
    }
}
void Txt_Spt::setStatsEnemigo(int id, int vidaA, int vidaM)
{
    _vidaEnemigo[id] = vidaA;
    _vidaMaxEnemigo[id] = vidaM;
}
void Txt_Spt::dibujarEnemigos(sf::RenderWindow& window)
{
    sf::Vector2f posiciones[3] =
    {
        {500, 150},
        {450, 200},
        {600, 190}
    };

    for (int i = 0; i < _cantidadEnemigos; i++)
    {
        _enemigosEnPelea[i].setPosition(posiciones[i]);
        window.draw(_enemigosEnPelea[i]);
    }
}
void Txt_Spt::configurarEnemigos(int cant, int e0, int e1, int e2)
{
    _cantidadEnemigos = cant;

    if (cant >= 1) _enemigosEnPelea[0] = _enemigoSprite[e0];
    if (cant >= 2) _enemigosEnPelea[1] = _enemigoSprite[e1];
    if (cant >= 3) _enemigosEnPelea[2] = _enemigoSprite[e2];
}
