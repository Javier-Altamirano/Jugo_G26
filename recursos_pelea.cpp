#include "recursos_pelea.h"
#include <iostream>

using namespace std;

RecursoPelea::RecursoPelea()
{
    if (!_font.loadFromFile("Font/square.ttf"))
    {
        cout << "Error al cargar fuente\n";
    }

    // ================= ALIADOS =================
    string aliados[MAX_ALIADOS] =
    {
        "Texture/capitan.png",
        "Texture/brian.png",
        "Texture/cloud.png"
    };

    for(int i = 0; i < MAX_ALIADOS; i++)
    {
        _aliadoTexture[i].loadFromFile(aliados[i]);
        _aliadoSprite[i].setTexture(_aliadoTexture[i]);
    }

    // ================= ENEMIGOS =================
    string enemigos[MAX_ENEMIGOS] =
    {
        "Texture/gordo.png",
        "Texture/predator.png",
        "Texture/t1.png"
    };

    for(int i = 0; i < MAX_ENEMIGOS; i++)
    {
        _enemigoTexture[i].loadFromFile(enemigos[i]);
        _enemigoSprite[i].setTexture(_enemigoTexture[i]);
    }

    // ================= HUD =================
    for (int i = 0; i < MAX_ALIADOS; i++)
    {
        _barraFondo[i].setSize({204, 20});
        _barraFondo[i].setFillColor(sf::Color(50, 50, 50));
        _barraFondo[i].setPosition(48, 448 + (i * 40));

        _barraVida[i].setSize({200, 18});
        _barraVida[i].setFillColor(sf::Color::Green);
        _barraVida[i].setPosition(50, 450 + (i * 40));

        _nombreAliado[i].setFont(_font);
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
    }

    // ================= TEXTO DE COMBATE =================
    _textoAtaque.setFont(_font);
    _textoAtaque.setCharacterSize(24);
    _textoAtaque.setFillColor(sf::Color::White);
    _textoAtaque.setPosition(400, 300);
    _contadorTexto = 0;

    _flechaTex.loadFromFile("Texture/espadas.png");
    _flecha.setTexture(_flechaTex);
    _objetivoActual = 0;

}

void RecursoPelea::configurarAliados(Aliado* equipo, int cantidad)
{
    for(int i = 0; i < cantidad && i < MAX_ALIADOS; i++)
    {
        _nombreAliado[i].setString(equipo[i].getNombre());
        _nombreAliado[i].setPosition(55,425 + i *40);
    }
}

void RecursoPelea::configurarEnemigos(int cantidad, int e0, int e1, int e2)
{
    _cantidadEnemigos = cantidad;

    if(cantidad >= 1) _enemigoSprite[0] = _enemigoSprite[e0];
    if(cantidad >= 2) _enemigoSprite[1] = _enemigoSprite[e1];
    if(cantidad >= 3) _enemigoSprite[2] = _enemigoSprite[e2];
}

void RecursoPelea::draw(
    sf::RenderWindow& window,
    Aliado* equipo, int cantA,
    Enemigos* enemigos, int cantE)
{
    // --------- ALIADOS ---------
    sf::Vector2f posA[MAX_ALIADOS] =
    {
        {100, 100},
        {50, 170},
        {200, 150}
    };
    for(int i = 0; i < cantA; i++)
    {
        float pct = (float)equipo[i].getVidaA() / equipo[i].getVidaM();
        if(pct < 0)
        {
            pct = 0;
        }

        _barraVida[i].setSize({200 * pct, 16});
        _vidaTexto[i].setString(to_string(equipo[i].getVidaA()) + " / " +to_string(equipo[i].getVidaM()));
        _energiaTexto[i].setString(to_string(equipo[i].getEnergiaActual()) + " / " +to_string(equipo[i].getEnergiaMax()));

        window.draw(_barraFondo[i]);
        window.draw(_barraVida[i]);
        window.draw(_nombreAliado[i]);
        window.draw(_vidaTexto[i]);
        window.draw(_energiaTexto[i]);

        _aliadoSprite[i].setPosition(posA[i]);


        if(equipo[i].getVidaA() > 0)
        {
            window.draw(_aliadoSprite[i]);
        }
    }

    // --------- ENEMIGOS ---------
    sf::Vector2f pos[MAX_ENEMIGOS] =
    {
        {500, 120},
        {450, 200},
        {600, 190}
    };

    for(int i = 0; i < cantE; i++)
    {
        if (i == _objetivoActual && enemigos[i].getVidaA() > 0)
        {
            _flecha.setPosition(
                _enemigoSprite[i].getPosition().x + 18,
                _enemigoSprite[i].getPosition().y - 30
            );
            window.draw(_flecha);
        }

        if (i == _objetivoActual)
            _enemigoSprite[i].setColor(sf::Color::White);
        else
            _enemigoSprite[i].setColor(sf::Color(150,150,150));

        if(enemigos[i].getVidaA() > 0)
        {
            _enemigoSprite[i].setPosition(pos[i]);
            window.draw(_enemigoSprite[i]);
        }
    }
}

void RecursoPelea::activarTextoAtaque(const std::string& txt, int quien)
{
    _textoAtaque.setFillColor(quien == 1 ? sf::Color::Red : sf::Color::White);
    _textoAtaque.setString(txt);
    _contadorTexto = 120;
}

void RecursoPelea::updateTextoAtaque()
{
    if (_contadorTexto > 0)
    {
        _contadorTexto--;
    }
}

void RecursoPelea::mostrarTextoAtaque(sf::RenderWindow& window)
{
    if (_contadorTexto > 0)
    {
        window.draw(_textoAtaque);
    }
}

void RecursoPelea::setObjetivo(int objetivo)
{
    _objetivoActual = objetivo;
}
