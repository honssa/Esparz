#ifndef LISTA_H
#define LISTA_H
//#include<stdio.h>
#include<stdlib.h>

// OCULTAR ESTO PARA FACER INTERFAZ
typedef struct LISTA {
    int tam_elemento;
    int tam;
    void** elementos;
} LISTA_T;


LISTA_T* ini_lista(int tam_elemento);
void engadir(LISTA_T* l, void* elemento);
void* get(LISTA_T* l, int idx);
int tam(LISTA_T* l);
int remover(LISTA_T* l, void* elemento, void (*free_metodo)(void* x));
int eliminar(LISTA_T* l, int idx, void (*free_metodo)(void* x));
int buscar(LISTA_T* l, void* elemento, int (*equals_metodo)(void* x, void* y));
void free_lista(LISTA_T* l, void(*free_metodo)(void* x));

#endif




