#include "letras.h"
#include "boton.h"
#include "director.h"


void inicializar_menu();
int eventos_menu();
int actualizar_menu();
int debuxar_menu(SDL_Renderer* rend);
void free_menu();
SDL_Surface* inicializar_titulo();
SDL_Surface* inicializar_autor();
void debuxar_titulo(SDL_Renderer* rend);
void debuxar_autor(SDL_Renderer* rend);
// o comezo de fila entendese como negro, cada fila conten 147px
#define TITULO { 26, 2, 83, 4, 32,                                                       \
                 25, 3, 81, 6, 32,                                                       \
                 23, 5, 26, 12, 42, 5, 1, 2, 31,                                         \
                 20, 8, 23, 3, 12, 1, 40, 4, 5, 1, 30,                                   \
                 19, 9, 17, 1, 4, 1, 15, 1, 39, 4, 7, 2, 28,                             \
                 18, 10, 16, 2, 3, 2, 15, 1, 38, 4, 10, 1, 27,                           \
                 16, 13, 15, 2, 3, 3, 15, 1, 3, 1, 33, 4, 11, 2, 25,                     \
                 13, 16, 14, 3, 3, 3, 6, 3, 6, 1, 3, 2, 32, 10, 7, 3, 22,                \
                 12, 17, 13, 4, 3, 4, 4, 1, 2, 2, 5, 1, 3, 4, 36, 6, 8, 1, 21,           \
                 9, 19, 13, 5, 4, 3, 4, 1, 2, 3, 4, 1, 4, 12, 3, 12, 15, 6, 6, 2, 19,    \
                 6, 20, 14, 6, 4, 3, 4, 1, 3, 2, 4, 1, 5, 9, 4, 16, 14, 5, 7, 3, 16,     \
                 4, 16, 19, 7, 4, 4, 4, 4, 5, 1, 6, 7, 5, 7, 3, 7, 16, 4, 8, 3, 13,      \
                 0, 17, 22, 7, 5, 3, 12, 1, 6, 8, 5, 5, 7, 5, 19, 4, 8, 3, 10,           \
                 0, 14, 22, 10, 5, 4, 11, 1, 6, 9, 4, 5, 8, 5, 20, 5, 8, 2, 8,           \
                 1, 8, 25, 12, 6, 3, 11, 1, 5, 10, 4, 5, 8, 5, 23, 5, 7, 4, 4,           \
                 1, 5, 25, 11, 2, 2, 6, 4, 9, 2, 5, 4, 3, 3, 4, 5, 8, 5, 25, 5, 9, 2, 2, \
                 2, 5, 22, 11, 5, 2, 5, 4, 5, 4, 7, 3, 4, 4, 3, 5, 8, 5, 25, 4, 12, 2,   \
                 3, 5, 17, 12, 16, 3, 5, 1, 10, 2, 5, 4, 3, 5, 7, 6, 10, 2, 12, 4, 8, 5, 2, \
                 3, 5, 11, 1, 6, 9, 18, 4, 4, 1, 9, 3, 5, 4, 3, 7, 3, 7, 10, 3, 11, 3, 7, 3, 7, \
                 4, 5, 4, 7, 6, 7, 15, 1, 5, 3, 3, 1, 10, 2, 6, 4, 4, 15, 11, 4, 8, 3, 7, 2, 10,\
                 4, 5, 1, 10, 8, 5, 15, 2, 4, 3, 3, 1, 10, 2, 6, 4, 4, 14, 11, 3, 1, 2, 5, 3, 7, 2, 12,\
                 5, 15, 9, 5, 14, 3, 4, 2, 3, 1, 9, 4, 4, 6, 3, 15, 9, 3, 4, 7, 5, 3, 14, \
                 5, 16, 9, 4, 13, 5, 3, 2, 3, 1, 9, 14, 3, 6, 4, 5, 8, 3, 8, 2, 5, 2, 17, \
                 5, 16, 10, 1, 14, 7, 2, 2, 3, 1, 9, 14, 4, 5, 5, 5, 6, 9, 8, 2, 19, \
                 5, 7, 21, 1, 10, 9, 3, 2, 3, 1, 8, 14, 4, 5, 5, 6, 13, 3, 8, 2, 17, \
                 5, 5, 22, 3, 6, 13, 2, 2, 3, 1, 7, 3, 4, 8, 4, 6, 5, 5, 12, 3, 11, 7, 10, \
                 5, 5, 20, 4, 3, 11, 2, 4, 2, 2, 3, 1, 7, 3, 5, 8, 3, 6, 5, 5, 11, 3, 4, 3, 7, 2, 13,\
                 6, 4, 15, 9, 1, 12, 2, 6, 1, 2, 3, 1, 6, 4, 5, 8, 3, 6, 6, 5, 9, 3, 4, 1, 2, 2, 4, 2, 15, \
                 6, 4, 13, 10, 2, 9, 5, 6, 2, 1, 3, 1, 6, 4, 6, 8, 2, 6, 6, 5, 8, 3, 4, 1, 5, 4, 17, \
                 6, 5, 11, 11, 3, 5, 7, 6, 3, 2, 3, 1, 5, 4, 5, 9, 2, 6, 7, 4, 7, 3, 4, 1, 6, 2, 19, \
                 6, 7, 6, 14, 15, 4, 5, 2, 3, 1, 4, 5, 6, 9, 2, 5, 7, 6, 4, 3, 4, 1, 6, 2, 20, \
                 7, 26, 14, 4, 6, 2, 3, 1, 4, 5, 5, 11, 2, 4, 8, 6, 1, 4, 4, 1, 29, \
                 7, 26, 14, 4, 7, 1, 3, 1, 4, 5, 6, 11, 2, 4, 8, 5, 1, 3, 4, 1, 30, \
                 7, 13, 7, 6, 11, 6, 8, 1, 3, 1, 3, 5, 8, 11, 1, 4, 6, 1, 2, 4, 1, 2, 4, 1, 31, \
                 6, 8, 17, 2, 5, 12, 9, 4, 38, 2, 11, 6, 27, \
                 6, 4, 27, 13, 51, 3, 16, 8, 19, \
                 36, 13, 53, 3, 23, 8, 11, \
                 35, 3, 65, 17, 15, 1, 11, \
                 35, 2, 83, 8, 6, 1, 12, \
                 128, 7, 12 }

