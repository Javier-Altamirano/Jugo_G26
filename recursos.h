#pragma once
#include <SFML/Graphics.hpp>

class Recursos, public sf::Drawable
{
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};
