#include "director.h"
#include "transf.h"

#define DIMX_NAVE 11
#define DIMY_NAVE 11
#define NUM_TECLAS 322
// Forma da nave
#define NAVE {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
              {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, \
              {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1}, \
              {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1}, \
              {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1}, \
              {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1}, \
              {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1}, \
              {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1}, \
              {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1}, \
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, \
              {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}

typedef struct SNAVE {
    T_SUPERFICIE_EXT* tse; // superficie de transformacion
    SDL_Surface* spnorm; // sprite normal
    SDL_Surface* sphit; // sprite danado
    int recarga; // recarga de disparo
    SDL_Point p; // Posicion
    T_VECTOR dir; // Direcion
    int grados; // Rotacion;
    float impulso; // Impulso de movemento
} T_NAVE; 

void inicializar_partida();
int eventos_partida();
int actualizar_partida();
int debuxar_partida(SDL_Renderer* rend);
void free_partida();
