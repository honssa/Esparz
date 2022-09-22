#include "partida.h"

T_NAVE* nave;
T_SUPERFICIE_EXT* tse;
//T_SUPERFICIE_EXT* tse2;
uint8_t TECLAS[NUM_TECLAS];
T_VECTOR* acu_posicion;
float acu_propulsion_dta;
float acu_propulsion_esq;
int xiro_agarda;

int i = 0, contador = 0;

T_NAVE* inicializar_nave(uint8_t x, uint8_t y){
    T_NAVE* n = malloc(sizeof(T_NAVE));
    SDL_Point pos = {.x = x, .y = y};
    T_VECTOR dir = {.x = 0, .y = 1}; // coordenadas clasicas
    n->p = pos;
    n->dir = dir;
    n->impulso = 0; 
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
    acu_posicion = malloc(sizeof(T_VECTOR));
    acu_posicion->x = 0; acu_posicion->y = 0; // coordenadas clasicas
    T_VECTOR off = {.x = 0, .y = 0};
    //tse2 = virar(tse, 0, off, &nave->dir);

    // Inicializamos o vector de teclas a 0
    for(int i=0; i<NUM_TECLAS; i++){
        TECLAS[i] = 0;
    }
    acu_propulsion_esq = 0; acu_propulsion_dta = 0;
    xiro_agarda = 0;
    //SDL_EnableKeyRepeat(0,0);
    return;
}

void simular_movemento() {
    float acu_prop = acu_propulsion_esq + acu_propulsion_dta;
    float prop_dif = acu_propulsion_dta - acu_propulsion_esq;
    if (prop_dif > 0) xiro_agarda++;
    else if (prop_dif < 0) xiro_agarda--;
    if ( ABS(xiro_agarda) >= round(11.0 - ABS(prop_dif)/12.) ){
        if (xiro_agarda < 0) { nave->grados -=5; }
        else if (xiro_agarda > 0) { nave->grados +=5; }
        
        // Restablecer grados
        if (nave->grados < -360){
            nave->grados += 360;
        }
        else if (nave->grados > 360) {
            nave->grados -= 360;
        }

        xiro_agarda = 0;
    }
    T_VECTOR off = {.x = 0, .y = 0};
    nave->tse = virar(tse, nave->grados, off, &nave->dir);
    nave->impulso = (MAX(acu_propulsion_esq,acu_propulsion_dta)/120)*2.5;
    return;
}

