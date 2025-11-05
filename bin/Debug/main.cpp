#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "souns.h"
#include "personaje_jugador.h"
#include "enemigo.h"
#include "campamento.h"
#include "vendedor.h"
#include "menu.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego"); ///Ventana
    window.setFramerateLimit(60); ///FPS
    sf::Clock reloj; ///Crea un reloj
    float delay = 0.2f; // segundo

    Jugador gwen;///Gwen
    Campamento camp;///Campamento / Tienda
    bool camp_cerca;
    Vendedor vendedor; /// NPC VENDEDOR
    Menu menu; ///TODOS LOS MENUS
    int f,c;
    bool vendedor_cerca;
    sf::Texture texura;
    if(!texura.loadFromFile("Texture/piso.png"))
    {
        std::cout << "error\n";
    }
    sf::Sprite sprite;
    sprite.setTexture(texura);
    ////////////////////////////
    Enemigo enemi;
    bool enemigo_cerca;
    sf::Texture texture2;
    texture2.loadFromFile("Texture/pelea.png");
    sf::Sprite sprite2;
    sprite2.setTexture(texture2);

    sf::Texture textCarta;
    textCarta.loadFromFile("Texture/cartilla.png");
    sf::Sprite carta;
    carta.setTexture(textCarta);

    ///Sonido
    Sound musica;
    //-----//
    ////////////////////////////
    sf::Font fuente;
    fuente.loadFromFile("Font/square.ttf");

    sf::Text mensaje;
    sf::Text mensaje_camp;
    mensaje_camp.setFont(fuente);
    mensaje_camp.setCharacterSize(20);
    mensaje_camp.setFillColor(sf::Color::Red);
    const char mens[30] = "Pesiona (F)";
    mensaje_camp.setString(mens);

    mensaje.setFont(fuente);
    mensaje.setFillColor(sf::Color::Red);
    mensaje.setCharacterSize(30);
    const char mens2[30] = "COMBATE";
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
            ///PELEA----------------------------------------------------
            else if(estado == PELEA)
            {
                window.setView(window.getDefaultView()); // Evita vista fuera de pantalla

                mensaje.setString(mens2);
                mensaje.setPosition(0, 0);
                if (event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if (event.key.code == sf::Keyboard::W)
                    {
                        menu.arriba_pelea();
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        menu.abajo_pelea();
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::A)
                    {
                        menu.izquierda();
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::D)
                    {
                        menu.derecha();
                        reloj.restart();
                    }
                }
                if(event.key.code == sf::Keyboard::F && reloj.getElapsedTime().asSeconds() > delay)
                {
                    reloj.restart();
                    f = menu.getFila();
                    c = menu.getColumna();
                    if(f == 0 && c == 0)
                    {
                        std::cout << "PELEA\n";
                    }
                    else if(f == 0 && c == 1)
                    {
                        std::cout << "MOCHILA\n";
                    }
                    else if(f == 1 && c == 0)
                    {
                        std::cout << "DEFIENDE\n";
                    }
                    else if(f == 1 && c == 1)
                    {
                        std::cout << "SALIR\n";
                        estado = MAPA;
                        musica.pelea_stop();
                        musica.mapa_chill();
                        x = 1525;
                        y = 1000;
                        gwen.pos(x,y);
                    }
                }
            }
            ///TIENDA--------------------------------------------------
            ///COMPRANDO
            else if(estado == TIENDA && estadoT == COMPRANDO)
            {
                if (event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if (event.key.code == sf::Keyboard::W)
                    {
                        menu.arriba();
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        menu.abajo();
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::F)
                    {
                        reloj.restart();
                        switch(menu.getSeleccion())
                        {
                        case 0:
                            std::cout << "COMPRASTE! \n";
                            break;
                        case 1:
                            std::cout << "VENDISTE! \n";
                            break;
                        case 2:
                            estadoT = VIENDO;
                            break;
                        }
                    }
                }
            }
        }
        ///MAPA -------------------------------------------------------
        if(estado == MAPA)
        {
            ///musica
            musica.mapa_chill();
            ///jugador
            gwen.update();
            ///evalua al enemigo
            enemigo_cerca = false;
            if(gwen.isColision(enemi))
            {
                mensaje.setString(mens);
                mensaje.setPosition(1525,1000);
                enemigo_cerca = true;
            }
            if(enemigo_cerca == true)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
                {
                    reloj.restart();
                    musica.mapa_chill_stop();
                    sprite2.setPosition(0,80);
                    estado = PELEA;
                }
            }
            ///evalua alidaos
            camp_cerca = false;
            if(gwen.isColision(camp))
            {
                mensaje_camp.setPosition(1025,1000);
                camp_cerca = true;
            }
            if(camp_cerca == true)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
                {
                    estado = TIENDA;
                    musica.mapa_chill_stop();
                    musica.tienda();
                    sprite.setPosition(0,0);
                    musica.open();
                    reloj.restart();
                    ////////
                    x = 400;
                    y = 600;
                    gwen.pos(x,y);
                    camp.pos(400,570);
                }
            }
        }
        ///TIENDA--------------------------------------------------
        ///VIENDO
        else if(estado == TIENDA && estadoT == VIENDO)
        {
            ///movimiento
            gwen.jugador_tienda();

            ///interactuar con vendedor
            vendedor_cerca = false;
            if(gwen.isColision(vendedor))
            {
                vendedor_cerca = true;
                mensaje.setString(mens3);
                mensaje.setPosition(30,230);
            }
            if(vendedor_cerca == true)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
                {
                    estadoT = COMPRANDO;
                    carta.setPosition(200,100);
                }
            }
            ///salir
            mostrar_mensaje = false;
            if(gwen.isColision(camp))
            {
                mensaje.setPosition(400,600);
                mostrar_mensaje = true;
            }
            if(mostrar_mensaje == true)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
                {
                    estado = MAPA;
                    musica.mapa_chill();
                    musica.tienda_stop();
                    reloj.restart();
                    //////////
                    x = 1000;
                    y = 1000;
                    gwen.pos(x,y);
                    camp.pos(1000,1000);
                }
            }
        }
        ////////////
        window.clear();
        ///DRAW------------------------------------------------------------------------------------
        ///mapa draw
        if(estado == MAPA)
        {
            gwen.updateView(view, mapSize);///sigue al pj
            window.setView(view); /// actualiza la posicion de la camara


            window.draw(mapa);
            window.draw(enemi);
            window.draw(camp);
            window.draw(gwen); ///Dibuja el personaje

            if(camp_cerca == true)
            {
                window.draw(mensaje_camp);
            }
        }
        ///pelea draw
        else if(estado == PELEA)
        {
            window.setView(window.getDefaultView());

            musica.pelea();

            window.draw(sprite2);
            window.draw(mensaje);
            menu.mostrar_pelea(window);
        }
        ///tirnda draw
        else if(estado == TIENDA)
        {
            window.setView(window.getDefaultView()); // Evita vista fuera de pantalla

            window.draw(sprite);
            window.draw(gwen);
            window.draw(vendedor);
            window.draw(camp); ///simula puerta
            if(estado == TIENDA && estadoT == VIENDO)
            {
                if(vendedor_cerca == true)
                {
                    window.draw(mensaje);
                }
                window.draw(mensaje);
            }
            else if(estado == TIENDA && estadoT == COMPRANDO)
            {
                window.draw(carta);
                menu.mostrar(window);
            }
        }
        window.display();
    }

    return 0;
}
