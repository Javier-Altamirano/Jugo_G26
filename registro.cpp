#include <iostream>
#include "registro.h"
using namespace std;


Registros::Registros()
{
    _combatesTotales = 0;
    _victorias = 0;
    _derrotas = 0;
    _inconcluso = 0;
    _danioTotalCausado = 0;
    _coleccionistasD = 0;
    _cazadoresD = 0;
    _jefesD = 0;
    _cantidadCuraciones = 0;
}
Registros::Registros(int combatesT,int victoria, int derrota,int danioTotalCausado, int coleccionistas, int cazadores, int jefes, int curaciones, int inconcluso)
{
    _combatesTotales = combatesT;
    _victorias = victoria;
    _derrotas = derrota;
    _inconcluso = inconcluso;
    _danioTotalCausado = danioTotalCausado;
    _coleccionistasD = coleccionistas;
    _cazadoresD = cazadores;
    _jefesD = jefes;
    _cantidadCuraciones = curaciones;
}
void Registros::reset()
{
    _combatesTotales = 0;
    _victorias = 0;
    _derrotas = 0;
    _inconcluso = 0;
    _danioTotalCausado = 0;
    _coleccionistasD = 0;
    _cazadoresD = 0;
    _jefesD = 0;
    _cantidadCuraciones = 0;
}
// Métodos para actualizar
void Registros::sumarCombates()
{
    _combatesTotales++;
}
void Registros::sumarVictoria()
{
    _victorias++;
}
void Registros::sumarDerrota()
{
    _derrotas++;
}
void Registros::sumarNulas()
{
    _inconcluso++;
}
void Registros::agregarDanio(int danio)
{
    _danioTotalCausado += danio;
}

void Registros::derrotarColeccionistas()
{
    _coleccionistasD++;
}
void Registros::derrotarCazadores()
{
    _cazadoresD++;
}
void Registros::derrotarJefe()
{
    _jefesD++;
}

void Registros::registrarCuracion(int cura)
{
    _cantidadCuraciones+= cura;
}

// Getters
int Registros::getCombates() const
{
    return _combatesTotales;
}
int Registros::getVictorias() const
{
    return _victorias;
}
int Registros::getDerrotas() const
{
    return _derrotas;
}
int Registros::getInconcluso() const
{
    return _inconcluso;
}
int Registros::getDanioTotal() const
{
    return _danioTotalCausado;
}

int Registros::getColeccionistas() const
{
    return _coleccionistasD;
}
int Registros::getCazadores() const
{
    return _cazadoresD;
}
int Registros::getJefes() const
{
    return _jefesD;
}

int Registros::getCuraciones() const
{
    return _cantidadCuraciones;
}

// Método para mostrar (opcional)
void Registros::mostrar()
{
    std::cout << "---- REGISTROS ----" << std::endl;
    std::cout << "Combates: " << _combatesTotales << std::endl;
    std::cout << "Victorias: " << _victorias << std::endl;
    std::cout << "Derrotas: " << _derrotas << std::endl;
    std::cout << "Daño total causado: " << _danioTotalCausado << std::endl;
    std::cout << "Enemigos débiles derrotados: " << _coleccionistasD << std::endl;
    std::cout << "Enemigos medios derrotados: " << _cazadoresD << std::endl;
    std::cout << "Enemigos jefes derrotados: " << _jefesD << std::endl;
    std::cout << "Curaciones realizadas: " << _cantidadCuraciones << std::endl;
    std::cout << "-------------------" << std::endl;
}

void Registros::guardar(FILE* p) const
{
    fwrite(&_combatesTotales, sizeof(int), 1, p);
    fwrite(&_victorias, sizeof(int), 1, p);
    fwrite(&_derrotas, sizeof(int), 1, p);
    fwrite(&_inconcluso, sizeof(int), 1, p);
    fwrite(&_danioTotalCausado, sizeof(int), 1, p);
    fwrite(&_coleccionistasD, sizeof(int), 1, p);
    fwrite(&_cazadoresD, sizeof(int), 1, p);
    fwrite(&_jefesD, sizeof(int), 1, p);
    fwrite(&_cantidadCuraciones, sizeof(int), 1, p);
}

void Registros::cargar(FILE* p)
{
    fread(&_combatesTotales, sizeof(int), 1, p);
    fread(&_victorias, sizeof(int), 1, p);
    fread(&_derrotas, sizeof(int), 1, p);
    fread(&_inconcluso, sizeof(int), 1, p);
    fread(&_danioTotalCausado, sizeof(int), 1, p);
    fread(&_coleccionistasD, sizeof(int), 1, p);
    fread(&_cazadoresD, sizeof(int), 1, p);
    fread(&_jefesD, sizeof(int), 1, p);
    fread(&_cantidadCuraciones, sizeof(int), 1, p);
}