void manexar_entrada(){
    if (TECLAS[SDLK_a]) {
        acu_propulsion_esq = MIN(120, acu_propulsion_esq++);
    }
    if (TECLAS[SDLK_f]) {
        acu_propulsion_dta = MIN(120, acu_propulsion_dta++);
    }
    if (!TECLAS[SDLK_a]) {
        acu_propulsion_esq = MAX(0, acu_propulsion_esq--);
    }
    if (!TECLAS[SDLK_f]) {
        acu_propulsion_dta = MAX(0, acu_propulsion_dta--);
    }
    /*
    if(TECLAS[SDLK_a] && TECLAS[SDLK_f]){
        acu_propulsion_esq = MIN(240, acu_propulsion_esq++);
        xiro_agarda_esq++;
        if (xiro_agarda_esq >= round(11.0 - (acu_propulsion_esq/24.)) ){
            xiro_agarda_esq = 0;
            nave->grados-=5;
        }
        //nave->grados += -5;
        if (nave->grados < -360){
            nave->grados += 360;
        }
        T_VECTOR off = {.x = 0, .y = 0};
        nave->tse = virar(tse, nave->grados, off, &nave->dir);
        nave->impulso = (acu_propulsion_esq/240)*4;
    }
    if(TECLAS[SDLK_f] && !TECLAS[SDLK_a]){
        acu_propulsion_dta = MIN(240, acu_propulsion_dta++);
        xiro_agarda_dta++;
        if (xiro_agarda_dta >= round(11.0 - (acu_propulsion_dta/24.)) ){
            xiro_agarda_dta = 0;
            nave->grados+=5;
        }
        //nave->grados += 5;
        if (nave->grados > 360){
            nave->grados -= 360;
        }
        T_VECTOR off = {.x = 0, .y = 0};
        nave->tse = virar(tse, nave->grados, off, &nave->dir);
        nave->impulso = (acu_propulsion_dta/240)*4;
        //printf("direccion: %f , %f \n", nave->dir.x, nave->dir.y);
        printf("acu_propulsion_dta: %f\n", acu_propulsion_dta++);
    }
    //else{
    //}
    // Esta parado
    if(!TECLAS[SDLK_s] && !TECLAS[SDLK_a]){
        acu_propulsion_dta = MAX(0, acu_propulsion_dta--);
        acu_propulsion_esq = MAX(0, acu_propulsion_esq--);
        nave->impulso = (acu_propulsion_dta/240)*4;
        //nave->impulso = (acu_propulsion_esq/240)*4;
    //    nave->impulso = 0;
        //nave->dir.x = 0; nave->dir.y = 0;
    }
    if (TECLAS[SDLK_a] && TECLAS[SDLK_f]){
        if (acu_propulsion_esq > acu_propulsion_dta){
            acu_propulsion_esq -= acu_propulsion_dta;
            nave->impulso = ((acu_propulsion_dta + acu_propulsion_esq)/240)*4;
        }
        //ABS(acu_propulsion_esq - acu_propulsion_dta)
    }
    */
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
    simular_movemento();
    SDL_Point p_enteira = {.x = 0, .y = 0};
    acu_posicion->x += nave->dir.x * nave->impulso;
    acu_posicion->y += -nave->dir.y * nave->impulso;
    // Se e menor que un nada, se e maior sacalle a parte enteira e actualizas posicion
    if (ABS(acu_posicion->x) > 1.0){
        p_enteira.x = ((int)acu_posicion->x);
        acu_posicion->x -= ((float)p_enteira.x);
    }
    if (ABS(acu_posicion->y) > 1.0){
        p_enteira.y = ((int)acu_posicion->y);
        acu_posicion->y -= ((float)p_enteira.y);
    }
    nave->p.x += p_enteira.x;
    nave->p.y += p_enteira.y;
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
    SDL_Texture* textura2 = SDL_CreateTextureFromSurface(rend, nave->tse->superficie);
    SDL_Rect dst2 = { .x = nave->p.x + ((int)(nave->tse->offset.x * FA)),
                      .y = nave->p.y + ((int)(nave->tse->offset.y * FA)),
                      .w = nave->tse->superficie->w * FA,
                      .h = nave->tse->superficie->h * FA };

    // Screen wrapping
    SDL_Texture* duplicada = SDL_CreateTextureFromSurface(rend, nave->tse->superficie);
    SDL_Rect dst_dup;
    if (dst2.x < 0 || (dst2.x+dst2.w) > XANELA_ANCHO || dst2.y < 0 || (dst2.y+dst2.h) > XANELA_ALTO) {
        if (dst2.x < 0) {
            printf("wrapping\n");
            dst_dup.x = XANELA_ANCHO + dst2.x;
            //dst_dup.w = dst2.w;
            //dst_dup.h = dst2.h;
            //dst_dup.y = dst2.y;
        }
        else if ( (dst2.x + dst2.w) > XANELA_ANCHO) {
            dst_dup.x = dst2.x - XANELA_ANCHO;
        }
        
        else {
            dst_dup.x = dst2.x;
        }
        if ( dst2.y < 0) {
            dst_dup.y = XANELA_ALTO + dst2.y;

        }
        else if ( (dst2.y + dst2.h) > XANELA_ALTO) {
            dst_dup.y = dst2.y - XANELA_ALTO;

        }
        else {
            dst_dup.y = dst2.y;
        }
        
        dst_dup.w = dst2.w;
        dst_dup.h = dst2.h;

        printf("Forma da estructura: x: %d, y: %d, w:%d , h: %d\n", dst_dup.x, dst_dup.y, dst_dup.w, dst_dup.h);

        SDL_RenderCopy(rend, duplicada, NULL, &dst_dup);
        //SDL_DestroyTexture(textura2);

        
    }
    SDL_RenderCopy(rend, textura2, NULL, &dst2);
    SDL_DestroyTexture(textura2);
    SDL_RenderPresent(rend);
    return 0;
}

void free_partida(){
    return;
}
