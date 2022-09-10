#include "director.h"

SDL_Renderer* rend;
SDL_Window* win;
float fps_actuais;
T_PILA* pila_escenas;


T_ESCENA* inicializarEscena(uint8_t escena_id, void(*inicializar)(), int(*eventos)(),
                            int(*actualizar)(), int(*debuxar)(SDL_Renderer* rend), void(*finalizar)()){
    T_ESCENA* escena = malloc(sizeof(T_ESCENA));
    escena->id = escena_id;
    escena->inicializar = inicializar;
    escena->eventos = eventos;
    escena->actualizar = actualizar;
    escena->debuxar = debuxar;
    escena->finalizar = finalizar;


    escena->inicializar();
    return escena;
}

void freeEscena(void* x){
    T_ESCENA* escena = (T_ESCENA*) x;
    free(escena);
}

void cambiarEscena(T_ESCENA* novaEscena){
    baleirar(pila_escenas);
    apilar(pila_escenas, novaEscena);
}


T_PILA* inicializar(){
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO);
    win = SDL_CreateWindow("Xogo",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       XANELA_ANCHO, XANELA_ALTO, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    rend = SDL_CreateRenderer(win, -1, render_flags);

    // Inicializar a pila de pila_escenas
    pila_escenas = inicializar_pila();
    fps_actuais = 0;

    return pila_escenas;
}


// Funcion principal do director
void bucleEventos(){
    unsigned int inicioFrame, finalFrame, tempoComputacion, counter = 0;
    float acu_fps = 0;
    while(1){
        inicioFrame = SDL_GetTicks();
        if ( ((T_ESCENA*)(pila_escenas->cabeza->elemento))->eventos() == 1){
            ((T_ESCENA*)(pila_escenas->cabeza->elemento))->finalizar();
            if (desapilar(pila_escenas)) break; // Se a lista queda baleira termina
        }
        ((T_ESCENA*)(pila_escenas->cabeza->elemento))->actualizar();
        ((T_ESCENA*)(pila_escenas->cabeza->elemento))->debuxar(rend);
        tempoComputacion = SDL_GetTicks() - inicioFrame;
        SDL_Delay(NAT(1000-tempoComputacion)/FPS); //1000ms/s dividido entre 60 frames/segundo
        finalFrame = SDL_GetTicks();
        acu_fps += 1000 / (finalFrame-inicioFrame);
        if (++counter==60) {fps_actuais = acu_fps/60; acu_fps = 0; counter = 0;}
    }
}


void finalizarExecucion(){
    // Temporal (So para eliminar a escena de menu)
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}


