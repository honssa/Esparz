#include "partida.h"

T_NAVE* nave;
T_SUPERFICIE_EXT* tse;
T_SUPERFICIE_EXT* tse2;
uint8_t TECLAS[NUM_TECLAS];

int i = 0, contador = 0;

T_NAVE* inicializar_nave(uint8_t x, uint8_t y){
    T_NAVE* n = malloc(sizeof(T_NAVE));
    SDL_Point pos = {.x = x, .y = y};
    SDL_Point dir = {.x = 0, .y = 0};
    n->p = pos;
    n->dir = dir;
    n->spnorm = SDL_CreateRGBSurface(SDL_SWSURFACE, DIMX_NAVE, DIMY_NAVE, 8, 0, 0, 0, 0);
    SDL_SetPaletteColors(n->spnorm->format->palette, gcolors, 0, 2);
    uint8_t* matriz = malloc(sizeof(uint8_t)*DIMX_NAVE*DIMY_NAVE);
    uint8_t mnave[DIMX_NAVE][DIMY_NAVE] = NAVE;
    SDL_Point ptmp = {.x = 0, .y = 0}; SDL_Point tamtmp = {.x = DIMX_NAVE, .y = DIMY_NAVE};
    debuxar_matriz(n->spnorm, ptmp, tamtmp, &mnave[0][0]);
    n->tse = formatear(n->spnorm);
    n->grados = 0;
    return n;
}

void inicializar_partida(){
    nave = inicializar_nave(100,100);
    tse = formatear(nave->spnorm);
    T_VECTOR off = {.x = 0, .y = 0};
    tse2 = virar(tse, 0, off);

    // Inicializamos o vector de teclas a 0
    for(int i=0; i<NUM_TECLAS; i++){
        TECLAS[i] = 0;
    }
    //SDL_EnableKeyRepeat(0,0);
    return;
}

void manexar_entrada(){
    if(TECLAS[SDLK_a]){
        nave->dir.x = -1; nave->dir.y = 0;
    }
    if(TECLAS[SDLK_d]){
        nave->dir.x = 1; nave->dir.y = 0;
    }
    if(TECLAS[SDLK_w]){
        nave->dir.x = 0; nave->dir.y = -1;
    }
    if(TECLAS[SDLK_s]){
        nave->dir.x = 0; nave->dir.y = 1;
    }
    // Esta parado
    if(!TECLAS[SDLK_s] && !TECLAS[SDLK_w] && !TECLAS[SDLK_d] && !TECLAS[SDLK_a]){
        nave->dir.x = 0; nave->dir.y = 0;
    }
    return;
}


int eventos_partida(){
    
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        switch(e.type){
            case SDL_QUIT:
                return 1;
            case SDL_KEYDOWN:
                //printf("PRESIONADA %d\n", ((uint8_t)e.key.keysym.sym));
                TECLAS[((uint8_t)e.key.keysym.sym)] = 1;
                break;
            case SDL_KEYUP:
                //printf("LIBERADA %d\n", ((uint8_t)e.key.keysym.sym));
                TECLAS[((uint8_t)e.key.keysym.sym)] = 0;
                break;
            default:
                break;
                //nave->dir.x = 0; nave->dir.y = 0;
        }
    }
    manexar_entrada();
    return 0;
    
    //if (teclado()) { return 1; }
    //manexar_entrada();
    //return 0;
}

int actualizar_partida(){
    nave->p.x += nave->dir.x;
    nave->p.y += nave->dir.y;
    return 0;
}

int debuxar_partida(SDL_Renderer* rend){
    SDL_RenderClear(rend);
    //Debuxar nave xirada
    //T_SUPERFICIE_EXT* tse = formatear(nave->spnorm);
    //T_SUPERFICIE_EXT* tse2 = virar(tse, i);
    //contador++;
    //if (contador == 50) { i += 15; contador = 0;}
    //SDL_Texture* textura = SDL_CreateTextureFromSurface(rend, tse2->superficie);
    //SDL_Rect dst = { .x = 200, .y = 200, .w = tse->superficie->w * FA, .h = tse->superficie->h * FA };
    //SDL_RenderCopy(rend, textura, NULL, &dst);
    //SDL_DestroyTexture(textura);
    // Debuxar nave
    T_VECTOR off = {.x = 2, .y = 2};
    nave->tse = virar(tse, nave->grados, off);
    SDL_Texture* textura2 = SDL_CreateTextureFromSurface(rend, nave->tse->superficie);
    SDL_Rect dst2 = { .x = nave->p.x + ((int)(nave->tse->offset.x * FA)),
                      .y = nave->p.y + ((int)(nave->tse->offset.y * FA)),
                      .w = nave->tse->superficie->w * FA,
                      .h = nave->tse->superficie->h * FA };
    SDL_RenderCopy(rend, textura2, NULL, &dst2);
    SDL_DestroyTexture(textura2);
    SDL_RenderPresent(rend);
    return 0;
}

void free_partida(){
    return;
}
