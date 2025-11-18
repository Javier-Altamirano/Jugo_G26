#include <iostream>
#include "t_s.h"
using namespace std;

const float BAR_ANCHO = 150.f;
const float BAR_ALTURA = 10.f;
const float JUGADOR_X = 500.f;
const float ENEMY_X = 450.f;
const float BAR_Y = 100.f;
const float posY = 500.f;
Txt_Spt::Txt_Spt()
{
    if (!_font.loadFromFile("Font/square.ttf"))
        cout << "Error al cargar fuente\n";

    // ==== posiciones Aliados ====
    allyPos[0] = {60, 380};
    allyPos[1] = {60, 300};
    allyPos[2] = {60, 220};

    // ==== posiciones Enemigos ====
    enemyPos[0] = {650, 120};
    enemyPos[1] = {650, 200};
    enemyPos[2] = {650, 280};

    // ==== cargar texturas aliados ====
    string aliados[] = {"Texture/cj.png", "Texture/banana.png", "Texture/cloud.png"};
    for(int i=0; i<3; i++)
    {
        _aliadoTexture[i].loadFromFile(aliados[i]);
        _aliadoSprite[i].setTexture(_aliadoTexture[i]);
    }

    // ==== cargar texturas enemigos ====
    string enemigos[] = {"Texture/gordo.png", "Texture/e1.png", "Texture/alien.png"};
    for(int i=0; i<3; i++)
    {
        _enemigoTexture[i].loadFromFile(enemigos[i]);
        _enemigoSprite[i].setTexture(_enemigoTexture[i]);
    }

    // ==== inicializar barras (solo vida) ====
    for(int i=0; i<3; i++)
    {
        // Aliados
        barrasAliado[i].setSize({100, 10});
        barrasAliado[i].setFillColor(sf::Color::Green);

        // Enemigos
        barrasEnemigo[i].setSize({100, 10});
        barrasEnemigo[i].setFillColor(sf::Color::Red);
    }
    // -------------------
    // CARGAR FONDOS
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

    _sprite[1].setPosition(0,80);
}


void Txt_Spt::fondos(sf::RenderWindow& window, int x)
{
    window.draw(_sprite[x]);
}
void Txt_Spt::alien(sf::RenderWindow& window, int x)
{
    window.draw(_enemigoSprite[x]);
}
// --- MÉTODO AUXILIAR PARA CALCULAR Y ACTUALIZAR ---
void Txt_Spt::_actualizarRelleno(float currentHealth, float maxHealth, sf::RectangleShape& fillBar, sf::Text& text)
{
    // Asegura que la vida no sea negativa
    if (currentHealth < 0) currentHealth = 0;

    // 1. Calcular el porcentaje de relleno (Factor de relleno)
    float ratio = currentHealth / maxHealth;

    // 2. Aplicar el factor al ancho de la barra de relleno
    float newWidth = BAR_ANCHO * ratio;

    // NOTA: Se usa setSize. La barra se "encoge" desde la esquina superior izquierda.
    fillBar.setSize(sf::Vector2f(newWidth, BAR_ALTURA));

    // 3. Actualizar el texto
    std::string healthString = std::to_string((int)currentHealth) + " / " + std::to_string((int)maxHealth);
    text.setString(healthString);

    // Opcional: Cambiar color si la vida es baja
    if (ratio <= 0.25f)
    {
        fillBar.setFillColor(sf::Color::Red);
    }
    else if (ratio <= 0.5f)
    {
        fillBar.setFillColor(sf::Color::Yellow);
    }
    else
    {
        fillBar.setFillColor(sf::Color::Green);
    }
}
void Txt_Spt::drawCombatUnits(
    sf::RenderWindow &win,
    const std::vector<Aliado> &aliados,
    const std::vector<Enemigos> &enemigos)
{
    // =============================
    // POSICIONES — DEFINILAS A TU GUSTO
    // =============================

    // Aliados (abajo a la izquierda)
    std::vector<sf::Vector2f> allyPos =
    {
        {50, 120},   // Aliado 0
        {50, 250},   // Aliado 1
        {200, 250}   // Aliado 2
    };

    // Enemigos (derecha y arriba)
    std::vector<sf::Vector2f> enemyPos =
    {
        {580, 180},  // Enemigo 0
        {450, 280},  // Enemigo 1
        {580, 310}   // Enemigo 2
    };


    // =============================================================
    // DIBUJAR ALIADOS — ¡Listo para 3 aliados!
    // =============================================================

    std::vector<sf::Vector2f> allyHUD =
    {
        {20, 460},
        {20, 500},
        {20, 540}
    };
    for (int i = 0; i < aliados.size(); i++)
    {
        int id = aliados[i].getId();
        float ratio = aliados[i].getVidaA() / aliados[i].getVidaM();

        // Sprite del aliado en el campo
        sf::Sprite s = _aliadoSprite[id];
        s.setPosition(allyPos[i]);
        win.draw(s);

        // === HUD INFERIOR IZQUIERDO ===
        barrasBaseAliado[i].setPosition(allyHUD[i].x, allyHUD[i].y);
        win.draw(barrasBaseAliado[i]);

        barrasAliado[i].setPosition(allyHUD[i].x, allyHUD[i].y);
        barrasAliado[i].setSize({200 * ratio, 15});  // FF7 usa barras largas
        win.draw(barrasAliado[i]);
    }


    // =============================================================
    // DIBUJAR ENEMIGOS — ¡Listo para 3 enemigos!
    // =============================================================

    for (int i = 0; i < enemigos.size(); i++)
    {
        int id = enemigos[i].getId();
        float ratio = enemigos[i].getVidaA() / enemigos[i].getVidaM();

        // Sprite del enemigo
        sf::Sprite s = _enemigoSprite[id];
        s.setPosition(enemyPos[i]);
        win.draw(s);
    }
}

