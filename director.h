#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
//#include "menu.h"
#include "pila.h"

// Tipos de escenas (flags)
#define ESCENA_MENU 101
#define ESCENA_PARTIDA 102
#define ESCENA_PAUSA 103
#define ESCENA_LOBBY 104
#define ESCENA_OPCIONS 105

// Dimensions da xanela
#define XANELA_ANCHO 630
#define XANELA_ALTO 480

// Frames por segundo
#define FPS 60

// Definicions de funcions macro de utilidade

// Devolve un numero natural
#define NAT(N) ((N<0)?(0):(N))

typedef struct escena {
    uint8_t id;
    //void** atributos;
    void (*inicializar)();
    int (*eventos)();
    int (*actualizar)();
    int (*debuxar)(SDL_Renderer* rend);
    void (*finalizar)();
}T_ESCENA;

T_ESCENA* inicializarEscena(uint8_t escena_id, void (*inicializar)(), int(*eventos)(),
                      int(*actualizar)(), int(*debuxar)(SDL_Renderer* rend), void(*finalizar)());
void freeEscena(void* x);
T_PILA* inicializar();
void bucleEventos();
void finalizarExecucion();
void cambiarEscena(T_ESCENA* novaEscena);

#endif
