//#include<stdio.h>
#include "lista.h"

LISTA_T* ini_lista(int tam_elemento) {
    LISTA_T* l = malloc(sizeof(LISTA_T));
    l->tam_elemento = tam_elemento;
    l->tam = 0;
    l->elementos = NULL;
    return l;
}


void engadir(LISTA_T* l, void* elemento){
    l->tam++;
    if (l->elementos == NULL)
        l->elementos = malloc(l->tam_elemento);
    else 
        l->elementos = realloc(l->elementos, l->tam * l->tam_elemento);
    
    l->elementos[l->tam-1] = elemento;
}


void desprazar_esq(LISTA_T* l, int idx){
    for (int i = idx; i < l->tam-1; i++){
        l->elementos[i] = l->elementos[i+1];
    }
    return;
} 


int eliminar(LISTA_T* l, int idx, void (*free_metodo)(void* x)){
    if (l->tam > idx){
        if (free_metodo) free_metodo(l->elementos[idx]);
        desprazar_esq(l,idx);
        l->tam--;
        l->elementos = realloc(l->elementos, l->tam_elemento * l->tam);
        return 0;
    }
    return 1;
}

// devolver o indice dun elemento da lista
int dev_idx(LISTA_T* l, void* elemento){
    for (int i = 0; i < l->tam; i++)
        if (l->elementos[i] == elemento) return i;
    return -1;
}


int remover(LISTA_T* l, void* elemento, void (*free_metodo)(void* x)){
    int idx = dev_idx(l, elemento);
    if (idx >= 0 ){
        eliminar(l, idx, free_metodo);
        return 0;
    }
    return 1; //fallou en atopar o indice en dev_idx
}


void* get(LISTA_T* l, int idx){
    return l->elementos[idx];
}


int tam(LISTA_T* l){
    return l->tam;
} 


// A diferencia de dev_idx esta funcion busca o 1er elemento
// da lista que cumpla a funcion equals. -1 error busqueda
int buscar(LISTA_T* l, void* elemento, int (*equals_metodo)(void* x,  void* y)){
    for (int i=0; i < l->tam; i++)
        if (equals_metodo(l->elementos[i], elemento)) return i;
    
    return -1;
}

void free_lista(LISTA_T* l, void(*free_metodo)(void* x)){
    for (int i=0; i < l->tam; i++)
        free_metodo(l->elementos[i]);
    
    free(l->elementos);
    free(l);
    return;
}