void Txt_Spt::status(
    sf::RenderWindow& w,
    const std::vector<Aliado>& aliados,
    const std::vector<Enemigos>& enemigos)
{
    int cantAliados = aliados.size();
    int cantEnemigos = enemigos.size();

    // --- ALIADOS ---
    for (int i = 0; i < cantAliados; i++)
    {
        float vidaA = aliados[i].getVidaA();
        float vidaM = aliados[i].getVidaM();
        float energiaA = aliados[i].getEA();
        float energiaM = aliados[i].getEM();
        int id = aliados[i].getId();

        // === mover sprite aliado ===
        _aliadoSprite[id].setPosition(allyPos[i]);

        // actualizar barras
        _actualizarBarraVida(i, vidaA, vidaM);
        _actualizarBarraEnergia(i, energiaA, energiaM);

        // dibujar sprite
        w.draw(_aliadoSprite[id]);

        // dibujar barras
        w.draw(barrasBaseAliado[i]);
        w.draw(barrasFillAliado[i]);
        w.draw(textoVidaAliado[i]);

        w.draw(energiaBaseAliado[i]);
        w.draw(energiaFillAliado[i]);
        w.draw(textoEnergiaAliado[i]);
    }

    // --- ENEMIGOS ---
    for (int i = 0; i < cantEnemigos; i++)
    {
        float vidaA = enemigos[i].getVidaA();
        float vidaM = enemigos[i].getVidaM();
        int id = enemigos[i].getId();

        // === mover sprite enemigo ===
        _enemigoSprite[id].setPosition(enemyPos[i]);

        _actualizarBarraVidaEnemigo(i, vidaA, vidaM);

        w.draw(_enemigoSprite[id]);

        w.draw(barrasBaseEnemigo[i]);
        w.draw(barrasFillEnemigo[i]);
        w.draw(textoVidaEnemigo[i]);
    }
}
void Txt_Spt::_actualizarBarraVida(int i, float vida, float max)
{
    float r = vida / max;
    if (r < 0) r = 0;

    barrasFillAliado[i].setSize({BAR_ANCHO * r, BAR_ALTURA});
    textoVidaAliado[i].setString(std::to_string((int)vida) + "/" + std::to_string((int)max));
}

void Txt_Spt::_actualizarBarraEnergia(int i, float e, float eMax)
{
    float r = e / eMax;
    if (r < 0) r = 0;

    energiaFillAliado[i].setSize({BAR_ANCHO * r, BAR_ALTURA});
    textoEnergiaAliado[i].setString(std::to_string((int)e) + "/" + std::to_string((int)eMax));
}

void Txt_Spt::_actualizarBarraVidaEnemigo(int i, float vida, float max)
{
    float r = vida / max;
    if (r < 0) r = 0;

    barrasFillEnemigo[i].setSize({BAR_ANCHO * r, BAR_ALTURA});
    textoVidaEnemigo[i].setString(std::to_string((int)vida) + "/" + std::to_string((int)max));
}

