#include <iostream>
#include "texto.h"
using namespace std;


Texto::Texto()
{
    if(!_font.loadFromFile("Font/square.ttf"))
    {
        ///error
    }
    _text.setFont(_font);
    _text2.setFont(_font);

    _mens1 = ">> TP Integrador de Programacion 2\n----------------------------------\n\n\n > Profesor: Brian Lara\n\n > Integrantes Grupo 26:\n\n   > Javier Francisco Altamirano\n\n   > Lucia Aylen Maffey";

}

void Texto::updateR(Registros& reg)
{
    float pVictorias, pDerrotas, pNada;
    int totalCombates = reg.getCombates();


    if (totalCombates > 0) {

        pVictorias = (static_cast<float>(reg.getVictorias()) / totalCombates) * 100.0f;
        pDerrotas = (static_cast<float>(reg.getDerrotas()) / totalCombates) * 100.0f;
        pNada = (static_cast<float>(reg.getInconcluso()) / totalCombates) * 100.0f;
    } else {
        pVictorias = pDerrotas = pNada = 0.0f;
    }

    _mens2 = ("\n ---------------------------------------------\n >>> Registo:\n"
              " ---------------------------------------------\n"
              "      >> Enfrentamientos: " + std::to_string(totalCombates) + ". \n"
              "          Victorias %" + std::to_string(pVictorias) +
              "\n          Derrotas %" + std::to_string(pDerrotas) +
              "\n          Nulas %" + std::to_string(pNada) +
              "\n\n      >> Enemigos Derrotados: \n" +
              "          Coleccionistas >>" + std::to_string(reg.getColeccionistas()) +
              "\n          Cazadores >>" + std::to_string(reg.getCazadores())+
              "\n          Jefes >>" + std::to_string(reg.getJefes())+ "\n\n" +
              "     > Danio Realizado >> " + std::to_string(reg.getDanioTotal()) +
              "\n     > Curaciones Realizadas >> " + std::to_string(reg.getCuraciones()));
}

void Texto::acercade(sf::RenderWindow& win)
{
    _text2.setCharacterSize(20);
    _text2.setColor(sf::Color::White);
    _text2.setPosition(300,100);
    _text2.setString(_mens1);
    win.draw(_text2);
}
void Texto::registros(sf::RenderWindow& win)
{
    _text.setCharacterSize(30);
    _text.setColor(sf::Color::Black);
    _text.setString(_mens2);
    win.draw(_text);
}
