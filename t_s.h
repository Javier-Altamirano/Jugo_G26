#pragma once
#include <SFML/Graphics.hpp>

class Txt_Spt
{
private:
    sf::Font _font;
    ///=================================
    sf::Texture _aliadoTexture[3];
    sf::Sprite  _aliadoSprite[3];

    sf::Texture _enemigoTexture[3];
    sf::Sprite  _enemigoSprite[3];
    sf::Sprite _enemigosEnPelea[3];
    int _cantidadEnemigos;
    ///=================================
    sf::Texture _texture[5];
    sf::Sprite  _sprite[5];
    ///=================================
    sf::RectangleShape _barraFondo[3];
    sf::RectangleShape _barraVida[3];

    sf::Text _nombreAliado[3];

    int _vida[3];
    int _vidaMax[3];

    sf::Text _vidaTexto[3];
    sf::Text _energiaTexto[3];

    int _energia[3];
    int _energiaMax[3];
    int _vidaEnemigo[3];
    int _vidaMaxEnemigo[3];
    ///=================================
    sf::Texture _indicadorTex;
    sf::Sprite _indicadorTurno;
    sf::Sprite _indicadorSeleccion;
public:
    Txt_Spt();

    void fondos(sf::RenderWindow& window, int x);
    void aliens(sf::RenderWindow& window, int i);
    void campeon(sf::RenderWindow& window, int i);

    ////=================================
    void setStatsAliado(int indice, int vidaActual, int vidaMaxima);
    void setNombreAliado(int indice, const std::string& nombre);
    void setEnergiaAliado(int indice, int enerActual, int enerMaxima);
    void setStatsEnemigo(int id, int vidaA, int vidaM);
    void configurarEnemigos(int cant, int e0, int e1, int e2);
    ////=================================
    void drawBarras(sf::RenderWindow& window);
    void dibujarAliados(sf::RenderWindow& window);
    void dibujarEnemigos(sf::RenderWindow& window);
};
