#include <iostream>
#include "vendedor.h"
using namespace std;


Vendedor::Vendedor()
{
    if(!_texture.loadFromFile("Texture/buhonero.png"))
    {
        std::cout << "error buhonero...\n";
    }
    _sprite.setTexture(_texture);
    _sprite.setPosition(300,250);
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

