#include "letras.h"

T_FONTE fonte = {.letra_A = LETRA_A, \
                 .letra_C = LETRA_C, \
                 .letra_E = LETRA_E, \
                 .letra_F = LETRA_F, \
                 .letra_I = LETRA_I, \
                 .letra_L = LETRA_L, \
                 .letra_N = LETRA_N, \
                 .letra_N2 = LETRA_N2, \
                 .letra_O = LETRA_O, \
                 .letra_P = LETRA_P, \
                 .letra_S = LETRA_S, \
                 .letra_IGUAL = LETRA_IGUAL,
                 .num_0 = NUM_0, \
                 .num_1 = NUM_1, \
                 .num_2 = NUM_2, \
                 .num_3 = NUM_3, \
                 .num_4 = NUM_4, \
                 .num_5 = NUM_5, \
                 .num_6 = NUM_6, \
                 .num_7 = NUM_7, \
                 .num_8 = NUM_8, \
                 .num_9 = NUM_9, \
                 .punto = PUNTO, \
                 .espazo = ESPAZO};

void imprimir_letra(const char letra, int index, SDL_Surface* sletras, SDL_Point p){
    uint8_t* trama_letra;
    switch(letra){
        case 'A':
            trama_letra = &fonte.letra_A[0][0];
            break;
        case 'C':
            trama_letra = &fonte.letra_C[0][0];
            break;
        case 'E':
            trama_letra = &fonte.letra_E[0][0];
            break;
        case 'F':
            trama_letra = &fonte.letra_F[0][0];
            break;
        case 'I':
            trama_letra = &fonte.letra_I[0][0];
            break;
        case 'L':
            trama_letra = &fonte.letra_L[0][0];
            break;
        case 'N':
            trama_letra = &fonte.letra_N[0][0];
            break;
        case '$':
            trama_letra = &fonte.letra_N2[0][0];
            break;
        case 'O':
            trama_letra = &fonte.letra_O[0][0];
            break;
        case 'P':
            trama_letra = &fonte.letra_P[0][0];
            break;
        case 'S':
            trama_letra = &fonte.letra_S[0][0];
            break;
        case '=':
            trama_letra = &fonte.letra_IGUAL[0][0];
            break;
        case '0':
            trama_letra = &fonte.num_0[0][0];
            break;
        case '1':
            trama_letra = &fonte.num_1[0][0];
            break;
        case '2':
            trama_letra = &fonte.num_2[0][0];
            break;
        case '3':
            trama_letra = &fonte.num_3[0][0];
            break;
        case '4':
            trama_letra = &fonte.num_4[0][0];
            break;
        case '5':
            trama_letra = &fonte.num_5[0][0];
            break;
        case '6':
            trama_letra = &fonte.num_6[0][0];
            break;
        case '7':
            trama_letra = &fonte.num_7[0][0];
            break;
        case '8':
            trama_letra = &fonte.num_8[0][0];
            break;
        case '9':
            trama_letra = &fonte.num_9[0][0];
            break;
        case '.':
            trama_letra = &fonte.punto[0][0];
            break;
        case ' ':
            trama_letra = &fonte.espazo[0][0];
            break;
        default:
            trama_letra = &fonte.num_0[0][0];
    }

    uint8_t* offscreen_l = (uint8_t*)sletras->pixels;
    offscreen_l += (sletras->pitch*p.y); // Se comentas a liña debuxacho arriba
    for (int i = 0; i < LETRA_ALTO; i++) {
        int cn = 0;
        for (int j = p.x; j < (LETRA_ANCHO+p.x); j++){
                offscreen_l[j+(index*LETRA_ANCHO)] = *(trama_letra+(i*LETRA_ANCHO+cn));//+j));
                cn++;
        }
        offscreen_l += sletras->pitch;
    }
}

// uso: imprimir_texto(rend, "hola_mundo", [2,3], 1);
SDL_Surface* imprimir_texto(const char* texto){
// Imprime o string na pantalla
    size_t numCaracteres = strlen(texto);
    SDL_Surface* stexto = SDL_CreateRGBSurface(SDL_SWSURFACE, LETRA_ANCHO*numCaracteres, LETRA_ALTO, 8, 0, 0, 0, 0);

    SDL_SetPaletteColors(stexto->format->palette, gcolors, 0, 2);
    SDL_Point p = {.x=0, .y=0};
    for (size_t len = strlen(texto), i = 0; i < len; i++){
        imprimir_letra(texto[i],i,stexto,p);
    }
    return stexto;
}

void debuxar_texto(SDL_Surface* s, SDL_Point p, const char* texto){
    for (size_t i = 0; i < strlen(texto); i++){
        imprimir_letra(texto[i],i,s,p);
    }
}

