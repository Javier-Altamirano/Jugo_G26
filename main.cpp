#include <SFML/Graphics.hpp>
#include <iostream>
#include "personaje_jugador.h"
#include "campamento.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego"); ///Ventana
    window.setFramerateLimit(60); ///FPS

    Jugador gwen;///Gwen
    Campamento camp;///Campamento
    sf::Texture texura;
    texura.loadFromFile("tienda.png");
    sf::Sprite sprite;
    sprite.setTexture(texura);

    sf::Font fuente;
    fuente.loadFromFile("letra.ttf");

    sf::Text mensaje;
    mensaje.setFont(fuente);
    const char mens[30] = "Pesiona F";
    const char mens2[30] = "Presiona (ESC) para salir";
    bool mostrar_mensaje;///verifica si estas cerca para mostrar el mensaje

    /////////////////
    bool esena = false;


    ////////FONDO
    sf::Sprite mapa;
    sf::Texture _mapa;
    _mapa.loadFromFile("pasto.png");
    mapa.setTexture(_mapa);
    ////////Funcion para seguir al personaje
    sf::View view(sf::FloatRect(0, 0, 800, 600)); // vista
    sf::Vector2f mapSize(2000.f, 2000.f); /// mapa


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ///
        window.clear();
        ///Update - Actualiza los estados del juego
        if(esena == false)
        {
            gwen.update();
            gwen.updateView(view, mapSize);///sigue al pj
            window.setView(view); /// actualiza la posicion de la camara

            window.draw(mapa);
            window.draw(camp);
            window.draw(gwen); ///Dibuja el personaje

            mostrar_mensaje = false;
            if(gwen.isColision(camp))
            {
                mensaje.setString(mens);
                mensaje.setPosition(1025,1000);
                mostrar_mensaje = true;
            }
            if(mostrar_mensaje == true)
            {
                window.draw(mensaje);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                {
                    esena = true;
                    sprite.setPosition(750,750);
                    window.draw(sprite);
                }
            }
        }

        if(esena == true)
        {

            mensaje.setString(mens2);
            mensaje.setPosition(600,700);
            window.draw(sprite);
            window.draw(mensaje);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                esena = false;
            }
        }

        window.display();
    }

    return 0;
}
