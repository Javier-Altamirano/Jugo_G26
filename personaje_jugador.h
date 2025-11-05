#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"

class Jugador: public sf::Drawable, public Colision
{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _velocidad;
public:
    Jugador();
    void updateView(sf::View& view, const sf::Vector2f& mapSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
    sf::FloatRect getBounds() const override;

    void pos(float x, float y);
    ///JOYSTICK
    void update();
    void jugador_mapa();
    void jugador_tienda();
};
