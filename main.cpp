#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "souns.h"
#include "personaje_jugador.h"
#include "enemigo.h"
#include "campamento.h"
#include "vendedor.h"
#include "menu.h"
#include "items.h"
#include "inventario.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Last Guardians"); ///Ventana
    window.setFramerateLimit(60); ///FPS
    sf::Clock reloj; ///Crea un reloj
    float delay = 0.2f; // segundo

    Inventario mochila(10);
    Item pocionV(1, "P Vida", 50, 25);
    Item pocionE(2, "P Energia", 200, 100);

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
    if(!texture2.loadFromFile("Texture/pelea.png"))
    {
        std::cout << "error pelea...\n";
    }
    sf::Sprite sprite2;
    sprite2.setTexture(texture2);

    sf::Texture textPortada;
    if(!textPortada.loadFromFile("Texture/portada.png"))
    {
        //error
    }
    sf::Sprite portada;
    portada.setTexture(textPortada);

    sf::Texture textCarta;
    if(!textCarta.loadFromFile("Texture/cartilla.png"))
    {
        std::cout << "error cartilla...\n";
    }
    sf::Sprite carta;
    carta.setTexture(textCarta);

    ///Sonido
    Sound musica;
    //-----//
    ////////////////////////////
    sf::Font fuente;
    if(!fuente.loadFromFile("Font/square.ttf"))
    {
        std::cout << "error square...\n";
    }

    sf::Text vol;
    vol.setFont(fuente);

    ///recuadro de fondo
    sf::RectangleShape fondo_pausa(sf::Vector2f(800, 600));
    fondo_pausa.setFillColor(sf::Color(0, 0, 0, 150)); // negro semitransparente

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
    const char mens3[30] = "Hello Strager";
    bool mostrar_mensaje;///verifica si estas cerca para mostrar el mensaje

    /////////////////
    enum EstadoJuego { MAPA, TIENDA, PELEA, MENUINICIO, SALIR};
    EstadoJuego estado = MENUINICIO;
    bool pausa = false;
    bool mochilaA = false;
    enum TiendaEstado {VIENDO, COMPRANDO, FUERA, QUIETO};
    TiendaEstado estadoT = FUERA;
    enum Comprando {COMPRA, VENTA, NADA};
    Comprando estadoC = NADA;
    float x,y;


    ////////FONDO
    sf::Sprite mapa;
    sf::Texture _mapa;
    if(!_mapa.loadFromFile("Texture/pasto.png"))
    {
        std::cout << "error pasto...\n";
    }
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
            {
                window.close();
            }
            ///MENU INICIO----------------------------------------------
            if(estado == MENUINICIO)
            {
                musica.menu();
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::W)
                    {
                        reloj.restart();
                        //menu.arriba_inicio();
                        menu.arribaG(1);
                    }
                    else if (event.key.code == sf::Keyboard::S)
                    {
                        reloj.restart();
                        menu.abajoG(1);
                    }
                    else if (event.key.code == sf::Keyboard::F)
                    {
                        // Acción del menú (nuevo juego, cargar, salir, etc)
                        reloj.restart();
                        switch(menu.getSeleccion())
                        {
                        case 0:
                            estado = MAPA;
                            std::cout << "Iniciando Nueva Partida...\n";
                            musica.menu_stop();
                            break;
                        case 1:
                            estado = MAPA;
                            std::cout << "Cargando partida...\n";
                            musica.menu_stop();
                            break;
                        case 2:
                            std::cout << "Made for Mr. Claudio :3...\n";
                            break;
                        case 3:
                            std::cout << "Saliendo de juego... \n";
                            std::cout << "BYE BYE... \n";
                            estado = SALIR;
                            window.close();
                        }
                    }
                }
            }
            ///PAUSA----------------------------------------------
            else if(pausa == true && mochilaA == false)
            {
                if(event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if(event.key.code == sf::Keyboard::W)
                    {
                        menu.arribaG(2);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        menu.abajoG(2);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::F)
                    {
                        switch(menu.getSeleccion())
                        {
                        case 0:
                            std::cout << "Continuando...\n";
                            pausa = false;
                            estadoT = VIENDO;
                            break;
                        case 1:
                            std::cout << "Mochila...\n";
                            mochilaA = true;
                            mochila.getCantidad();
                            mochila.getCapacidadMax();
                            mochila.mostrarContenido();
                            break;
                        case 2:
                            std::cout << "Saliendo...\n";
                            musica.mapa_chill_stop();
                            estado = MENUINICIO;
                            pausa = false;
                            break;
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Escape)
                    {
                        reloj.restart();
                        estadoT = VIENDO;
                        pausa = false;
                    }
                }
            }
            ////
            else if(pausa ==  true && mochilaA == true)
            {
                if(event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if(event.key.code == sf::Keyboard::F)
                    {
                        reloj.restart();
                        mochilaA = false;
                    }
                }
            }
            ///PELEA----------------------------------------------------
            else if(estado == PELEA)
            {
                window.setView(window.getDefaultView()); // Evita vista fuera de pantalla

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
            }
            ///TIENDA--------------------------------------------------
            ///COMPRANDO
            else if(estado == TIENDA && estadoT == COMPRANDO && estadoC == NADA)
            {
                if (event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if (event.key.code == sf::Keyboard::W)
                    {
                        menu.arribaG(2);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        menu.abajoG(2);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::F)
                    {
                        reloj.restart();
                        switch(menu.getSeleccion())
                        {
                        case 0:
                            std::cout << "COMPRASTE! \n";
                            //mochila.agregarItem(pocion);
                            estadoC = COMPRA;
                            break;
                        case 1:
                            std::cout << "VENDISTE! \n";
                            //mochila.quitarItem(1);
                            estadoC = VENTA;
                            break;
                        case 2:
                            estadoT = VIENDO;
                            estadoC = NADA;
                            break;
                        }
                    }
                }
            }
            else if(estadoC == COMPRA && estadoT == COMPRANDO)
            {
                if (event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if (event.key.code == sf::Keyboard::W)
                    {
                        menu.arribaG(1);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        menu.abajoG(1);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::F)
                    {
                        reloj.restart();
                        switch(menu.getSeleccion())
                        {
                        case 0:
                            mochila.agregarItem(pocionV);
                            break;
                        case 1:
                            mochila.agregarItem(pocionE);
                            break;
                        case 2:
                            estadoC = NADA;
                            break;
                        }
                    }
                }
            }
            else if(estadoC == VENTA && estadoT == COMPRANDO)
            {
                if (event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if (event.key.code == sf::Keyboard::W)
                    {
                        menu.arribaG(1);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        menu.abajoG(1);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::F)
                    {
                        reloj.restart();
                        switch(menu.getSeleccion())
                        {
                        case 0:
                            mochila.quitarItem(1);
                            break;
                        case 1:
                            mochila.quitarItem(2);
                            break;
                        case 2:
                            estadoC = NADA;
                            break;
                        }
                    }
                }
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////////
        ///POR LAS DUDAS DE QUE CRASHEE
        if(estado == MENUINICIO)
        {

        }
        //////////////////////////////////////////////////////////////////////////////////////////
        ///MAPA -------------------------------------------------------
        if(estado == MAPA && pausa == false)
        {
            ///musica
            musica.mapa_chill();
            ///jugador
            gwen.update();
            ///Pausa
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && reloj.getElapsedTime().asSeconds() > delay)
            {
                reloj.restart();
                pausa = true;
            }
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
                    estadoT = VIENDO;
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

            ///Pausa
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && reloj.getElapsedTime().asSeconds() > delay)
            {
                reloj.restart();
                estadoT = QUIETO;
                pausa = true;
            }
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
                    estadoT = FUERA;
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
        ///VOLUMEN
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            musica.subir();
            vol.setString(std::to_string(musica.getVolumen()));
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && reloj.getElapsedTime().asSeconds() > delay)
        {
            reloj.restart();
            musica.bajar();
            vol.setString(std::to_string(musica.getVolumen()));
        }
        ////////////
        window.clear();
        ///DRAW------------------------------------------------------------------------------------
        ///menu inicio
        if(estado == MENUINICIO)
        {
            window.setView(window.getDefaultView()); // Evita vista fuera de pantall
            window.draw(portada);
            menu.mostrar_inicio(window);
            window.draw(vol);
        }
        ///mapa draw
        else if(estado == MAPA)
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
        if(pausa == true && estado == MAPA)
        {
            // Asegura que el texto esté centrado en la pantalla
            window.setView(window.getDefaultView()); // Fija la vista base
            if(mochilaA == false)
            {
                window.draw(fondo_pausa);
                // Ahora dibujas el menú de pausa, si quieres sobre el cartel

                menu.posicion(300,200);
                menu.mostrar_pausa(window);
            }
            else if(mochilaA == true)
            {
                window.draw(fondo_pausa);
                mochila.mostrar(window);
            }
        }
        ///pelea draw
        else if(estado == PELEA)
        {
            window.setView(window.getDefaultView());

            musica.pelea();

            window.draw(sprite2);
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
            if(pausa == true && estadoT == QUIETO)
            {
                window.draw(fondo_pausa);
                // Ahora dibujas el menú de pausa, si quieres sobre el cartel
                if(mochilaA == false)
                {
                    window.draw(fondo_pausa);
                    // Ahora dibujas el menú de pausa, si quieres sobre el cartel

                    menu.posicion(300,200);
                    menu.mostrar_pausa(window);
                }
                else if(mochilaA == true)
                {
                    window.draw(fondo_pausa);
                    mochila.mostrar(window);
                }

            }
            if(estado == TIENDA && estadoT == VIENDO)
            {
                if(vendedor_cerca == true)
                {
                    window.draw(mensaje);
                }
                window.draw(mensaje);
            }
            else if(estado == TIENDA && estadoT == COMPRANDO && estadoC == NADA)
            {
                window.draw(carta);
                menu.mostrar(window);
            }
            else if(estado == TIENDA && estadoT == COMPRANDO && estadoC == COMPRA)
            {
                menu.mostrar_items(window);
            }
            else if(estado == TIENDA && estadoT == COMPRANDO && estadoC == VENTA)
            {
                menu.mostrar_items(window);
            }
        }


        window.display();
    }

    return 0;
}
