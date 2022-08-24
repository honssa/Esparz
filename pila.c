#include "pila.h"


T_PILA* inicializar_pila(){
    T_PILA* p = malloc(sizeof(T_PILA));
    p->cabeza = NULL;
    return p;
}


void apilar(T_PILA* p, void* elemento){
    T_NODO* n = malloc(sizeof(T_NODO));
    n->elemento = elemento;

    if (p->cabeza == NULL) {n->anterior = NULL; p->cabeza = n;}
    else {n->anterior = p->cabeza; p->cabeza = n;}
}

// Devolve 1 se a lista esta baleira ou non se puido eliminar
int desapilar(T_PILA* p){
    if (p->cabeza == NULL) return 1; // Lista baleira
    else if(p->cabeza->anterior == NULL){ // So 1 elemento -> baleira a lista
        free(p->cabeza->elemento);
        free(p->cabeza);
        p->cabeza = NULL;
        return 1;
    }
    else {  // Varios elementos -> o anterior á cabeza pasa a ser a cabeza
        T_NODO* aux = p->cabeza;
        p->cabeza = p->cabeza->anterior;
        free(aux->elemento);
        free(aux);
    }
    return 0;
}


void baleirar(T_PILA* p){
    int pila_baleira = 0;
    do{
        pila_baleira = desapilar(p);
    } while(!pila_baleira);
}

