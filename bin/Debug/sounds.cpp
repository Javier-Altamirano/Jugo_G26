#include <iostream>
#include "souns.h"
using namespace std;

Sound::Sound()
{
    _buffer_Map.loadFromFile("Sound/song.wav");
    _sound_Map.setBuffer(_buffer_Map);
    _sound_Map.setLoop(true);

    _buffer_Tienda.loadFromFile("Sound/tienda.wav");
    _sound_Tienda.setBuffer(_buffer_Tienda);
    _sound_Tienda.setLoop(true);

    _buffer_Pelea.loadFromFile("Sound/ff.wav");
    _sound_Pelea.setBuffer(_buffer_Pelea);
    _sound_Pelea.setLoop(true);

    _buffer_Open.loadFromFile("Sound/open.wav");
    _sound_Open.setBuffer(_buffer_Open);
}
///------------------------------------------------------------------------
void Sound::mapa_chill() ///PLAY
{
    if(_sound_Map.getStatus() != sf::Sound::Playing)
    {
        _sound_Map.play();
    }
}
void Sound::mapa_chill_stop() ///STOP
{
    if(_sound_Map.getStatus() == sf::Sound::Playing)
    {
        _sound_Map.stop();
    }
}
///------------------------------------------------------------------------
void Sound::tienda() ///PLAY
{
    if(_sound_Tienda.getStatus() != sf::Sound::Playing)
    {
        _sound_Tienda.play();
    }
}
void Sound::tienda_stop() ///STOP
{
    if(_sound_Tienda.getStatus() == sf::Sound::Playing)
    {
        _sound_Tienda.stop();
    }
}
///------------------------------------------------------------------------
void Sound::pelea() ///PLAY
{
    if(_sound_Pelea.getStatus() != sf::Sound::Playing)
    {
        _sound_Pelea.play();
    }
}
void Sound::pelea_stop() ///STOP
{
    if(_sound_Pelea.getStatus() == sf::Sound::Playing)
    {
        _sound_Pelea.stop();
    }
}
///------------------------------------------------------------------------
void Sound::open()
{
    if(_sound_Open.getStatus() != sf::Sound::Playing)
    {
        _sound_Open.play();
    }
}

