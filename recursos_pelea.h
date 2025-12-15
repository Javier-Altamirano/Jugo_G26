#pragma once
#include <SFML/Graphics.hpp>
#include "aliados.h"
#include "enemigos.h"


constexpr int MAX_ALIADOS  = 3;
constexpr int MAX_ENEMIGOS = 3;

class Aliado;
class Enemigos;

class RecursoPelea
{
private:
    sf::Font _font;

    // ================= Sprites =================
    sf::Texture _aliadoTexture[MAX_ALIADOS];
    sf::Sprite  _aliadoSprite[MAX_ALIADOS];

    sf::Texture _enemigoTexture[MAX_ENEMIGOS];
    sf::Sprite  _enemigoSprite[MAX_ENEMIGOS];

    int _cantidadEnemigos = 0;
    // ================= HUD =================
    sf::RectangleShape _barraFondo[MAX_ALIADOS];
    sf::RectangleShape _barraVida[MAX_ALIADOS];

    sf::Text _nombreAliado[MAX_ALIADOS];
    sf::Text _vidaTexto[MAX_ALIADOS];
    sf::Text _energiaTexto[MAX_ALIADOS];

    // ================= Texto combate =================
    sf::Text _textoAtaque;
    int _contadorTexto = 0;

    // ================ OBJETIBOS ======================
    sf::Sprite _flecha;
    sf::Texture _flechaTex;

    int _objetivoActual;

public:
    RecursoPelea();

    // ---------- Fondo ----------
    void fondos(sf::RenderWindow& window, int x);

    // ---------- Configuración ----------
    void configurarAliados(Aliado* equipo, int cantidad);
    void configurarEnemigos(int cantidad, int e0, int e1, int e2);

    // ---------- Dibujo ----------
    void draw(
    sf::RenderWindow& window,
    Aliado* equipo,
    int cantA,
    Enemigos* enemigos,
    int cantE);

    // ---------- Feedback ----------
    void activarTextoAtaque(const std::string& txt, int quien);
    void updateTextoAtaque();
    void mostrarTextoAtaque(sf::RenderWindow& window);

    void setObjetivo(int objetivo);

};
