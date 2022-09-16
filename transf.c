#include "transf.h"
// pequena probinha

SDL_Point nova_dim(T_VECTOR v1, T_VECTOR v2, T_VECTOR v3, T_VECTOR v4){
    float max_x = MAX( MAX(v1.x, v2.x), MAX(v3.x, v4.x) );
    float min_x = MIN( MIN(v1.x, v2.x), MIN(v3.x, v4.x) );
    float max_y = MAX( MAX(v1.y, v2.y), MAX(v3.y, v4.y) );
    float min_y = MIN( MIN(v1.y, v2.y), MIN(v3.y, v4.y) );
    SDL_Point nova_dim = {.x = ceil(max_x - min_x), .y = ceil(max_y - min_y)};
    return nova_dim;
}

T_SUPERFICIE_EXT* formatear(SDL_Surface* s){
    T_SUPERFICIE_EXT* ns = malloc(sizeof(T_SUPERFICIE_EXT));
    ns->superficie = s;
    T_VECTOR aux1 = {.x = ((float)-s->w)/2., .y = ((float)s->h)/2.}; ns->v1 = aux1;
    T_VECTOR aux2 = {.x = aux1.x, .y = -aux1.y}; ns->v2 = aux2;
    T_VECTOR aux3 = {.x = -aux1.x, .y = -aux1.y}; ns->v3 = aux3;
    T_VECTOR aux4 = {.x = -aux1.x, .y = aux1.y}; ns->v4 = aux4;
    T_VECTOR aux5 = {.x = 0, .y = 0}; ns->offset = aux5;
    // (x1,y1) e (x2,y2) son os dous vectores que definen a superficie
    //ns->x1 = ((float)-s->w)/(float)2;
    //ns->y1 = ((float)s->h)/(float)2;
    //ns->x2 = ns->x1; ns->y2 = -ns->y1;
    return ns;
}




T_SUPERFICIE_EXT* virar(T_SUPERFICIE_EXT* s, int grados, T_VECTOR off){
    T_SUPERFICIE_EXT* nova_superficie = malloc(sizeof(T_SUPERFICIE_EXT));
    float rad = RADIANS*grados;

    // Transformas os vectores que definen a superficie
    float nx1 = (s->v1.x-off.x)*cos(rad) - (s->v1.y-off.y)*sin(rad);
    float ny1 = (s->v1.x-off.x)*sin(rad) + (s->v1.y-off.y)*cos(rad);
    T_VECTOR v1 = {.x = nx1, .y = ny1};

    float nx2 = (s->v2.x-off.x)*cos(rad) - (s->v2.y-off.y)*sin(rad);
    float ny2 = (s->v2.x-off.x)*sin(rad) + (s->v2.y-off.y)*cos(rad);
    T_VECTOR v2 = {.x = nx2, .y = ny2};
    
    float nx3 = (s->v3.x-off.x)*cos(rad) - (s->v3.y-off.y)*sin(rad);
    float ny3 = (s->v3.x-off.x)*sin(rad) + (s->v3.y-off.y)*cos(rad);
    T_VECTOR v3 = {.x = nx3, .y = ny3};
    
    float nx4 = (s->v4.x-off.x)*cos(rad) - (s->v4.y-off.y)*sin(rad);
    float ny4 = (s->v4.x-off.x)*sin(rad) + (s->v4.y-off.y)*cos(rad);
    T_VECTOR v4 = {.x = nx4, .y = ny4};
    
    SDL_Point ndim = nova_dim(v1, v2, v3, v4);

    //uint8_t nova_anchura = ceil( 2*MAX(ABS(nx1),ABS(nx2)) ) ;
    //uint8_t nova_altura = ceil( 2*MAX(ABS(ny1),ABS(ny2)) );
    
    // Crear unha nova superficie e mapear nela todos os pixels
    uint8_t novos_pixeles[ndim.y][ndim.x];
    memset(novos_pixeles, 0, ndim.y*ndim.x);
    
    nova_superficie->offset.x = -(ndim.x - s->superficie->w) / 2.;
    nova_superficie->offset.y = -(ndim.y - s->superficie->h) / 2.;

    // Vector centro dende Ct (C0_Ct)
    SDL_Point centro = {.x = -off.x, .y = -off.y};

    // Aplicar transformacion xeometrica C0tran_Ct
    int cx = round(centro.x*cos(rad) - centro.y*sin(rad));
    int cy = round(centro.x*sin(rad) + centro.y*cos(rad));

    // Averiguar o vector translacion (C0tran_C0)
    SDL_Point translacion = {.x = cx - centro.x, .y = cy - centro.y};

    // Actualizamos o offset
    nova_superficie->offset.x += translacion.x;
    nova_superficie->offset.y += translacion.y;

    uint8_t* offscreen_l = (uint8_t*)s->superficie->pixels;
    for (int i = 0; i < s->superficie->h; i++) {
        for (int j = 0; j < s->superficie->w; j++){
            if(offscreen_l[j]>0){ // Se e un pixel que conteña informacion
                // Transformar as coordenadas (de forma que o orixe (0,0) sexa o centro)
                SDL_Point punto = {.x = j - s->superficie->w/2 - off.x,
                                   .y = i - s->superficie->h/2 - off.y};

                // Aplicar a transformacion xeometrica
                int tx = round(punto.x*cos(rad) - punto.y*sin(rad) );
                int ty = round(punto.x*sin(rad) + punto.y*cos(rad) );
                
                // Atopar o vector dende o centro orixinal transformado (C0tran_Ct)
                tx -= cx; ty -= cy;

                // Transformar a coordenadas da nova superficie
                punto.x = ndim.x/2 + tx;
                punto.y = ndim.y/2 + ty;

                // Asignar
                novos_pixeles[punto.y][punto.x] = offscreen_l[j];
            }
        }
        offscreen_l += s->superficie->pitch; // Pasas á seguinte fila
    }

    // Escribir a nova superficie
    SDL_Surface* ns = SDL_CreateRGBSurface(0, ndim.x, ndim.y, 8, 0, 0, 0, 0);
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
    //nova_superficie->x1 = nx1; nova_superficie->y1 = ny1;
    //nova_superficie->x2 = nx2; nova_superficie->y2 = ny2;

    return nova_superficie;
}
