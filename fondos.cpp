#include <iostream>
#include "fondos.h"
using namespace std;


Fondos::Fondos()
{
    std::string direccion[] =
    {
        "Texture/piso.png",
        "Texture/pelea.png",
        "Texture/portada.png",
        "Texture/mapa.png",
        "Texture/derrota.png",
        "Texture/milei.png",
        "Texture/registro.png"
    };

    for (int i = 0; i < 7; i++)
    {
        if (!_texture[i].loadFromFile(direccion[i]))
            cout << "Error cargando " << direccion[i] << endl;

        _sprite[i].setTexture(_texture[i]);
    }
}

void Fondos::fondos(sf::RenderWindow& window, int x)
{
    window.draw(_sprite[x]);
}
