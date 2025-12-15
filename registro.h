#pragma once

class Registros
{
private:
    int _combatesTotales;
    int _victorias;
    int _derrotas;
    int _inconcluso;
    int _danioTotalCausado;
    int _cantidadCuraciones;
    int _coleccionistasD;
    int _cazadoresD;
    int _jefesD;

public:
    Registros();

    Registros(int combatesT, int victoria, int derrota,int danioTotalCausado, int coleccionistas, int cazadores, int jefes, int curaciones, int inconcluso);

    // Métodos para actualizar
    void sumarCombates();

    void sumarVictoria();

    void sumarDerrota();

    void sumarNulas();

    void agregarDanio(int danio);

    void derrotarColeccionistas();

    void derrotarCazadores();

    void derrotarJefe();

    void registrarCuracion(int cura);

    // Getters
    int getCombates() const;

    int getVictorias() const;

    int getDerrotas() const;

    int getInconcluso() const;

    int getDanioTotal() const;


    int getColeccionistas() const;

    int getCazadores() const;

    int getJefes() const;


    int getCuraciones() const;

    void mostrar();

    void reset();

    void guardar(std::ofstream& out) const;
    void cargar(std::ifstream& in);

};
