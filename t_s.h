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
    ///=================================
    sf::Texture _texture[4];
    sf::Sprite  _sprite[4];
    ///=================================
    sf::RectangleShape barraFondo[3];
    sf::RectangleShape barraVida[3];

    sf::Text nombreAliado[3];

    int vida[3];
    int vidaMax[3];

    sf::Text vidaTexto[3];
    sf::Text energiaTexto[3];

    int energia[3];
    int energiaMax[3];
    int vidaEnemigo[3];
    int vidaMaxEnemigo[3];
    ///=================================
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
    ////=================================
    void drawBarras(sf::RenderWindow& window);
    void dibujarAliados(sf::RenderWindow& window);
    void dibujarEnemigos(sf::RenderWindow& window);
};
