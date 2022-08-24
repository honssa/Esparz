#ifndef BOTON_H
#define BOTON_H
#include "letras.h"


#define FLECHA {{0, 0, 0, 0, 1, 0, 0}, \
                {0, 0, 0, 0, 1, 1, 0}, \
                {1, 1, 1, 1, 1, 1, 1}, \
                {1, 1, 1, 1, 1, 1, 1}, \
                {0, 0, 0, 0, 1, 1, 0}, \
                {0, 0, 0, 0, 1, 0, 0}}

#define FLECHA_DIM_X 7
#define FLECHA_DIM_Y 6
#define DIMENSION_X 52
#define DIMENSION_Y 24
#define PDIM_X 52
#define PDIM_Y 21
#define NUM_BOTONS 4

typedef struct BOTON{
    SDL_Surface* base;
    SDL_Surface* sens;
    SDL_Surface* prem;
    SDL_Rect dst; // destino (posicion + tam)

    //SDL_Point tam;
    void (*funcion_chamada)(); // funcion que sera chamada ao premer este boton
} T_BOTON;

typedef struct BOTONS{
    int boton_sensado;
    T_BOTON* arr_botons[NUM_BOTONS];
    bool click;
} T_BOTONS;

T_BOTON* inicializar_boton(const char* texto, SDL_Point pos, void(*funcion_chamada)());
T_BOTONS* inicializar_botons();
void actualizar_botons(T_BOTONS* botons, int cursor_x, int cursor_y);
void debuxar_botons(SDL_Renderer* rend, T_BOTONS* botons);
void free_botons();
#endif
