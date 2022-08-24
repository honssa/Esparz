#include "director.h"
#include "menu.h"

int main(){
    // Inicializar director
    T_PILA* pila_escenas = inicializar();

    // Inicializar a primeira escena do xogo (menu)
    T_ESCENA* menu = inicializarEscena(ESCENA_MENU, inicializar_menu, eventos_menu,
                                      actualizar_menu, debuxar_menu, free_menu);

    // Apilar a primeira escena do xogo (menu)
    apilar(pila_escenas, menu);

    // Iniciar o bucle do xogo do director
    bucleEventos();

    // Finalizar execucion do director
    finalizarExecucion();
  
    // Liberar memoria da pila
    baleirar(pila_escenas);
    free(pila_escenas);
    // sair do programa
    return 0;
}
