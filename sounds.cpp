#include <iostream>
#include "souns.h"
using namespace std;

Sound::Sound()
{
    if(!_buffer_Menu.loadFromFile("Sound/cumbia.wav"))
    {
        std::cout << "error cumbia...\n";
    }
    _sound_Menu.setBuffer(_buffer_Menu);
    _sound_Menu.setLoop(true);

    if(!_buffer_Map.loadFromFile("Sound/fondo1.wav"))
    {
        std::cout << "error fondo1...\n";
    }
    _sound_Map.setBuffer(_buffer_Map);
    _sound_Map.setLoop(true);

    if(!_buffer_Tienda.loadFromFile("Sound/tienda.wav"))
    {
        std::cout << "error tienda ost...\n";
    }
    _sound_Tienda.setBuffer(_buffer_Tienda);
    _sound_Tienda.setLoop(true);

    if(!_buffer_Pelea.loadFromFile("Sound/ff.wav"))
    {
        std::cout << "error ff...\n";
    }
    _sound_Pelea.setBuffer(_buffer_Pelea);
    _sound_Pelea.setLoop(true);

    if(!_buffer_Open.loadFromFile("Sound/open.wav"))
    {
        std::cout << "error open...\n";
    }
    _sound_Open.setBuffer(_buffer_Open);

    if(!_buffer_ty.loadFromFile("Sound/ty.wav"))
    {
        std::cout << "error ty...\n";
    }
    _sound_ty.setBuffer(_buffer_ty);

    if(!_buffer_wel.loadFromFile("Sound/welcome.wav"))
    {
        std::cout << "error welcome...\n";
    }
    _sound_wel.setBuffer(_buffer_wel);

    if(!_buffer_ok.loadFromFile("Sound/ok1.wav"))
    {
        std::cout << "error ok1...\n";
    }
    _sound_ok.setBuffer(_buffer_ok);
    if(!_buffer_ok2.loadFromFile("Sound/ok2.wav"))
    {
        std::cout << "error ok2...\n";
    }
    _sound_ok2.setBuffer(_buffer_ok2);
    if(!_buffer_nop.loadFromFile("Sound/nop.wav"))
    {
        ///error
    }
    _sound_nop.setBuffer(_buffer_nop);

    _volumen = 50.0f;
    _sound_nop.setVolume(_volumen);
    _sound_ok2.setVolume(_volumen);
    _sound_ok.setVolume(_volumen);
    _sound_wel.setVolume(_volumen);
    _sound_ty.setVolume(_volumen);
    _sound_Menu.setVolume(_volumen);
    _sound_Map.setVolume(_volumen);
    _sound_Open.setVolume(_volumen);
    _sound_Pelea.setVolume(_volumen);
    _sound_Tienda.setVolume(_volumen);
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
void Sound::menu() ///PLAY
{
    if(_sound_Menu.getStatus() != sf::Sound::Playing)
    {
        _sound_Menu.play();
    }
}
void Sound::menu_stop() ///STOP
{
    if(_sound_Menu.getStatus() == sf::Sound::Playing)
    {
        _sound_Menu.stop();
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
void Sound::thanks()
{
    if(_sound_ty.getStatus() != sf::Sound::Playing)
    {
        _sound_ty.play();
    }
}
void Sound::welcome()
{
    if(_sound_wel.getStatus() != sf::Sound::Playing)
    {
        _sound_wel.play();
    }
}
void Sound::ok()
{
    if(_sound_ok.getStatus() != sf::Sound::Playing)
    {
        _sound_ok.play();
    }
}
void Sound::ok2()
{
    if(_sound_ok2.getStatus() != sf::Sound::Playing)
    {
        _sound_ok2.play();
    }
}
void Sound::nop()
{
    if(_sound_nop.getStatus() != sf::Sound::Playing)
    {
        _sound_nop.play();
    }
}
///---------CONTROL DE VOLUMEN-------------------------
void Sound::subir()
{
    if(_volumen < 100)
    {
        _volumen++;
    }
    _sound_nop.setVolume(_volumen);
    _sound_ok2.setVolume(_volumen);
    _sound_ok.setVolume(_volumen);
    _sound_wel.setVolume(_volumen);
    _sound_ty.setVolume(_volumen);
    _sound_Menu.setVolume(_volumen);
    _sound_Map.setVolume(_volumen);
    _sound_Open.setVolume(_volumen);
    _sound_Pelea.setVolume(_volumen);
    _sound_Tienda.setVolume(_volumen);
}
void Sound::bajar()
{
    if(_volumen > 0)
    {
        _volumen--;
    }
    _sound_nop.setVolume(_volumen);
    _sound_ok2.setVolume(_volumen);
    _sound_ok.setVolume(_volumen);
    _sound_wel.setVolume(_volumen);
    _sound_ty.setVolume(_volumen);
    _sound_Menu.setVolume(_volumen);
    _sound_Map.setVolume(_volumen);
    _sound_Open.setVolume(_volumen);
    _sound_Pelea.setVolume(_volumen);
    _sound_Tienda.setVolume(_volumen);
}
int Sound::getVolumen()
{
    return _volumen;
}

