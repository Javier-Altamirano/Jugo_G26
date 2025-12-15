#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "sound.h"
#include "personaje_jugador.h"
#include "enemigos.h"
#include "menu.h"
#include "menu_pausa.h"
#include "recursos_pelea.h"
#include "items.h"
#include "inventario.h"
#include "archivos.h"
#include "inventarioView.h"
#include "mapManager.h"
#include "tiendaManager.h"
#include "estados.h"
#include "combate_back.h"
#include "fondos.h"
#include "game_data.h"
#include "texto.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Last Guardians"); ///Ventana
    window.setFramerateLimit(60); ///FPS
    sf::Clock reloj; ///Crea un reloj
    float delay = 0.2f; // segundo

    Registros registro;
    Texto _texto;

    Inventario mochila;
    InventarioView inventView(mochila);
    Archivos archivos("Aliados.dat","Enemigos.dat","Items.dat");
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<Item> itemsTienda;

    itemsTienda.push_back(archivos.LeerItem(0));
    itemsTienda.push_back(archivos.LeerItem(1));

    Aliado equipo[3];
    int cantAliados = 3;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Sound musica;
    RecursoPelea sprites;
    Fondos fondos;
    Jugador gwen;
    Menu menu;

    int cant = archivos.CantItemsG();

    Item* guardados = new Item[cant];
    archivos.LeerIT(guardados,cant);

    for(int i=0; i<cant; i++)
    {
        std::cout << guardados[i].getNombre() << std::endl;
        std::cout << guardados[i].getCantidad() << std::endl;;
    }
    delete[] guardados;

    ///----------------- >FUNCIONES DE ESTADO <---------------------------

    EstadoJuego estadoJuego = EstadoJuego::MENUINICIO;
    TiendaEstado estadoTienda = TiendaEstado::FUERA;
    EstadoCombate estadoCombat = EstadoCombate::FUERA;

    GameData save;
    MenuPausa mp(save,&registro,mochila,equipo);
    Combate lucha(estadoJuego,mochila,&registro,estadoCombat,estadoTienda,gwen,musica,save);

    TiendaManager tienda(mochila,estadoJuego,estadoTienda,gwen,musica,equipo,mp);
    tienda.setItems(itemsTienda);
    MapManager mapa(estadoJuego,estadoTienda,gwen,musica,mochila,mp,lucha);


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
            if(estadoJuego == EstadoJuego::MENUINICIO)
            {
                musica.ostPlay(3);
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
                        reloj.restart();
                        switch(menu.getSeleccion())
                        {
                        case 0:
                            std::cout << "Iniciando Nueva Partida...\n";

                            estadoJuego = EstadoJuego::MAPA;
                            estadoTienda = TiendaEstado::FUERA;
                            estadoCombat = EstadoCombate::FUERA;

                            mochila.setSaldo(100);
                            registro.reset();
                            equipo[0] = archivos.LeerAliado(archivos.BIA(1));
                            equipo[1] = archivos.LeerAliado(archivos.BIA(2));
                            equipo[2] = archivos.LeerAliado(archivos.BIA(3));

                            gwen.pos(1500,1000);
                            musica.efectos(2);
                            musica.ostPause(3);
                            break;
                        case 1:
                            if(save.cargar("save.dat"))
                            {
                                std::cout << "Cargando partida...\n";
                                save.getEquipo(equipo);
                                mochila.copiar(save.getInventario());
                                registro = save.getRegistros();

                                musica.efectos(2);
                                musica.ostPause(3);
                                gwen.pos(1500,1000);

                                estadoJuego = EstadoJuego::MAPA;
                            }
                            else
                            {
                                std::cout << "No hay partida guardada\n";
                            }

                            break;
                        case 2:
                            estadoJuego = EstadoJuego::INFO;
                            break;
                        case 3:
                            estadoJuego = EstadoJuego::REGISTROS;
                            break;
                        case 4:
                            estadoJuego = EstadoJuego::SALIR;
                            window.close();
                            break;
                        }
                    }
                }
            }
        }
        ///PELEA----------------------------------------------------
        if (estadoJuego == EstadoJuego::PELEA)
        {

        }
        if(estadoJuego == EstadoJuego::INFO)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
            {
                estadoJuego = EstadoJuego::MENUINICIO;
            }
        }
        if(estadoJuego == EstadoJuego::REGISTROS)
        {
            _texto.updateR(registro);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && reloj.getElapsedTime().asSeconds() > delay)
            {
                estadoJuego = EstadoJuego::MENUINICIO;
            }
        }
        ///MAPA -------------------------------------------------------
        if(estadoJuego == EstadoJuego::MAPA)
        {
            mapa.update();
        }
        ///TIENDA------------------------------------------------------
        if(estadoJuego == EstadoJuego::TIENDA)
        {
            tienda.update();
        }
        ///////////////////
        window.clear(); ///
        ///////////////////
        ///DRAW---------------------------------------------------------
        ///menu inicio
        if(estadoJuego == EstadoJuego::MENUINICIO)
        {
            window.setView(window.getDefaultView()); // Evita vista fuera de pantall
            fondos.fondos(window,2);
            menu.mostrar_inicio(window);
        }
        if(estadoJuego == EstadoJuego::INFO)
        {
            fondos.fondos(window,5);
            window.setView(window.getDefaultView());
            _texto.acercade(window);
        }
        if(estadoJuego == EstadoJuego::REGISTROS)
        {
            fondos.fondos(window,6);
            window.setView(window.getDefaultView());
            _texto.registros(window);
        }
        ///mapa draw
        if(estadoJuego == EstadoJuego::MAPA)
        {
            fondos.fondos(window, 3);
            mapa.draw(window);
        }
        ///pelea draw
        if(estadoJuego == EstadoJuego::PELEA)
        {
            window.setView(window.getDefaultView());
            fondos.fondos(window,1);
            lucha.update(window, mochila,equipo,cantAliados);
        }
        ///tienda draw
        if(estadoJuego == EstadoJuego::TIENDA)
        {
            fondos.fondos(window, 0);
            tienda.draw(window);
        }

        window.display();
    }

    return 0;
}
