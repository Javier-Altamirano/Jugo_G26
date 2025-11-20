#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "souns.h"
#include "personaje_jugador.h"
#include "enemigo.h"
#include "enemigos.h"
#include "campamento.h"
#include "vendedor.h"
#include "menu.h"
#include "menu_pausa.h"
#include "menu_pelea.h"
#include "tienda_menu.h"
#include "t_s.h"
#include "items.h"
#include "inventario.h"
#include "archivos.h"
#include "inventarioView.h"
#include "game.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Last Guardians"); ///Ventana
    window.setFramerateLimit(60); ///FPS
    sf::Clock reloj; ///Crea un reloj
    float delay = 0.2f; // segundo

    MenuPausa mp;
    MenuPelea mpelea;
    TiendaMenu tiendM;
    int menuDeseado;

    Inventario mochila;
    InventarioView inventView(mochila);
    Archivos archivos("Aliados.dat","Enemigos.dat","Items.dat");
    //Item pocionV(1, "Hierva Verde", 50, 25,1);
    //Item pocionE(2, "Monster Mango Loco", 70, 35,1);
    /// ========>> ITEMS <<========
    Item pocionV = archivos.LeerItem(0);
    Item pocionE = archivos.LeerItem(1);
    /// ========>> ALIADOS <<========
    //Aliado a1(1,"Messi",540,540,67,37,300,300,true);
   // Aliado a2(2,"Ford",620,620,55,42,300,300,true);
    //Aliado a3(3,"Claudio",600,600,50,42,300,300,true);


    Combate world(1,mochila);
    int ca = archivos.CantEnemigoG();
    std::cout << "Cantidad detectada por CantAliadoG() = " << ca << std::endl;
    Aliado* lista = new Aliado[ca];
    archivos.LeerAT(lista, ca);
    for(int i = 0; i < ca; i++)
    {
        std::cout << "-> enemigos " << i << " nombre: '" << lista[i].getNombre() << "'" << std::endl;
        std::cout << "-> enemigos " << i << " nombre: '" << lista[i].getId() << "'" << std::endl;
    }
    delete[] lista;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///Sonido
    Sound musica;
    Txt_Spt sprites;
    Jugador gwen;///Gwen JUGADO ****************************
    Campamento camp;///Campamento / Tienda
    Vendedor vendedor; /// NPC VENDEDOR
    Menu menu; ///TODOS LOS MENUS
    Enemigo enemi; ///ENEMIGO
    Enemigo e1,e2,e3,e4,e5,e6,e7,e8;
    //int f,c; ///POSICION DE FILA Y COLUMNA
    bool camp_cerca;
    bool vendedor_cerca;
    bool enemigo_cerca;
    ////////////////////////////
    ////////Funcion para seguir al personaje
    sf::View view(sf::FloatRect(0, 0, 800, 600)); // vista
    sf::Vector2f mapSize(4000.f, 3200.f); /// mapa
    ////////////////////////////
    sf::Font fuente;
    if(!fuente.loadFromFile("Font/square.ttf"))
    {
        std::cout << "error square...\n";
    }
    sf::Text vol;
    vol.setFont(fuente);
    sf::Text _acercaDe;
    _acercaDe.setFont(fuente);
    _acercaDe.setString("TP Integrador de Programacion 2\nIntegrantes\nJavier Francisco Altamirano\nLucia Aylen Maffey\nGrupo 26!!");
    _acercaDe.setCharacterSize(40);
    _acercaDe.setPosition(100,80);
    ///recuadro de fondo
    sf::RectangleShape fondo_pausa(sf::Vector2f(800, 600));
    fondo_pausa.setFillColor(sf::Color(0, 0, 0, 150)); // negro semitransparente

    sf::Text mensaje;
    sf::Text mensaje_camp;
    mensaje_camp.setFont(fuente);
    mensaje_camp.setCharacterSize(20);
    mensaje_camp.setFillColor(sf::Color::White);
    const char mens[30] = "Pesiona (F)";
    mensaje_camp.setString(mens);

    bool mostrar_mensaje;///verifica si estas cerca para mostrar el mensaje
    bool ganaste = false;
    ///----------------- >FUNCIONES DE ESTADO <---------------------------
    enum EstadoJuego { MAPA, TIENDA, PELEA, MENUINICIO, SALIR, CINEMATICA};
    enum TiendaEstado {VIENDO, COMPRANDO, FUERA, QUIETO};
    enum Comprando {COMPRA, VENTA, NADA};
    EstadoJuego estado = MENUINICIO;
    TiendaEstado estadoT = FUERA;
    Comprando estadoC = NADA;
    bool pausa = false;
    bool mochilaA = false;
    float x,y;

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
                        menu.arriba();
                    }
                    else if (event.key.code == sf::Keyboard::S)
                    {
                        reloj.restart();
                        menu.abajo();
                    }
                    else if (event.key.code == sf::Keyboard::F)
                    {
                        // Acción del menú (nuevo juego, cargar, salir, etc)
                        reloj.restart();
                        switch(menu.getSeleccion())
                        {
                        case 0:
                            std::cout << "Iniciando Nueva Partida...\n";
                            estado = MAPA;
                            gwen.pos(1500,1000);
                            musica.ok();
                            musica.menu_stop();
                            break;
                        case 1:
                            estado = CINEMATICA;
                            break;
                        case 2:
                            estado = SALIR;
                            window.close();
                            break;
                        }
                    }
                }
            }
            ///
            ///PAUSA----------------------------------------------
            else if(pausa == true && mochilaA == false)
            {
                if(event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if(event.key.code == sf::Keyboard::W)
                    {
                        mp.arriva();
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        mp.abajo();
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::F)
                    {
                        switch(mp.getseleccion())
                        {
                        case 0:
                            std::cout << "Continuando...\n";
                            pausa = false;
                            estadoT = VIENDO;
                            break;
                        case 1:
                            std::cout << "Inventario...\n";
                            mochilaA = true;
                            mochila.getCantidad();
                            mochila.getCapacidadMax();
                            mochila.mostrarContenido();
                            break;
                        case 2:
                            std::cout << "Saliendo...\n";
                            musica.mapa_chill_stop();
                            musica.tienda_stop();
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
            ///TIENDA--------------------------------------------------
            ///COMPRANDO
            else if(estado == TIENDA && estadoT == COMPRANDO && estadoC == NADA)
            {
                menuDeseado = 1;
                if (event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if (event.key.code == sf::Keyboard::W)
                    {
                        tiendM.arriba(menuDeseado);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        tiendM.abajo(menuDeseado);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::F)
                    {
                        reloj.restart();
                        switch(tiendM.getseleccion(menuDeseado))
                        {
                        case 0:
                            std::cout << "Comprando... \n";
                            estadoC = COMPRA;
                            break;
                        case 1:
                            std::cout << "Vendiendo... \n";
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
                menuDeseado = 2;
                if (event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if (event.key.code == sf::Keyboard::W)
                    {
                        tiendM.arriba(menuDeseado);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        tiendM.abajo(menuDeseado);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::F)
                    {
                        reloj.restart();
                        switch(tiendM.getseleccion(menuDeseado))
                        {
                        case 0:
                            if(mochila.agregarItem(pocionV))
                                musica.thanks();
                            else
                                musica.nop();
                            break;
                        case 1:
                            if(mochila.agregarItem(pocionE))
                                musica.thanks();
                            else
                                musica.nop();
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
                menuDeseado = 3;
                if (event.type == sf::Event::KeyPressed && reloj.getElapsedTime().asSeconds() > delay)
                {
                    if (event.key.code == sf::Keyboard::W)
                    {
                        tiendM.arriba(menuDeseado);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::S)
                    {
                        tiendM.abajo(menuDeseado);
                        reloj.restart();
                    }
                    else if(event.key.code == sf::Keyboard::F)
                    {
                        reloj.restart();
                        switch(tiendM.getseleccion(menuDeseado))
                        {
                        case 0:
                            if(mochila.quitarItem(pocionV.getId()) == true)
                                musica.thanks();
                            else
                                musica.nop();
                            break;
                        case 1:
                            if(mochila.quitarItem(pocionE.getId()) == true)
                                musica.thanks();
                            else
                                musica.nop();
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
        ///PELEA----------------------------------------------------
        else if (estado == PELEA)
        {
            if(world.resultado() == 2)
            {
                world.update(window);
            }
            int r = world.resultado();

            if (r == 1 || r == 0)
            {
                musica.pelea_stop();
                reloj.restart();
                enemi.respawn();
                e1.respawn();
                e2.respawn();
                e3.respawn();
                e4.respawn();
                e5.respawn();
                e6.respawn();
                e7.respawn();
                e8.respawn();
                estado = MAPA;
                continue;
            }
            if(r == -1)
            {
                estado = MENUINICIO;
                musica.pelea_stop();
                estado = MENUINICIO;
                world.iniciarPelea(1);
                world.iniciarPelea(2);
                world.iniciarPelea(3);
                continue;
            }
        }
        else if(estado == CINEMATICA)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
            {
                estado = MENUINICIO;
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////////
        ///MAPA -------------------------------------------------------
        if(estado == MAPA && pausa == false)
        {
            enemi.update();
            e1.update();
            e2.update();
            e3.update();
            e4.update();
            e5.update();
            e6.update();
            e7.update();
            e8.update();
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
                reloj.restart();
                musica.ok2();
                musica.mapa_chill_stop();
                estado = PELEA;
                world.iniciarPelea(3);
            }
            if(gwen.isColision(e1) || gwen.isColision(e2) || gwen.isColision(e3) || gwen.isColision(e4))
            {
                mensaje.setString(mens);
                mensaje.setPosition(1525,1000);
                enemigo_cerca = true;
                reloj.restart();
                musica.ok2();
                musica.mapa_chill_stop();
                estado = PELEA;
                world.iniciarPelea(1);
            }
            if(gwen.isColision(e5) || gwen.isColision(e6) || gwen.isColision(e7) || gwen.isColision(e8))
            {
                mensaje.setString(mens);
                mensaje.setPosition(1525,1000);
                enemigo_cerca = true;
                reloj.restart();
                musica.ok2();
                musica.mapa_chill_stop();
                estado = PELEA;
                world.iniciarPelea(1);
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
            }
            if(vendedor_cerca == true)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
                {
                    musica.welcome();
                    estadoT = COMPRANDO;
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
        ///////////////////
        window.clear(); ///
        ///////////////////
        ///DRAW------------------------------------------------------------------------------------
        ///menu inicio
        if(estado == MENUINICIO)
        {
            window.setView(window.getDefaultView()); // Evita vista fuera de pantall
            sprites.fondos(window,2);
            menu.mostrar_inicio(window);
            window.draw(vol);
        }
        else if(estado == CINEMATICA)
        {
            window.setView(window.getDefaultView());
            window.draw(_acercaDe);
        }
        ///mapa draw
        else if(estado == MAPA)
        {
            gwen.updateView(view, mapSize);///sigue al pj
            window.setView(view); /// actualiza la posicion de la camara

            sprites.fondos(window, 3);
            window.draw(enemi);
            window.draw(e1);
            window.draw(e2);
            window.draw(e3);
            window.draw(e4);
            window.draw(e5);
            window.draw(e6);
            window.draw(e7);
            window.draw(e8);
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
                window.draw(mp);
                inventView.maletinC(window);
                mp.mostrarPausa(window);
                inventView.mostrar_saldo(window, 1);
            }
            else if(mochilaA == true)
            {
                window.draw(fondo_pausa);
                window.draw(mp);
                inventView.maletinO(window);
                mp.mostrarPausa(window);
                inventView.mostrar_saldo(window, 1);
                inventView.MostrarInv(window);
            }
        }
        ///pelea draw
        else if(estado == PELEA)
        {
            window.setView(window.getDefaultView());

            musica.pelea();
            world.draw(window);
        }
        ///tienda draw
        else if(estado == TIENDA)
        {
            window.setView(window.getDefaultView()); // Evita vista fuera de pantalla

            sprites.fondos(window, 0);
            window.draw(gwen);
            window.draw(vendedor);
            window.draw(camp); ///simula puerta
            if(pausa == true && estadoT == QUIETO)
            {
                if(mochilaA == false)
                {
                    window.draw(fondo_pausa);
                    window.draw(mp);
                    inventView.maletinC(window);
                    mp.mostrarPausa(window);
                    inventView.mostrar_saldo(window,1);

                }
                else if(mochilaA == true)
                {
                    window.draw(fondo_pausa);
                    window.draw(mp);
                    inventView.maletinO(window);
                    mp.mostrarPausa(window);
                    inventView.mostrar_saldo(window,1);
                    inventView.MostrarInv(window);
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
                window.draw(tiendM);
                tiendM.mostrar(window);
                inventView.mostrar_saldo(window,2);
            }
            else if(estado == TIENDA && estadoT == COMPRANDO && estadoC == COMPRA)
            {
                window.draw(tiendM);
                tiendM.mostrarCompra(window);
                inventView.mostrar_saldo(window,2);
            }
            else if(estado == TIENDA && estadoT == COMPRANDO && estadoC == VENTA)
            {
                window.draw(tiendM);
                tiendM.mostrarVenta(window);
                inventView.mostrar_saldo(window,2);
            }
        }
        window.display();
    }

    return 0;
}
