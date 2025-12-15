#pragma once
#include <SFML/Graphics.hpp>
#include "inventario.h"
#include "inventarioView.h"
#include "estados.h"
#include "sound.h"
#include "game_data.h"
#include "inventario.h"
#include "registro.h"
#include "aliados.h"

class MenuPausa
{
private:
    GameData& _save;
    Registros* _registro;
    Inventario& _mochila;
    Aliado* _equipo;

    sf::Font _font;
    sf::Text _text[5];
    int _seleccion;

    sf::Texture _textura;
    sf::Sprite _sprite;

    sf::Clock _reloj;
    float _delay = 0.2f;

    Pausa _ePausa;

    sf::RectangleShape _fondo;
public:
    MenuPausa(GameData& save,Registros* reg,Inventario& inv,Aliado* equipo);

    void arriva();
    void abajo();

    int getseleccion();

    void update(Inventario& inv, EstadoJuego& eJuego,Sound& musica);

    void mostrarPausa(sf::RenderWindow& window);

    void draw(sf::RenderWindow& win, Inventario& inv, EstadoJuego& eJuego, Sound& musica);

    void activar();
    bool estaActivo();
};
