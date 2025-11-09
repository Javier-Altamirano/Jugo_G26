#pragma once
#include "personajes.h"
#include <SFML/Graphics.hpp>

class Jugables : protected Personajes, public sf::Drawable
{
private:
public:
    Personajes(int id, const std::string& nombre, int vidaM, int vidaA, int ataque, int defensa, bool vivo)
    : Jugables(id, nombre, vidaM, vidaA, ataque, defensa, vivo){}


    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};

