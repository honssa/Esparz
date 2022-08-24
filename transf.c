#include "transf.h"


T_SUPERFICIE_EXT* formatear(SDL_Surface* s){
    T_SUPERFICIE_EXT* ns = malloc(sizeof(T_SUPERFICIE_EXT));
    ns->superficie = s;
    // (x1,y1) e (x2,y2) son os dous vectores que definen a superficie
    ns->x1 = ((float)-s->w)/(float)2;
    ns->y1 = ((float)s->h)/(float)2;
    ns->x2 = ns->x1; ns->y2 = -ns->y1;
    return ns;
}




T_SUPERFICIE_EXT* virar(T_SUPERFICIE_EXT* s, int grados){
    T_SUPERFICIE_EXT* nova_superficie = malloc(sizeof(T_SUPERFICIE_EXT));
    float rad = RADIANS*grados;

    // Transformas os vectores que definen a superficie
    float nx1 = s->x1*cos(rad) - s->y1*sin(rad);
    float ny1 = s->x1*sin(rad) + s->y1*cos(rad);

    float nx2 = s->x2*cos(rad) - s->y2*sin(rad);
    float ny2 = s->x2*sin(rad) + s->y2*cos(rad);

    uint8_t nova_anchura = ceil( 2*MAX(ABS(nx1),ABS(nx2)) ) ;
    uint8_t nova_altura = ceil( 2*MAX(ABS(ny1),ABS(ny2)) );

    // Crear unha nova superficie e mapear nela todos os pixels
    uint8_t novos_pixeles[nova_altura][nova_anchura];
    memset(novos_pixeles, 0, nova_altura*nova_anchura);


    uint8_t* offscreen_l = (uint8_t*)s->superficie->pixels;
    for (int i = 0; i < s->superficie->h; i++) {
        for (int j = 0; j < s->superficie->w; j++){
            if(offscreen_l[j]>0){ // Se e un pixel que conteña informacion
                // Transformar as coordenadas (de forma que o orixe (0,0) sexa o centro)
                SDL_Point punto = {.x = j - s->superficie->w/2, .y = i - s->superficie->h/2};

                // Aplicar a transformacion xeometrica
                int tx = floor(punto.x*cos(rad) - punto.y*sin(rad) );
                int ty = floor(punto.x*sin(rad) + punto.y*cos(rad) );

                // Transformar a coordenadas da nova superficie
                punto.x = nova_anchura/2 + tx;
                punto.y = nova_altura/2 + ty;

                // Asignar
                novos_pixeles[punto.y][punto.x] = offscreen_l[j];
            }
        }
        offscreen_l += s->superficie->pitch; // Pasas á seguinte fila
    }

    // Escribir a nova superficie
    SDL_Surface* ns = SDL_CreateRGBSurface(0, nova_anchura, nova_altura, 8, 0, 0, 0, 0);
    SDL_SetPaletteColors(ns->format->palette, gcolors, 0, 2);

    uint8_t* offscreen = (uint8_t*)ns->pixels;
    for (int i = 0; i < ns->h; i++) {
        for (int j = 0; j < ns->w; j++){
                offscreen[j] = novos_pixeles[i][j];
        }
        offscreen += ns->pitch; // Pasas á seguinte fila
    }

    // Devolver resultado
    nova_superficie->superficie = ns;
    nova_superficie->x1 = nx1; nova_superficie->y1 = ny1;
    nova_superficie->x2 = nx2; nova_superficie->y2 = ny2;

    return nova_superficie;
}
