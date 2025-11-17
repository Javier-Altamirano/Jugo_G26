#include <iostream>
#include "enemigo.h"
using namespace std;


Enemigo::Enemigo()
{
    if(!_texture.loadFromFile("Texture/alien.png"))
    {
        std::cout << "error alien...\n";
    }
    _sprite.setTexture(_texture);
    _sprite.setPosition(1500,1000);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2, _sprite.getGlobalBounds().height/2);
}

void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    target.draw(_sprite, states);
}

sf::FloatRect Enemigo::getBounds() const
{
    return _sprite.getGlobalBounds();
}

void Enemigo::respawn()
{
    _sprite.setPosition(200,200);
}
