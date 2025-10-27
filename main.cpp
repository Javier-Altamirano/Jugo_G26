#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "souns.h"
#include "personaje_jugador.h"
#include "enemigo.h"
#include "campamento.h"
#include "vendedor.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego"); ///Ventana
    window.setFramerateLimit(60); ///FPS

    Jugador gwen;///Gwen
    Campamento camp;///Campamento / Tienda
    Vendedor vendedor; /// NPC VENDEDOR
    bool vendedor_cerca;
    sf::Texture texura;
    texura.loadFromFile("Texture/piso.png");
    sf::Sprite sprite;
    sprite.setTexture(texura);
    ////////////////////////////
    Enemigo enemi;
    bool enemigo_cerca;
    sf::Texture texture2;
    texture2.loadFromFile("Texture/pelea.png");
    sf::Sprite sprite2;
    sprite2.setTexture(texture2);

    ///Sonido
    Sound musica;
    //-----//
    ////////////////////////////
    sf::Font fuente;
    fuente.loadFromFile("letra.ttf");

    sf::Text mensaje;
    mensaje.setFont(fuente);
    mensaje.setFillColor(sf::Color::Red);
    mensaje.setCharacterSize(16);
    const char mens[30] = "Pesiona (F)";
    const char mens2[30] = "Presiona (G) para salir";
    const char mens3[30] = "Hello Strager";
    bool mostrar_mensaje;///verifica si estas cerca para mostrar el mensaje

    /////////////////
    enum EstadoJuego { MAPA, TIENDA, PELEA };
    EstadoJuego estado = MAPA;
    enum TiendaEstado {VIENDO, COMPRANDO};
    TiendaEstado estadoT = VIENDO;
    float x,y;


    ////////FONDO
    sf::Sprite mapa;
    sf::Texture _mapa;
    _mapa.loadFromFile("Texture/pasto.png");
    mapa.setTexture(_mapa);
    ////////Funcion para seguir al personaje
    sf::View view(sf::FloatRect(0, 0, 800, 600)); // vista
    sf::Vector2f mapSize(2000.f, 2000.f); /// mapa

    sf::Vector2f mapSize2(600.f, 600.f); /// tienda


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        ///
        window.clear();
        ///Update - Actualiza los estados del juego
        ///MAPA -------------------------------------------------------
        if(estado == MAPA)
        {
            musica.mapa_chill();

            gwen.update();
            gwen.jugador_mapa();
            gwen.updateView(view, mapSize);///sigue al pj
            window.setView(view); /// actualiza la posicion de la camara

            window.draw(mapa);
            window.draw(enemi);
            window.draw(camp);
            window.draw(gwen); ///Dibuja el personaje

            enemigo_cerca = false;
            if(gwen.isColision(enemi))
            {
                mensaje.setString(mens);
                mensaje.setPosition(1525,1000);
                enemigo_cerca = true;
            }
            if(enemigo_cerca == true)
            {
                window.draw(mensaje);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                {
                    musica.mapa_chill_stop();
                    sprite2.setPosition(0,80);
                    estado = PELEA;
                }
            }
            //////////////////////////////////////////////////////////////////////
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
                    estado = TIENDA;
                    musica.mapa_chill_stop();
                    sprite.setPosition(0,0);
                    window.draw(sprite);
                    musica.open();
                    ////////
                    x = 400;
                    y = 600;
                    gwen.pos(x,y);
                }
            }
        }
        ///TIENDA--------------------------------------------------
        else if(estado == TIENDA)
        {
            musica.tienda();

            window.setView(window.getDefaultView()); // Evita vista fuera de pantalla

            window.draw(sprite);///tienda
            window.draw(vendedor);
            window.draw(gwen);

            bool interactuo = false;

            window.draw(mensaje);
            if(estadoT == VIENDO)
            {
                gwen.jugador_tienda();
                vendedor_cerca = false;
                ///ITERACTUAR CON EL VENDEDOR
                if(gwen.isColision(vendedor))
                {
                    vendedor_cerca = true;
                    mensaje.setString(mens3);
                    window.draw(mensaje);
                    mensaje.setPosition(30,230);
                }
                if(vendedor_cerca == true)
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                    {
                        estadoT = COMPRANDO;
                        window.draw(mensaje);
                        mensaje.setPosition(30,230);
                    }
                }
                ///SALIR DE LA TIENDA
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
                {
                    estado = MAPA;
                    musica.open();
                    musica.tienda_stop();
                    //////////
                    x = 1000;
                    y = 1000;
                    gwen.pos(x,y);
                }
            }
            if(estadoT == COMPRANDO)
            {
                mensaje.setString("1) Comprar X\n\n\n2) Comprar Y\n\n\nESC para salir");
                mensaje.setPosition(90, 230);
                mensaje.setCharacterSize(30);
                window.draw(mensaje);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                {
                    // Comprar X
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                {
                    // Comprar Y
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    estadoT = VIENDO;
                    mensaje.setCharacterSize(16);
                    mensaje.setString("Adios");
                    window.draw(mensaje);
                }
            }
        }
        ///PELEA----------------------------------------------------
        else if(estado == PELEA)
        {
            musica.pelea();

            window.setView(window.getDefaultView()); // Evita vista fuera de pantalla

            window.draw(sprite2);
            mensaje.setString(mens2);
            mensaje.setPosition(0, 0);
            window.draw(mensaje);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            {
                estado = MAPA;
                musica.pelea_stop();
                //////////
                x = 1525;
                y = 1000;
                gwen.pos(x,y);
            }
        }

        window.display();
    }

    return 0;
}
