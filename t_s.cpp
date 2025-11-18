#include <iostream>
#include "t_s.h"
using namespace std;

const float BAR_WIDTH = 300.f;
const float BAR_HEIGHT = 10.f;
const float PLAYER_X = 50.f;
const float ENEMY_X = 500.f;
const float BAR_Y = 100.f;

Txt_Spt::Txt_Spt()
{
    std::string direccion [] {"Texture/piso.png","Texture/pelea.png","Texture/portada.png","Texture/mapa.png"};

    for(int i=0; i<4; i++)
    {
        if(!_texture[i].loadFromFile(direccion[i]))
        {
            ///error
            cout << "Error al cargar " << direccion[i] << endl;
        }
        _sprite[i].setTexture(_texture[i]);
    }
    _sprite[1].setPosition(0,80);
    std::string otros [] {"Texture/gordo.png","Texture/e1.png","Texture/banana.png"};
    for(int i=0; i<3; i++)
    {
        if(!_enemigoTexture[i].loadFromFile(otros[i]))
        {
            ///error
        }

        _enemigoSprite[i].setTexture(_enemigoTexture[i]);
        _enemigoSprite[i].setPosition(400,300);
    }
    _enemigoSprite[0].setPosition(490,120);
    // --- INICIALIZACIÓN DE BARRAS DE VIDA ---

    // 1. Cargar la fuente para el texto
    if (!_font.loadFromFile("Font/square.ttf")) // Asume que tienes el archivo "arial.ttf"
    {
        cout << "Error al cargar la fuente." << endl;
    }

    // 2. Configurar la barra base (Contenedor, ancho fijo)
    // --- JUGADOR ---
    _playerBarBase.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
    _playerBarBase.setPosition(PLAYER_X, BAR_Y);
    _playerBarBase.setFillColor(sf::Color(50, 50, 50)); // Gris oscuro
    _playerBarBase.setOutlineThickness(2.f);
    _playerBarBase.setOutlineColor(sf::Color::White);

    // --- ENEMIGO ---
    _enemyBarBase.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
    _enemyBarBase.setPosition(ENEMY_X, BAR_Y);
    _enemyBarBase.setFillColor(sf::Color(50, 50, 50));
    _enemyBarBase.setOutlineThickness(2.f);
    _enemyBarBase.setOutlineColor(sf::Color::White);

    // 3. Configurar la barra de relleno (Fill)
    _playerBarFill.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT)); // Tamaño inicial completo
    _playerBarFill.setPosition(PLAYER_X, BAR_Y);
    _playerBarFill.setFillColor(sf::Color::Green);

    _enemyBarFill.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
    _enemyBarFill.setPosition(ENEMY_X, BAR_Y);
    _enemyBarFill.setFillColor(sf::Color::Red);

    // 4. Configurar el texto
    _playerHealthText.setFont(_font);
    _playerHealthText.setCharacterSize(18);
    _playerHealthText.setFillColor(sf::Color::White);
    _playerHealthText.setPosition(PLAYER_X + 10, BAR_Y - 5); // Posicionarlo encima o al lado

    _enemyHealthText.setFont(_font);
    _enemyHealthText.setCharacterSize(18);
    _enemyHealthText.setFillColor(sf::Color::White);
    _enemyHealthText.setPosition(ENEMY_X + 10, BAR_Y-5);

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
    float newWidth = BAR_WIDTH * ratio;

    // NOTA: Se usa setSize. La barra se "encoge" desde la esquina superior izquierda.
    fillBar.setSize(sf::Vector2f(newWidth, BAR_HEIGHT));

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

// --- MÉTODO PRINCIPAL DE DIBUJO ---
void Txt_Spt::dibujarBarras(sf::RenderWindow& window, float currentP, float maxP, float currentE, float maxE)
{
    // 1. Actualizar el estado de las barras
    _actualizarRelleno(currentP, maxP, _playerBarFill, _playerHealthText);
    _actualizarRelleno(currentE, maxE, _enemyBarFill, _enemyHealthText);

    // 2. DIBUJAR

    // Dibujar la base (el marco)
    window.draw(_playerBarBase);
    window.draw(_enemyBarBase);

    // Dibujar el relleno (lo que se mueve)
    window.draw(_playerBarFill);
    window.draw(_enemyBarFill);

    // Dibujar el texto
    window.draw(_playerHealthText);
    window.draw(_enemyHealthText);
}
