#include "partida.h"

T_NAVE* nave;
T_SUPERFICIE_EXT* tse;
//T_SUPERFICIE_EXT* tse2;
uint8_t TECLAS[NUM_TECLAS];
T_VECTOR* acu_posicion;
float acu_propulsion_dta;
float acu_propulsion_esq;
int xiro_agarda;
int recarga;

LISTA_T* l; 

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
    //uint8_t* matriz = malloc(sizeof(uint8_t)*DIMX_NAVE*DIMY_NAVE);
    uint8_t mnave[DIMX_NAVE][DIMY_NAVE] = NAVE;
    SDL_Point ptmp = {.x = 0, .y = 0}; SDL_Point tamtmp = {.x = DIMX_NAVE, .y = DIMY_NAVE};
    debuxar_matriz(n->spnorm, ptmp, tamtmp, &mnave[0][0]);
    n->tse = formatear(n->spnorm);
    n->grados = 0;
    return n;
}

T_PROXECTIL* inicializar_proxectil(SDL_Point p, T_VECTOR dir){
    T_PROXECTIL* proxectil = malloc(sizeof(T_PROXECTIL));
    
    // Debuxo do proxectil
    proxectil->dbx = SDL_CreateRGBSurface(SDL_SWSURFACE, DIMX_PROXECTIL, DIMY_PROXECTIL, 8, 0, 0, 0, 0);
    SDL_SetPaletteColors(proxectil->dbx->format->palette, gcolors, 0, 2);
    //uint8_t* matriz = malloc(sizeof(uint8_t)*DIMX_PROXECTIL*DIMY_PROXECTIL);
    uint8_t mproxectil[DIMX_PROXECTIL][DIMY_PROXECTIL] = PROXECTIL;
    SDL_Point ptmp = {.x = 0, .y = 0}; SDL_Point tamtmp = {.x = DIMX_PROXECTIL, .y = DIMY_PROXECTIL};
    debuxar_matriz(proxectil->dbx, ptmp, tamtmp, &mproxectil[0][0]);
    
    // Posicion e direcion
    SDL_Point tmp = {.x = p.x, .y = p.y};
    T_VECTOR tmp2 = {.x = dir.x, .y = dir.y};
    proxectil->p = tmp;
    proxectil->dir = tmp2;
    T_VECTOR acu_p = {.x = 0, .y = 0}; 
    proxectil->acu_p = acu_p;
    return proxectil;
}

void inicializar_partida(){
    nave = inicializar_nave(100,100);
    tse = formatear(nave->spnorm);
    acu_posicion = malloc(sizeof(T_VECTOR));
    acu_posicion->x = 0; acu_posicion->y = 0; // coordenadas clasicas
    recarga = 0; // Tempo de espera ata volver a disparar
    //T_VECTOR off = {.x = 0, .y = 0};
    //tse2 = virar(tse, 0, off, &nave->dir);

    // Inicializamos o vector de teclas a 0
    for(int i=0; i<NUM_TECLAS; i++){
        TECLAS[i] = 0;
    }
    acu_propulsion_esq = 0; acu_propulsion_dta = 0;
    xiro_agarda = 0;

    // Inicializar lista de proxectiles
    l = ini_lista(sizeof(T_PROXECTIL));
    //SDL_EnableKeyRepeat(0,0);
    return;
}

