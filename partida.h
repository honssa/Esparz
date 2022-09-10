#include "director.h"
#include "graficos.h"

#define DIMX_NAVE 12
#define DIMY_NAVE 12

// Forma da nave
#define NAVE {{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, \
              {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0}, \
              {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0}, \
              {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0}, \
              {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0}, \
              {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0}, \
              {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, \
              {0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0}, \
              {0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0}, \
              {0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0}, \
              {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1}, \
              {0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0}}

typedef struct SNAVE {
    SDL_Surface* spnorm; // sprite normal
    SDL_Surface* sphit; // sprite danado
    int recarga; // recarga de disparo
    SDL_Point p; // Posicion
    SDL_Point dir; // Direcion
} T_NAVE; 

void inicializar_partida();
int eventos_partida();
int actualizar_partida();
int debuxar_partida(SDL_Renderer* rend);
void free_partida();
