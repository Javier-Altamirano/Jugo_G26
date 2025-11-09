#include <iostream>
#include "menu.h"
using namespace std;


Menu::Menu()
{
    if(!_font.loadFromFile("Font/square.ttf"))
    {
        ///error
        std::cout << "error\n";
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
    ///PAUSA-------------------------------------------------------------
    std::string op_pausa[] = {"CONTINUAR","MOCHILA","SALIR"};
    for(int i=0; i<3; i++)
    {
        _text_pausa[i].setFont(_font);
        _text_pausa[i].setString(op_pausa[i]);
        _text_pausa[i].setCharacterSize(25);
    }
    ///TIENDA------------------------------------------------------------
    std::string opciones[] = {"Comprar","Vender","Atras..."};
    for(int i=0; i<3; i++)
    {
        _text[i].setFont(_font);
        _text[i].setString(opciones[i]);
        _text[i].setCharacterSize(30);
        _text[i].setPosition(220, 150 + i * 70);
    }
    std::string opciones_items[] = {"Pocion V", "Pocion E", "Atras..."};
    for(int i=0; i<3; i++)
    {
        _text_items[i].setFont(_font);
        _text_items[i].setString(opciones_items[i]);
        _text_items[i].setCharacterSize(30);
        _text_items[i].setPosition(220, 150 + i * 70);
    }
    _seleccion = 0;
    ///PELEA-------------------------------------------------------------
    ///MATRIZ
    std::string acciones[2][2] =
    {
        {"Atacar","Defender"},
        {"Mochila","Huir"}
    };
    for(int i=0; i<2; i++)
    {
        for(int l=0; l<2; l++)
        {
            _text_pelea[i][l].setFont(_font);
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
    sf::Color verdeSemiOscuro(34, 139, 34, 255);
    sf::Color negroT(0, 0, 0, 128);
    for(int i=0; i<2; i++)
    {
        for(int l=0; l<2; l++)
        {
            _text_pelea[i][l].setFillColor((i == _columna && l == _fila) ? sf::Color::Red : negroT);
            window.draw(_text_pelea[i][l]);
        }
    }
}
///INICIO---------------------------------------------------
void Menu::mostrar_inicio(sf::RenderWindow& window)
{
    for (int i = 0; i < 4; i++)
    {
        _text_inicio[i].setFillColor(i == _seleccion ? sf::Color::Red : sf::Color::White);
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
void Menu::mostrar_pausa(sf::RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        _text_pausa[i].setFillColor(i == _seleccion ? sf::Color::Red : sf::Color::White);
        window.draw(_text_pausa[i]);
    }
}
///TIENDA---------------------------------------------------
int Menu::getSeleccion() const
{
    return _seleccion;
}
void Menu::mostrar(sf::RenderWindow& window)
{
    ///colores
    sf::Color verdeSemiOscuro(34, 139, 34, 255);
    sf::Color grisTransparente(128, 128, 128, 100);
    ///
    for (int i = 0; i < 3; i++)
    {
        _text[i].setFillColor(i == _seleccion ? verdeSemiOscuro : grisTransparente);
        window.draw(_text[i]);
    }
}
void Menu::mostrar_items(sf::RenderWindow& window)
{

    sf::Color verdeSemiOscuro(34, 139, 34, 255);
    sf::Color grisTransparente(128, 128, 128, 100);
    for (int i = 0; i < 3; i++)
    {
        _text_items[i].setFillColor(i == _seleccion ? verdeSemiOscuro : grisTransparente);
        window.draw(_text_items[i]);
    }
}
///MOVIMIENTO GENERAL
void Menu::arribaG(int x)
{
    int a,b;
    a = 0;
    if(x == 1)
    {
        b = 3;
    }
    else if(x == 2)
    {
        b = 2;
    }
    _seleccion --;
    if(_seleccion < a)
    {
        _seleccion = b;
    }
}
void Menu::abajoG(int x)
{
    int a,b;
    a = 0;
    if(x == 1)
    {
        b = 3;
    }
    else if(x == 2)
    {
        b = 2;
    }
    _seleccion ++;
    if(_seleccion > b)
    {
        _seleccion = a;
    }
}