void simular_movemento() {
    //float acu_prop = acu_propulsion_esq + acu_propulsion_dta;
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

void simular_movemento_proba(){
    if (TECLAS[SDLK_w]) {
        nave->p.y -= 1;
    }
    if (TECLAS[SDLK_a]) {
        nave->p.x -= 1;
    }
    if (TECLAS[SDLK_s]) {
        nave->p.y += 1;
    }
    if (TECLAS[SDLK_d]) {
        nave->p.x += 1;
    }
}

void spawn_proxectil(){
    // Debuxamos un proxectil e movemolo en direcion Vdir da nave
    // Temos que engadilo a lista de proxectiles
    // Esta lista conten todos os proxectiles a actualizar e 
    // debuxar 
    // Cando o proxectil saia da pantalla eliminamolo da lista
    SDL_Point p = {.x = nave->p.x + (DIMX_NAVE/2)*FA, .y = nave->p.y + (DIMY_NAVE/2)*FA};
    T_PROXECTIL* proxectil = inicializar_proxectil(p, nave->dir);
    engadir(l, proxectil);
    printf("Dir proxectil: %f, %f\n", proxectil->dir.x, proxectil->dir.y);
    printf("Dir nave: %f, %f\n", nave->dir.x, nave->dir.y);
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
    if (TECLAS[SDLK_l] && !recarga) {
        // Disparamos proxectil
        spawn_proxectil();
        recarga = 120;
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
    //simular_movemento_proba();
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

    // Actualizar a posicion dos proxectiles
    for(int i=0; i<tam(l); i++){
        T_PROXECTIL* proxectil = (T_PROXECTIL*) get(l,i);
        proxectil->acu_p.x += proxectil->dir.x * 2.5;
        proxectil->acu_p.y += -proxectil->dir.y * 2.5;
        proxectil->p.x += floor(proxectil->acu_p.x);
        proxectil->acu_p.x -= floor(proxectil->acu_p.x);
        proxectil->p.y += floor(proxectil->acu_p.y);
        proxectil->acu_p.y -= floor(proxectil->acu_p.y);
    }
    // Actualizar o tempo de recarga
    recarga = MAX(0,recarga-1);
    //printf("Dir nave: < %f , %f > \n", nave->dir.x, nave->dir.y);
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
    if (dst2.x < -dst2.w) {
        dst2.x += XANELA_ANCHO;
        nave->p.x += XANELA_ANCHO;
        goto FINAL_WRAPEO;
    }
    else if ((dst2.x + dst2.w) > (XANELA_ANCHO+dst2.w)) {
        dst2.x -= XANELA_ANCHO;
        nave->p.x -= XANELA_ANCHO;
        goto FINAL_WRAPEO;
    }
    else if (dst2.y < -dst2.h) {
        dst2.y += XANELA_ALTO;
        nave->p.y += XANELA_ALTO;
        goto FINAL_WRAPEO;
    }
    else if ((dst2.y + dst2.h) > (XANELA_ALTO+dst2.h)) {
        dst2.y -= XANELA_ALTO;
        nave->p.y -= XANELA_ALTO;
        goto FINAL_WRAPEO;
    }
    if (dst2.x < 0 || (dst2.x+dst2.w) > XANELA_ANCHO || dst2.y < 0 || (dst2.y+dst2.h) > XANELA_ALTO) {
        // Se te saes moito tes que reposicionar o orixinal e borrar o fantasma
        //if ( dst2.x < -dst2.w ) {
        //    dst2.x += XANELA_ANCHO;
            // Perdoame Edsger Djikstra
        //    goto FINAL_WRAPEO;
        //}

        if (dst2.x < 0) {
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

        // Se esta nunha esquina
        if ( (dst2.x < 0 || (dst2.x + dst2.w) > XANELA_ANCHO ) && (dst2.y < 0 || (dst2.y + dst2.h) > XANELA_ALTO) ) {
            // Creamos outras duas texturas e as debuxamos xa directamente aqui nas posicions correspondentes
            
            // A reflexada en X da orixinal
            SDL_Texture* dup3 = SDL_CreateTextureFromSurface(rend, nave->tse->superficie);
            SDL_Rect dst_dup3; 
            if (dst2.x < 0) {
                dst_dup3.x = dst2.x + XANELA_ANCHO;
            }
            else if ( (dst2.x + dst2.w) > XANELA_ANCHO) {
                dst_dup3.x = dst2.x - XANELA_ANCHO;
            }
            dst_dup3.y = dst2.y;
            dst_dup3.w = dst2.w;
            dst_dup3.h = dst2.h;

            // A reflexada en Y da orixinal (porque o reflexo orixinal e o diagonal)
            SDL_Texture* dup4 = SDL_CreateTextureFromSurface(rend, nave->tse->superficie);
            SDL_Rect dst_dup4; 
            if (dst2.y < 0) {
                dst_dup4.y = dst2.y + XANELA_ALTO;
            }
            else if ( (dst2.y + dst2.h) > XANELA_ALTO) {
                dst_dup4.y = dst2.y - XANELA_ALTO;
            }
            dst_dup4.x = dst2.x;
            dst_dup4.w = dst2.w;
            dst_dup4.h = dst2.h;

                                    
                                
            SDL_RenderCopy(rend, dup3, NULL, &dst_dup3);
            SDL_RenderCopy(rend, dup4, NULL, &dst_dup4);
            
        }
        
        dst_dup.w = dst2.w;
        dst_dup.h = dst2.h;

        printf("Forma da estructura: x: %d, y: %d, w:%d , h: %d\n", dst_dup.x, dst_dup.y, dst_dup.w, dst_dup.h);

        SDL_RenderCopy(rend, duplicada, NULL, &dst_dup);
        // ola!
        //SDL_DestroyTexture(textura2);

        
    }
FINAL_WRAPEO:
    SDL_RenderCopy(rend, textura2, NULL, &dst2);
    SDL_DestroyTexture(textura2);
    
    for(int i=0; i<tam(l); i++){
        T_PROXECTIL* proxectil = (T_PROXECTIL*) get(l,i);
        SDL_Rect dst_tmp = { .x = proxectil->p.x,
                          .y = proxectil->p.y,
                          .w = proxectil->dbx->w * FA,
                          .h = proxectil->dbx->h * FA };
        SDL_Texture* textura_tmp = SDL_CreateTextureFromSurface(rend, proxectil->dbx);
        SDL_RenderCopy(rend, textura_tmp, NULL, &dst_tmp);
    }
    SDL_RenderPresent(rend);
    return 0;
}

void free_partida(){
    return;
}
