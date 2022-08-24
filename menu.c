#include "menu.h"

char mensaxe[8] = "FPS = ";
T_BOTONS* botons;
SDL_Surface* titulo;
SDL_Surface* autor;

void facer_nada(){return;}

SDL_Surface* inicializar_titulo(){
    SDL_Surface* s = SDL_CreateRGBSurface(SDL_SWSURFACE, DIMX_TITULO, DIMY_TITULO, 8, 0, 0, 0, 0);
    SDL_SetPaletteColors(s->format->palette, gcolors, 0, 2);
    SDL_Point tam = {.x = DIMX_TITULO, .y = DIMY_TITULO}; SDL_Point p = {.x = 0, .y = 0};
    uint8_t* matriz = malloc(sizeof(uint8_t)*DIMX_TITULO*DIMY_TITULO);
    //memset(matriz, 0, nova_altura*nova_anchura);
    int arr[DIM_TITULO] = TITULO;

    int i = 0, acu = 0;
    uint8_t cor = 0;
    while(i < DIM_TITULO){
        // Alternas a cor

        if ((acu % DIMX_TITULO) == 0) cor = 0;
        else cor = (cor * -1) + 1;
        if ((arr[i-1] == 0) && (i>0)) cor = 1; // Solucia problemas de comezo con branco

        // Escribes os bytes
        memset((matriz+acu), cor, arr[i]);

        // Seguinte iteracion
        acu += arr[i];
        i++;
    }
    debuxar_matriz(s,p,tam,matriz);
    free(matriz);
    return s;
}


SDL_Surface* inicializar_autor(){
    SDL_Surface* s = SDL_CreateRGBSurface(SDL_SWSURFACE, AUTOR_X, AUTOR_Y, 8, 0, 0, 0, 0);
    SDL_SetPaletteColors(s->format->palette, gcolors, 0, 2);
    SDL_Point tam = {.x = AUTOR_X, .y = AUTOR_Y}; SDL_Point p = {.x = 0, .y = 0};
    uint8_t* matriz = malloc(sizeof(uint8_t)*AUTOR_X*AUTOR_Y);

    int arr[TAM_AUTOR] = AUTOR;

    int i = 0, acu = 0;
    uint8_t cor = 0;
    while(i < TAM_AUTOR){
        // Alternas a cor
        if ((acu % AUTOR_X) == 0) cor = 0;
        else cor = (cor * -1) + 1;
        if ((arr[i-1] == 0) && (i>0)) cor = 1; // Solucia problemas de comezo con branco

        // Escribes os bytes
        memset((matriz+acu), cor, arr[i]);

        // Seguinte iteracion
        acu += arr[i];
        i++;
    }
    debuxar_matriz(s,p,tam,matriz);
    free(matriz);
    return s;
}


void debuxar_titulo(SDL_Renderer* rend){
    SDL_Texture* textura = SDL_CreateTextureFromSurface(rend, titulo);
    SDL_Rect dst = {.x = 100, .y = 25, .w = DIMX_TITULO * FA,.h = DIMY_TITULO * FA};
    SDL_RenderCopy(rend, textura, NULL, &dst);
    SDL_DestroyTexture(textura);
}

void debuxar_autor(SDL_Renderer* rend){
    SDL_Texture* textura = SDL_CreateTextureFromSurface(rend, autor);
    SDL_Rect dst = {.x = 350, .y = 160, .w = AUTOR_X * FA,.h = AUTOR_Y * FA};
    SDL_RenderCopy(rend, textura, NULL, &dst);
    SDL_DestroyTexture(textura);
}


void inicializar_menu(){
    // Inicializamos todos os botons
    SDL_Point pos = {.x = XANELA_ANCHO/2 - (DIMENSION_X*3)/2, .y = 220};
    T_BOTON* boton = inicializar_boton("LOCAL", pos, facer_nada);

    pos.y = 300;
    T_BOTON* boton2 = inicializar_boton("EN LI$A", pos, facer_nada);

    pos.x = 50; pos.y = 400;
    T_BOTON* boton3 = inicializar_boton("A", pos, facer_nada);

    pos.x = 470; pos.y = 400;
    T_BOTON* boton4 = inicializar_boton("B", pos, facer_nada);

    botons = inicializar_botons(boton, boton2, boton3, boton4);

    titulo = inicializar_titulo();
    autor = inicializar_autor();

    return;
}


int eventos_menu(){
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_QUIT:
                printf("Pechase");
                return 1;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT){
                    botons->click = true;
                }

                break;
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT){
                    botons->click = false;
                }
                break;
        }
    }
    return 0;
}


int actualizar_menu(){
    int cursor_x, cursor_y;
    int buttons = SDL_GetMouseState(&cursor_x, &cursor_y);
    actualizar_botons(botons, cursor_x, cursor_y);
    return 0;

}


int debuxar_menu(SDL_Renderer* rend){
    SDL_RenderClear(rend); // Borrar a pantalla
    debuxar_botons(rend, botons); // debuxas os botons

    debuxar_titulo(rend); // debuxa o titulo
    debuxar_autor(rend);
    SDL_RenderPresent(rend); // Esto so se executa 1 vez cada frame
    return 0;
}


void free_menu(){
  // Free as surface de SDL
  SDL_FreeSurface(titulo);
  SDL_FreeSurface(autor);
  // Free aos botons (individuais)
  // Free a "botons" (colectivo)
  free_botons(botons);
  return
}
