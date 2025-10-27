#include <iostream>
#include "campamento.h"
using namespace std;


Campamento::Campamento()
{
    _texture.loadFromFile("Texture/camp.png");
    _sprite.setTexture(_texture);
    _sprite.setPosition(1000,1000);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2, _sprite.getGlobalBounds().height/2);
}

void Campamento::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    target.draw(_sprite, states);
}

sf::FloatRect Campamento::getBounds() const
{
    return _sprite.getGlobalBounds();
}
