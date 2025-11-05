#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"

class Vendedor: public sf::Drawable, public Colision
{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
public:
    Vendedor();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
    sf::FloatRect getBounds() const override;
    void mensage();
};
