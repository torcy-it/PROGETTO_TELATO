#include <stdio.h>
#include <stdlib.h>
#include "grafi.h"

int main()
{

    Grafo G;

    int numero_nodi;

    printf("Hello world!\n");
    printf("\nWUanti nodi vuoi nel tuo grafo?");
    scanf("%d", &numero_nodi);

    G = crea_grafo( numero_nodi );
    stampa_grafo( G );


    return 0;
}
