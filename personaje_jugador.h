#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "colision.h"
#include "souns.h"

class Jugador: public sf::Drawable, public Colision, public Sound
{
private:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
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
