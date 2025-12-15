#include <iostream>
#include "menu_pausa.h"
using namespace std;


MenuPausa::MenuPausa(GameData& save,Registros* reg,Inventario& inv,Aliado* equipo)
    :_save(save),_registro(reg),_mochila(inv),_equipo(equipo)
{
    _fondo.setSize(sf::Vector2f(800.0f, 600.0f));
    sf::Color turquesa(128, 128, 128);
    _fondo.setFillColor(turquesa);
    _ePausa = Pausa::OFF;
    if(!_font.loadFromFile("Font/square.ttf"))
    {
        ///error
    }
    std::string opciones [] {"CONTINUAR","INVENTARIO","VOLUMEN","GUARDA","SALIR"};
    for(int i=0; i<5; i++)
    {
        _text[i].setFont(_font);
        _text[i].setString(opciones[i]);
        _text[i].setCharacterSize(20);
        _text[i].setPosition(70,100 + i * 60);
    }
    if(!_textura.loadFromFile("Texture/menu1.png"));
    _sprite.setTexture(_textura);
    _sprite.setPosition(50,50);
    _seleccion = 0;
}
///Move
void MenuPausa::arriva()
{
    if(_seleccion > 0)
    {
        _seleccion--;
    }
}
void MenuPausa::abajo()
{
    if(_seleccion < 4)
    {
        _seleccion++;
    }
}
///
int MenuPausa::getseleccion()
{
    return _seleccion;
}
/// -----------------------------------------------------
void MenuPausa::update(Inventario& inv, EstadoJuego& eJuego, Sound& musica)
{
    if(_ePausa == Pausa::ON)
    {
        if(_reloj.getElapsedTime().asSeconds() > _delay)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                _reloj.restart();
                arriva();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                _reloj.restart();
                abajo();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                cout << _seleccion << endl;
                switch(_seleccion)
                {
                case 0:
                    _ePausa = Pausa::OFF;
                    break;
                case 1:
                    _ePausa = Pausa::INVENTARIO;
                    break;
                case 2:
                    _ePausa = Pausa::VOLUMEN;
                    break;
                case 3:
                    _save.setEquipo(_equipo);
                    _save.setInventario(_mochila);
                    _save.setRegistros(*_registro);

                    if(_save.guardar("save.dat"))
                    {
                        std::cout << "Partida guardada\n";
                    }
                    else
                    {
                        std::cout << "Error al guardar\n";
                    }
                    break;
                case 4:
                    eJuego = EstadoJuego::MENUINICIO;
                    _ePausa = Pausa::OFF;
                    musica.ostPause(1);
                    musica.ostPause(2);
                    break;
                }
            }
        }
    }
    if(_ePausa == Pausa::INVENTARIO)
    {
        if(_reloj.getElapsedTime().asSeconds() > _delay)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                _reloj.restart();
                _ePausa = Pausa::ON;
            }
        }
    }
    if(_ePausa == Pausa::VOLUMEN)
    {
        if(_reloj.getElapsedTime().asSeconds() > _delay)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                _reloj.restart();
                musica.subir();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                _reloj.restart();
                musica.bajar();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                _reloj.restart();
                _ePausa = Pausa::ON;
            }
        }
    }

}
///texto
void MenuPausa::mostrarPausa(sf::RenderWindow& window)
{
    window.draw(_sprite);
    for (int i = 0; i < 5; i++)
    {
        _text[i].setFillColor(i == _seleccion ? sf::Color::Red : sf::Color::White);
        window.draw(_text[i]);
    }
}

void MenuPausa::draw(sf::RenderWindow& win, Inventario& inv, EstadoJuego& eJuego, Sound& musica)
{
    win.setView(win.getDefaultView());
    InventarioView view(inv);
    win.draw(_fondo);

    if(_ePausa == Pausa::ON)
    {
        view.maletinC(win);
        mostrarPausa(win);
        view.mostrar_saldo(win,1);
    }
    if(_ePausa == Pausa::INVENTARIO)
    {
        view.maletinO(win);
        mostrarPausa(win);
        view.mostrar_saldo(win,1);
        view.MostrarInv(win);
    }
    if(_ePausa == Pausa::VOLUMEN)
    {
        view.maletinC(win);
        mostrarPausa(win);
        view.mostrar_saldo(win,1);
        musica.drawVol(win);
    }
}

void MenuPausa::activar()
{
    _ePausa = Pausa::ON;
}

bool MenuPausa::estaActivo()
{
    return _ePausa != Pausa::OFF;
}
