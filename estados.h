#pragma once

enum class EstadoJuego {
    MENUINICIO,
    INFO,
    MAPA,
    PELEA,
    TIENDA,
    REGISTROS,
    SALIR,
};

enum class TiendaEstado {
    FUERA,
    DENTRO,
    INTERACTUANDO
};

enum class Comprando {
    NADA,
    MENU,
    COMPRA,
    VENTA
};

enum class Pausa {
    OFF,
    ON,
    INVENTARIO,
    VOLUMEN
};

enum class EstadoCombate {
    FUERA,
    LUCHANDO,
    GANASTE,
    PERDISTE,
    HUIR
};
enum class TurnoCombate
{
    JUGADOR,
    ESPERANDO_ENEMIGO,
    ENEMIGO,
    ESPERANDO_JUGADOR
};
