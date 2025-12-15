#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Sound
{
private:
    sf::Music _musicOst[4];

    sf::SoundBuffer _bufferEfectos[6];
    sf::Sound _efectos[6];

    sf::SoundBuffer _combateBuffer[10];
    sf::Sound _combateSound[10];

    int _volumen;

    sf::Texture _volumenT;
    sf::Sprite _volumenS;
    sf::RectangleShape _barra;
public:
    Sound();

    void subir();
    void bajar();
    int getVolumen();

    void ostPlay(int n);
    void ostPause(int n);

    void efectos(int n);

    void barraUpdate();

    void combatePlay(int n);

    void drawVol(sf::RenderWindow& win);

};
