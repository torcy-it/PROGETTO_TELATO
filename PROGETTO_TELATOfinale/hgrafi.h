#ifndef HGRAF_H
#define HGRAF_H

  
    struct archi
    {
        int lunghezza;
        int key;
        int peso; // settare ad 1
        
        struct archi *next;
    };
    typedef struct archi * arco;

    struct graph
    {
        int numero_vertici; // numero di vertici del grafo 
        struct archi **adj; // vettore con le liste delle adiacenze 
    };


    typedef struct graph * grafo;

    void dijkstra(grafo ,int ,int , int );

    void print_archi ( arco  );

    void stampa_grafo( grafo , int );

    int is_empty( grafo ); 

    void create_graph( grafo , FILE * , int *, bool );

    arco add_archi( arco , FILE * , bool * );

    int numero_vertici( grafo  );


#endif