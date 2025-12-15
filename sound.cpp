#include <iostream>
#include "sound.h"
using namespace std;

Sound::Sound()
{
    _volumen = 50.0f;

    std::string soundtrack [] {"Sound/ff.ogg","Sound/tienda.ogg","Sound/fondo1.ogg","Sound/cumbia.ogg"};
    for(int i=0; i<4; i++)
    {
        if(!_musicOst[i].openFromFile(soundtrack[i]))
        {
            cout << soundtrack[i] << endl;
        }
        _musicOst[i].setVolume(_volumen);
        _musicOst[i].setLoop(true);
    }

    std::string efectos [] {
        "Sound/open.wav",
        "Sound/nop.wav",
        "Sound/ok1.wav",
        "Sound/ok2.wav",
        "Sound/welcome.wav",
        "Sound/ty.wav"};
    for(int i=0; i<6; i++)
    {
        if(!_bufferEfectos[i].loadFromFile(efectos[i]))
        {
            cout << efectos[i] << endl;
        }
        _efectos[i].setBuffer(_bufferEfectos[i]);
        _efectos[i].setVolume(_volumen);
    }

    std::string combate [] {
        "Sound/claudioAtk.wav",
        "Sound/claudioAtk2.wav",
        "Sound/claudiodead.wav",
        "Sound/miami.wav",
        "Sound/cortastelaloz.wav",
        "Sound/sacalamano.wav",
        "Sound/faaa.wav",
        "Sound/mega.wav"
        };
    for(int i=0;i<8;i++)
    {
        if(!_combateBuffer[i].loadFromFile(combate[i]))
        {
            //error
        }
        _combateSound[i].setBuffer(_combateBuffer[i]);
        _combateSound[i].setVolume(_volumen);
    }

    if(!_volumenT.loadFromFile("Texture/volumen.png"))
    {
        ///error
    }
    _volumenS.setTexture(_volumenT);
    _volumenS.setPosition(65,390);

    _barra.setSize(sf::Vector2f((_volumen * 200) / 100,10));
    _barra.setFillColor(sf::Color::Green);
    _barra.setPosition(90,397);
}
///---------CONTROL DE VOLUMEN-------------------------
void Sound::subir()
{
    if(_volumen < 100)
    {
        _volumen++;
        barraUpdate();
    }

    for(int i=0;i<4;i++)
    {
        _musicOst[i].setVolume(_volumen);
    }
    for(int i=0;i<6;i++)
    {
        _efectos[i].setVolume(_volumen);
    }
    for(int i=0;i<8;i++)
    {
        _combateSound[i].setVolume(_volumen);
    }
}
void Sound::bajar()
{
    if(_volumen > 0)
    {
        _volumen--;
        barraUpdate();
    }

    for(int i=0;i<4;i++)
    {
        _musicOst[i].setVolume(_volumen);
    }
    for(int i=0;i<6;i++)
    {
        _efectos[i].setVolume(_volumen);
    }
    for(int i=0;i<8;i++)
    {
        _combateSound[i].setVolume(_volumen);
    }
}

int Sound::getVolumen()
{
    return _volumen;
}

void Sound::combatePlay(int n)
{
    if(n >= 0 && n < 8)
    {
        if(_combateSound[n].getStatus() != sf::Sound::Playing)
        {
            _combateSound[n].play();
        }
    }
}

void Sound::efectos(int n)
{
    if(n >= 0 && n < 10)
    {
        if(_efectos[n].getStatus() != sf::Sound::Playing)
        {
            _efectos[n].play();
        }
    }
}

void Sound::ostPlay(int n) ///PLAY
{
    if(n >= 0 && n < 4)
    {
        if(_musicOst[n].getStatus() != sf::Sound::Playing)
        {
            _musicOst[n].play();
        }
    }
}
void Sound::ostPause(int n) ///STOP
{
    if(n >= 0 && n < 4)
    {
        if(_musicOst[n].getStatus() == sf::Sound::Playing)
        {
            _musicOst[n].stop();
        }
    }
}

void Sound::barraUpdate()
{
    _barra.setSize(sf::Vector2f((_volumen * 200) / 100, 10));
}

void Sound::drawVol(sf::RenderWindow& win)
{
    win.draw(_barra);
    win.draw(_volumenS);
}
