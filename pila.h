#ifndef PILA_H
#define PILA_H
#include <stdlib.h> // Probablemente incluir algunhas librerias estandar mais
// declaracion de typedefs
typedef struct NODO {
    void* elemento;
    struct NODO* anterior;
}T_NODO;

typedef struct PILA{
    //size_t tam_item;
    //size_t tam;
    T_NODO* cabeza;
} T_PILA;

// declaracion de funcions
T_PILA* inicializar_pila();
void apilar(T_PILA* p, void* elemento);
int desapilar(T_PILA* p);
void baleirar(T_PILA* p);


// declaracion de macros
#endif
