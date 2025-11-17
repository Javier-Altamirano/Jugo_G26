#include <iostream>
#include "personaje_jugador.h"
using namespace std;


///constructor del personaje
Jugador::Jugador()
{
    _sprite.setPosition(400, 300);
    if(!_texture.loadFromFile("Texture/fury.png"))///carga la textura
    {
        std::cout << "error fury...\n";
    }
    _sprite.setTexture(_texture); /// asigna la textura al sprite del personaje
    _sprite.setTextureRect(sf::IntRect(0, 136, 65, 116));
    //_sprite.setScale(0.4f,0.4f);
    _velocidad = {4,4}; ///velocidad a la que lo podemos mover
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2, _sprite.getGlobalBounds().height);///coloca el eje en el centro del sprite
}
// para dibujar
void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    target.draw(_sprite, states);
}
/// Para que la camara siga al jugador
void Jugador::updateView(sf::View& view, const sf::Vector2f& mapSize)
{
    sf::Vector2f center = _sprite.getPosition();
    sf::Vector2f halfView(view.getSize().x / 2.f, view.getSize().y / 2.f);

    // Limitar la cámara dentro del mapa
    if (center.x < halfView.x) center.x = halfView.x;
    if (center.y < halfView.y) center.y = halfView.y;
    if (center.x > mapSize.x - halfView.x) center.x = mapSize.x - halfView.x;
    if (center.y > mapSize.y - halfView.y) center.y = mapSize.y - halfView.y;

    view.setCenter(center);
}
///Moviemiento del jugador
void Jugador::update()
{
    _velocidad = {0,0};
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ///Mover Arriba
    {
        _velocidad.y = -4;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ///Mover Izquierda
    {
        _velocidad.x = -4;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))///Mover Abajo
    {
        _velocidad.y = 4;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))///Mover Derecha
    {
        _velocidad.x = 4;
    }
    _sprite.move(_velocidad);
    /// Vista del Personaje
    if(_velocidad.x < 0) /// Mira para la izquierda
    {
        _sprite.setScale(-1,1);
    }
    else if(_velocidad.x > 0) /// Mira para la derecha
    {
        _sprite.setScale(1,1);
    }
    ///Posicion evita que se salga de la pantalla
    if(_sprite.getGlobalBounds().left < 0)
    {
        _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
    }
    if(_sprite.getGlobalBounds().top < 0)
    {
        _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
    }

    if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 4000)
    {
        _sprite.setPosition(4000 - (_sprite.getGlobalBounds().width - _sprite.getOrigin().x), _sprite.getPosition().y);
    }
    if(_sprite.getGlobalBounds().top+_sprite.getGlobalBounds().height > 3200)
    {
        _sprite.setPosition(_sprite.getPosition().x, 3200 + (_sprite.getGlobalBounds().height - _sprite.getOrigin().y));
    }
}
void Jugador::jugador_mapa()
{}
void Jugador::jugador_tienda()
{
    _velocidad = {0,0};
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ///Mover Arriba
    {
        _velocidad.y = -4;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ///Mover Izquierda
    {
        _velocidad.x = -4;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))///Mover Abajo
    {
        _velocidad.y = 4;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))///Mover Derecha
    {
        _velocidad.x = 4;
    }
    _sprite.move(_velocidad);
    /// Vista del Personaje
    if(_velocidad.x < 0) /// Mira para la izquierda
    {
        _sprite.setScale(-1,1);
    }
    else if(_velocidad.x > 0) /// Mira para la derecha
    {
        _sprite.setScale(1,1);
    }
    ///Posicion evita que se salga de la pantalla
    if(_sprite.getGlobalBounds().left < 0)///Borde Alto
    {
        _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
    }
    if(_sprite.getGlobalBounds().top < 0)///Borde Izquierdo
    {
        _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
    }

    if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 800)///Borde Derecho
    {
        _sprite.setPosition(800 - (_sprite.getGlobalBounds().width - _sprite.getOrigin().x), _sprite.getPosition().y);
    }
    if(_sprite.getGlobalBounds().top+_sprite.getGlobalBounds().height > 600)///Borde Bajo
    {
        _sprite.setPosition(_sprite.getPosition().x, 600 + (_sprite.getGlobalBounds().height - _sprite.getOrigin().y));
    }
}
///COLISION DEL PJ
sf::FloatRect Jugador::getBounds() const
{
    return _sprite.getGlobalBounds();
}

void Jugador::pos(float x, float y)
{
    _sprite.setPosition(x,y);
}
