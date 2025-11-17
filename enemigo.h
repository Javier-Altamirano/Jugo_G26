#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"

class Enemigo: public sf::Drawable, public Colision
{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
public:
    Enemigo();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
    sf::FloatRect getBounds() const override;

    void respawn();
};

