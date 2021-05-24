

#ifndef graf
    #define graf

    struct graph
    {
        int numero_vertici; /* numero di vertici del grafo */
        struct archi **adj; /* vettore con le liste delle adiacenze */
    };
    typedef struct graph * Grafo;

    struct archi
    {
        int key;
        char nome[20];
        int peso;
        struct archi *next;
    };
    typedef struct archi * Arco;

    // ok
    //Grafo crea_grafo( int );
    //
    Grafo crea_grafo( );
    // ok
    void elimina_grafo( Grafo );

    // ok
    int empty_grafo( Grafo );
    // ok
    int empty_edge( Arco );

    // ok
    int numero_vertici( Grafo );
    // ok
    int numero_archi( Grafo );


    int grado( Grafo , Arco );
    int grado_uscente( Grafo , Arco );
    int grado_entrante( Grafo , Arco );

    // ok
    void dai_peso_arco( Arco , int );
    // ok
    void modifica_peso_arco( Arco );

    // ok?
    void stampa_grafo( Grafo );

    // ok?
    void add_arco( Grafo , int , Arco );
    // ok
    void verifica_presenza_arco( Grafo , int , int , int *);

    // ok
    void remove_arco( Grafo , int , int );

    void remove_nodo_logico( );

    Arco crea_nodo();
    void add_nodo( Grafo , int , int , char * );

    Grafo crea_grafo_da_grafo( Grafo , int , Grafo );


#endif // graf
