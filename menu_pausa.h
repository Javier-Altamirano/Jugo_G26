#pragma once
#include <SFML/Graphics.hpp>

class MenuPausa:  public sf::Drawable
{
private:
    sf::Font _font;
    sf::Text _text[3];
    int _seleccion;

    sf::Texture _textura;
    sf::Sprite _sprite;
public:
    MenuPausa();
    ///Move
    void arriva();
    void abajo();

    int getseleccion();
    ///texto
    void mostrarPausa(sf::RenderWindow& window);

    ///fodo
    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

};
