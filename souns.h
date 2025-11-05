#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Sound
{
private:
    sf::SoundBuffer _buffer_Map;
    sf::Sound _sound_Map;

    sf::SoundBuffer _buffer_Tienda;
    sf::Sound _sound_Tienda;

    sf::SoundBuffer _buffer_Open;
    sf::Sound _sound_Open;

    sf::SoundBuffer _buffer_Pelea;
    sf::Sound _sound_Pelea;

    sf::SoundBuffer _buffer_Menu;
    sf::Sound _sound_Menu;

    int _volumen;
public:
    Sound();
    void mapa_chill();
    void mapa_chill_stop();

    void tienda();
    void tienda_stop();

    void pelea();
    void pelea_stop();

    void menu();
    void menu_stop();

    void open();

    void subir();
    void bajar();
    int getVolumen();

};
