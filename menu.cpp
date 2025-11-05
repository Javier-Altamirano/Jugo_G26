#include <iostream>
#include "menu.h"
using namespace std;


Menu::Menu()
{
    if(!_font_pelea.loadFromFile("Font/square.ttf"))
    {
        ///error
        std::cout << "error\n";
    }
    if(!_font.loadFromFile("Font/moab.ttf"))
    {
        ///error
    }
    ///INICIO------------------------------------------------------------
    std::string opciones_ini[] = {"NUEVA PARTIDA","CONTINUAR","ACERCA DE","SALIR"};
    for(int i=0; i<4; i++)
    {
        _text_inicio[i].setFont(_font);
        _text_inicio[i].setString(opciones_ini[i]);
        _text_inicio[i].setCharacterSize(28);
        _text_inicio[i].setPosition(280, 180 + i * 70);
    }
    _seleccion_inicio = 0;
    ///PAUSA-------------------------------------------------------------
    std::string op_pausa[] = {"CONTINUAR","MOCHILA","SALIR"};
    for(int i=0; i<3; i++)
    {
        _text_pausa[i].setFont(_font);
        _text_pausa[i].setString(op_pausa[i]);
        _text_pausa[i].setCharacterSize(25);
        _text_pausa[i].setPosition(280, 180 + i * 70);
    }
    ///TIENDA------------------------------------------------------------
    std::string opciones[] = {"Comprar","Vender","Atras"};
    for(int i=0; i<3; i++)
    {
        _text[i].setFont(_font);
        _text[i].setString(opciones[i]);
        _text[i].setCharacterSize(28);
        _text[i].setPosition(280, 180 + i * 70);
    }
    _seleccion = 0;
    ///PELEA-------------------------------------------------------------
    std::string acciones[2][2] =
    {
        {"Atacar","Defender"},
        {"Mochila","Huir"}
    };
    for(int i=0; i<2; i++)
    {
        for(int l=0; l<2; l++)
        {
            _text_pelea[i][l].setFont(_font_pelea);
            _text_pelea[i][l].setString(acciones[i][l]);
            _text_pelea[i][l].setCharacterSize(30);
            _text_pelea[i][l].setPosition(400 + i * 200, 458 + l * 80);
        }
    }
    _fila = 0;
    _columna = 0;
}
///PELEA-------------------------------------------------------------
void Menu::arriba_pelea()
{
    if (_fila > 0) _fila--;
}
void Menu::abajo_pelea()
{
    if (_fila < 1) _fila++;
}
void Menu::izquierda()
{
    if (_columna > 0) _columna--;
}
void Menu::derecha()
{
    if (_columna < 1) _columna++;
}

int Menu::getFila() const
{
    return _fila;
}
int Menu::getColumna() const
{
    return _columna;
}

void Menu::mostrar_pelea(sf::RenderWindow& window)
{
    for(int i=0; i<2; i++)
    {
        for(int l=0; l<2; l++)
        {
            _text_pelea[i][l].setFillColor((i == _columna && l == _fila) ? sf::Color::Yellow : sf::Color::White);
            window.draw(_text_pelea[i][l]);
        }
    }
}
///INICIO---------------------------------------------------
void Menu::arriba_inicio()
{
    _seleccion_inicio --;
    if(_seleccion_inicio < 0)
    {
        _seleccion_inicio = 3;
    }
}
void Menu::abajo_inicio()
{
    _seleccion_inicio ++;
    if(_seleccion_inicio > 3)
    {
        _seleccion_inicio = 0;
    }
}
int Menu::getSeleccion_inicio() const
{
    return _seleccion_inicio;
}
void Menu::mostrar_inicio(sf::RenderWindow& window)
{
    for (int i = 0; i < 4; i++)
    {
        _text_inicio[i].setFillColor(i == _seleccion_inicio ? sf::Color::Red : sf::Color::White);
        window.draw(_text_inicio[i]);
    }
}
///PAUSA---------------------------------------------------
void Menu::posicion(int x, int y)
{
    for(int i=0; i<3; i++)
    {
        _text_pausa[i].setPosition(x, y + i * 70);
    }
}
void Menu::arriba_pausa()
{
    _seleccion_pausa --;
    if(_seleccion_pausa < 0)
    {
        _seleccion_pausa = 2;
    }
}
void Menu::abajo_pausa()
{
    _seleccion_pausa ++;
    if(_seleccion_pausa > 2)
    {
        _seleccion_pausa = 0;
    }
}
int Menu::getSeleccion_pausa() const
{
    return _seleccion_pausa;
}
void Menu::mostrar_pausa(sf::RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        _text_pausa[i].setFillColor(i == _seleccion_pausa ? sf::Color::Red : sf::Color::White);
        window.draw(_text_pausa[i]);
    }
}
///TIENDA---------------------------------------------------
void Menu::arriba()
{
    _seleccion --;
    if(_seleccion < 0)
    {
        _seleccion = 2;
    }
}
void Menu::abajo()
{
    _seleccion ++;
    if(_seleccion > 2)
    {
        _seleccion = 0;
    }
}
int Menu::getSeleccion() const
{
    return _seleccion;
}
void Menu::mostrar(sf::RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        _text[i].setFillColor(i == _seleccion ? sf::Color::Red : sf::Color::Black);
        window.draw(_text[i]);
    }
}
