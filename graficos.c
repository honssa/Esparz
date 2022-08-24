#include "graficos.h"
SDL_Color gcolors[2] = PALETA;



// recebe unha matriz e imprimea nunha superficie
void debuxar_matriz(SDL_Surface* s, SDL_Point p, SDL_Point tam, uint8_t* matriz){
    uint8_t* offscreen_l = (uint8_t*)s->pixels;
    offscreen_l += (s->pitch*p.y);
    for (int i = 0; i < MIN(tam.y,s->h-p.y); i++) {
        for (int j = p.x; j < MIN(p.x+tam.x,s->w-p.x); j++){
            offscreen_l[j] = *(matriz+(i*tam.x+(j-p.x)));//matriz[i][j-p.x];
        }
        offscreen_l += s->pitch;
    }//*(trama_letra+(i*LETRA_ANCHO+j))
}

// Serve para debuxar rectas horizontais e verticais e rectangulos de calquer dimension
void debuxar_rectangulo(SDL_Surface* s, SDL_Point p1, SDL_Point p2, uint8_t cor){
    // p1 seria a esquina superior esquerda do rectangulo
    // p2 a esquina inferior dereita
    uint8_t* offscreen = (uint8_t*)s->pixels;
    offscreen += (s->pitch*p1.y); // Situamolo na primeira fila a debuxar
    for (int i = p1.y; i<=MIN(s->h, p2.y); i++){
        for (int j = p1.x; j<=MIN(s->w, p2.x); j++){
            offscreen[j] = cor;
        }
        offscreen += s->pitch;
    }
    return;

}