#define AUTOR { 1,1,19,1,19,1,1,1,12,1,1, \
               1,1,11,1,7,2,18,1,1,1,5,1,4,1,2,1, \
               1,2,5,2,2,1,8,1,3,1,2,2,2,1,1,1,2,2,2,1,1,1,4,1,8,1, \
               1,1,1,1,1,2,1,1,1,1,2,1,1,2,4,1,2,1,2,3,2,1,1,1,1,3,2,1,1,1,1,2,2,1,4,1,2,1, \
               1,1,1,1,1,2,1,1,1,1,1,1,2,3,3,2,1,1,3,3,2,1,3,3,1,1,1,1,1,2,1,1,7,1,1 }


//11+16+26+38+35
#define TAM_AUTOR 126
#define AUTOR_X 58
#define AUTOR_Y 5

// 5 + 5 + 9 + 11 + 13 + 13 + 15 + 17 + 19 + 21 + 21 + 21 + 19 + 19 (208)
// + 19 + 23 + 22 + 23 + 25 + 25 (137) --> 345
// + 27 + 23 + 23 + 21 + 21  (115) --> 460
// + 23 + 27 + 29 + 27 + 27 (133) --> 593
// + 25 + 21 + 21 + 25 + 13 (105) --> 698
// + 9 + 7 + 7 + 7 + 3 (33) --> 731
#define DIMX_TITULO 147
#define DIMY_TITULO 40
#define DIM_TITULO 731// (345 con 14 liñas)
