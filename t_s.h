#pragma once
#include <SFML/Graphics.hpp>

class Txt_Spt
{
private:
    sf::Texture _teture[4];

    sf::Sprite _sprite[4];

    // La forma base (contenedor) para la barra del Jugador (Player) y Enemigo (Enemy)
    sf::RectangleShape _playerBarBase;
    sf::RectangleShape _enemyBarBase;

    // La parte que se rellena (FILL) para la barra del Jugador y Enemigo
    sf::RectangleShape _playerBarFill;
    sf::RectangleShape _enemyBarFill;

    // Para el texto de vida (Ej: 80/100)
    sf::Font _font;
    sf::Text _playerHealthText;
    sf::Text _enemyHealthText;
    void _actualizarRelleno(float currentHealth, float maxHealth, sf::RectangleShape& fillBar, sf::Text& text);


public:
    Txt_Spt();
    void fondos(sf::RenderWindow& window, int x);
    void dibujarBarras(sf::RenderWindow& window, float currentP, float maxP, float currentE, float maxE);

};
