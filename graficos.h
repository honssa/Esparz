#ifndef GRAFICOS_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#define NEGRO {0,0,0,255}
#define BRANCO {255,255,255,255}
#define PALETA {NEGRO,BRANCO}
#define ABS(N) ((N<0)?(-N):(N))
#define MAX(X,Y) ((X>Y)?(X):(Y))
#define MIN(X,Y) ((X<Y)?(X):(Y))
#define FA 3 // FACTOR AUMENTACION: multiplica x3 os graficos

extern SDL_Color gcolors[2];


void debuxar_rectangulo(SDL_Surface* s, SDL_Point p1, SDL_Point p2, uint8_t cor);
void debuxar_matriz(SDL_Surface* s, SDL_Point p, SDL_Point tam, uint8_t* matriz);
#endif
