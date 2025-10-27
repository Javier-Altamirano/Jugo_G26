#include <iostream>
#include "vendedor.h"
using namespace std;


Vendedor::Vendedor()
{
    _texture.loadFromFile("Texture/buhonero.png");
    _sprite.setTexture(_texture);
    _sprite.setPosition(30,300);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2, _sprite.getGlobalBounds().height/2);
}

void Vendedor::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    target.draw(_sprite, states);
}

sf::FloatRect Vendedor::getBounds() const
{
    return _sprite.getGlobalBounds();
}

