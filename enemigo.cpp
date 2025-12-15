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
        _velocidad = {5,5};
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
        _time = 60 * 5;
        _sprite.setPosition(std::rand() % 4000 + _sprite.getGlobalBounds().width, std::rand() % 3000 + _sprite.getGlobalBounds().height);
    }

    void Enemigo::update()
    {
        //_sprite.move( _velocidad);
        _time--;
        if(_time < 0)
        {
            respawn();
        }
    }
