#pragma once
#include <SFML/Graphics.hpp>
#include "enemigos.h"
#include "aliados.h"

class Txt_Spt
{
private:
    // ---- posiciones de aliados y enemigos ----
    sf::Vector2f allyPos[3];
    sf::Vector2f enemyPos[3];

    // ---- sprites y texturas ----
    sf::Texture _aliadoTexture[3];
    sf::Sprite  _aliadoSprite[3];

    sf::Texture _enemigoTexture[3];
    sf::Sprite  _enemigoSprite[3];

    // ---- barras simples (las que usás en drawCombatUnits) ----
    sf::RectangleShape barrasAliado[3];
    sf::RectangleShape barrasEnemigo[3];

    // ---- barras completas (vida + energía) ----
    sf::RectangleShape barrasBaseAliado[3];
    sf::RectangleShape barrasFillAliado[3];
    sf::Text textoVidaAliado[3];

    sf::RectangleShape energiaBaseAliado[3];
    sf::RectangleShape energiaFillAliado[3];
    sf::Text textoEnergiaAliado[3];

    sf::RectangleShape barrasBaseEnemigo[3];
    sf::RectangleShape barrasFillEnemigo[3];
    sf::Text textoVidaEnemigo[3];

    // ---- fuente ----
    sf::Font _font;

    // ---- fondos ----
    sf::Texture _texture[4];
    sf::Sprite _sprite[4];

    // funciones internas
    void _actualizarBarraVida(int i, float vida, float max);
    void _actualizarBarraEnergia(int i, float e, float eMax);
    void _actualizarBarraVidaEnemigo(int i, float vida, float max);



    sf::RectangleShape _playerBarBase;
    sf::RectangleShape _enemyBarBase;

    // La parte que se rellena (FILL) para la barra del Jugador y Enemigo
    sf::RectangleShape _playerBarFill;
    sf::RectangleShape _enemyBarFill;

    sf::Text _playerHealthText;
    sf::Text _enemyHealthText;
    void _actualizarRelleno(float currentHealth, float maxHealth, sf::RectangleShape& fillBar, sf::Text& text);


public:
    Txt_Spt();
    void fondos(sf::RenderWindow& window, int x);
    void alien(sf::RenderWindow& window, int x);
    void status(sf::RenderWindow& w,const std::vector<Aliado>& aliados,const std::vector<Enemigos>& enemigos);
    void dibujarBarras(sf::RenderWindow& window, float currentP, float maxP, float currentE, float maxE);

    void drawCombatUnits(sf::RenderWindow& win,const std::vector<Aliado>& aliados,const std::vector<Enemigos>& enemigos);
};
