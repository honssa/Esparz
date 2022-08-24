#include "boton.h"


// Pasaslle un texto e devolveche a structura boton asociada
T_BOTON* inicializar_boton(const char* texto, SDL_Point pos, void(*funcion_chamada)()){
    T_BOTON* btn = malloc(sizeof(T_BOTON));
    SDL_Rect dst = {.x = pos.x, .y = pos.y, .w = DIMENSION_X * FA, .h = DIMENSION_Y * FA};
    btn->dst = dst;
    btn->base = SDL_CreateRGBSurface(SDL_SWSURFACE, DIMENSION_X, DIMENSION_Y, 8, 0, 0, 0, 0);
    SDL_SetPaletteColors(btn->base->format->palette, gcolors, 0, 2);

    btn->sens = SDL_CreateRGBSurface(SDL_SWSURFACE, FLECHA_DIM_X, FLECHA_DIM_Y, 8, 0, 0, 0, 0);
    SDL_SetPaletteColors(btn->sens->format->palette, gcolors, 0, 2);
    uint8_t debuxo_flecha[FLECHA_DIM_Y][FLECHA_DIM_X] = FLECHA;
    SDL_Point pf = {.x=0,.y=0}; SDL_Point tamf = {.x=FLECHA_DIM_X,.y=FLECHA_DIM_Y};
    debuxar_matriz(btn->sens, pf, tamf, &debuxo_flecha[0][0]);


    btn->prem = SDL_CreateRGBSurface(SDL_SWSURFACE, PDIM_X, PDIM_Y, 8, 0, 0, 0, 0);
    SDL_SetPaletteColors(btn->prem->format->palette, gcolors, 0, 2);

    btn->funcion_chamada = funcion_chamada;




    // Debuxar o boton base
    SDL_Point p1 = {.x = 0, .y = 0}; SDL_Point p2 = {.x = 51, .y=0};
    debuxar_rectangulo(btn->base, p1, p2, 1);

    p1.x = 0; p1.y = 1; p2.x = 0; p2.y=18;
    debuxar_rectangulo(btn->base, p1, p2, 1);

    p1.x = 51; p1.y = 1; p2.x = 51; p2.y=18;
    debuxar_rectangulo(btn->base, p1, p2, 1);

    p1.x = 0; p1.y = 19; p2.x = 51; p2.y=22;
    debuxar_rectangulo(btn->base, p1, p2, 1);

    p1.x = 6; p1.y = 6;
    debuxar_texto(btn->base, p1, texto);

    // Debuxar o boton premido
    p1.x = 0; p1.y = 0; p2.x = 51; p2.y=0;
    debuxar_rectangulo(btn->prem, p1, p2, 1);

    p1.x = 0; p1.y = 1; p2.x = 0; p2.y=18;
    debuxar_rectangulo(btn->prem, p1, p2, 1);

    p1.x = 51; p1.y = 1; p2.x = 51; p2.y=18;
    debuxar_rectangulo(btn->prem, p1, p2, 1);

    p1.x = 0; p1.y = 19; p2.x = 51; p2.y=19;
    debuxar_rectangulo(btn->prem, p1, p2, 1);

    p1.x = 6; p1.y = 6;
    debuxar_texto(btn->prem, p1, texto);

    return btn;

}


T_BOTONS* inicializar_botons(T_BOTON* b1, T_BOTON* b2, T_BOTON* b3, T_BOTON* b4){
    T_BOTONS* botons = malloc(sizeof(T_BOTONS));
    botons->boton_sensado = -1;
    botons->click = false;

    botons->arr_botons[0] = b1;
    botons->arr_botons[1] = b2;
    botons->arr_botons[2] = b3;
    botons->arr_botons[3] = b4;

    return botons;

}

void free_botons(T_BOTONS* botons){
  for (int i=0; i<4; i++){
    SDL_FreeSurface(botons->arr_botons[i]->base);
    SDL_FreeSurface(botons->arr_botons[i]->sens);
    SDL_FreeSurface(botons->arr_botons[i]->prem);
    free(botons->arr_botons[i]);
  }
  free(botons);  
}

void actualizar_botons(T_BOTONS* botons, int cursor_x, int cursor_y){
    botons->boton_sensado = -1;
    for (int i = 0; i < NUM_BOTONS; i++){
        if (( cursor_x > botons->arr_botons[i]->dst.x && \
            cursor_x < (botons->arr_botons[i]->dst.x+botons->arr_botons[i]->dst.w)) \
            && ( cursor_y > botons->arr_botons[i]->dst.y && \
            cursor_y < (botons->arr_botons[i]->dst.y+botons->arr_botons[i]->dst.h) )){
                botons->boton_sensado = i;
                break;
        }
    }
    return;
}


void debuxar_botons(SDL_Renderer* rend, T_BOTONS* botons){
    // Debuxa todos os botons
    for (int i = 0; i < NUM_BOTONS; i++){
        if (botons->boton_sensado == i){
            if (botons->click) {
                SDL_Texture* textura = SDL_CreateTextureFromSurface(rend, botons->arr_botons[i]->prem);
                SDL_Rect dst = {.x = botons->arr_botons[i]->dst.x,      \
                                .y = botons->arr_botons[i]->dst.y + 9,  \
                                .w = botons->arr_botons[i]->prem->w * FA,    \
                                .h = botons->arr_botons[i]->prem->h * FA};
                SDL_RenderCopy(rend, textura, NULL, &dst);
                SDL_DestroyTexture(textura);
            }
            else{
                // Debuxar ese boton sensado ou clicado
                SDL_Texture* textura = SDL_CreateTextureFromSurface(rend, botons->arr_botons[i]->base);
                SDL_Rect dst = botons->arr_botons[i]->dst;
                SDL_RenderCopy(rend, textura, NULL, &dst);
                SDL_DestroyTexture(textura);

                SDL_Texture* textura2 = SDL_CreateTextureFromSurface(rend, botons->arr_botons[i]->sens);
                SDL_Rect dst2 = {.x = dst.x-36, .y = dst.y+21, .w = FLECHA_DIM_X * FA,.h = FLECHA_DIM_Y * FA};
                SDL_RenderCopy(rend, textura2, NULL, &dst2);
                SDL_DestroyTexture(textura2);
            }

        }
        else{
            // Debuxar ese boton normal
            SDL_Texture* textura = SDL_CreateTextureFromSurface(rend, botons->arr_botons[i]->base);
            SDL_Rect dst = botons->arr_botons[i]->dst;
            SDL_RenderCopy(rend, textura, NULL, &dst);
            SDL_DestroyTexture(textura);
        }
    }
    return;
}
