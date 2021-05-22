#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define INIT 4

    struct archi
    {
        int key;
        int peso; // settare ad 1
        
        struct archi *next;
    };
    typedef struct archi * arco;

    struct graph
    {
        int numero_vertici; /* numero di vertici del grafo */
        struct archi **adj; /* vettore con le liste delle adiacenze */
    };
    typedef struct graph * grafo;




    void print_archi ( arco  );

    void stampa_grafo( grafo , int );

    int is_empty( grafo ); 

    void create_graph( grafo , FILE * , int *);

    arco add_archi( int , FILE *  );

    int numero_vertici( grafo  );


int main(void) 
{

    grafo gr = NULL;       //grafo inizializzato a NULL

    int num_vertici = 0;

    gr  = (grafo  )malloc(sizeof( struct graph ));

    if(gr == NULL) 
    {
        printf("ERRORE: imp. allocare mem. del grafo\n");
        exit(1);
    }

    gr->adj = ( arco *)malloc( INIT * sizeof ( arco ));

    if(gr->adj == NULL)  
    {
        printf("ERRORE: imp. allocare mem. per la lista del grafo\n");
        exit (1);
    } 
    

    create_graph( gr, fopen("file_citta_island.txt","r"), &num_vertici);

    gr->numero_vertici = num_vertici ;

    gr == NULL ? printf("\n\n\tGrafo Vuoto\n") : stampa_grafo ( gr, 0 );

    return 0;
}


void create_graph( grafo gr, FILE * fp , int *vertici)
{
    if(!fp) 
    {   
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
        return ;
    }

    int val = 0;

    fscanf (fp,"%d",&val);

    //devo aggiungere un vertice e poi successivamente arco

    //fine dati da file per il grafoS
    if( feof(fp) )
    {
        fclose( fp );
        return;
    }
    
    if( *vertici >= INIT )
    {
        //REALLOC MEMORY
        gr->adj = realloc( gr->adj, ( *vertici + 1) * sizeof( struct archi) );
    }

    gr->adj [ *vertici ] = add_archi(val, fp) ;

    *vertici = *vertici +1;
    

    create_graph( gr,  fp , vertici);

}

arco add_archi( int val, FILE * fp )
{

    if(!fp) //eseguo un controllo per vedere se il file e' stato aperto correttamente
    {   
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
        return NULL;
    }

    arco nodo_t = (arco ) malloc(sizeof(struct archi )); //alloco memoria per il nodo

    if( val == -1 || feof( fp )) 
    {
        
        free ( nodo_t ); //libero il nodo allocato in precendenza 

        return NULL; // e ritorno null quindi lo stack si chiudera' dando come ultimo elemento un nodo a NULL
    }
    
    nodo_t->key = val;
    nodo_t->peso = 1;

    fscanf (fp,"%d",&val);
    
    // caso ricorsivo
    nodo_t->next = add_archi(val, fp);

    return nodo_t;

}

int numero_vertici( grafo gr )
{
    return gr->numero_vertici;
}


void stampa_grafo( grafo gr, int indice )
{

    if( indice >= gr->numero_vertici )
    {
        return ;
    }
    else
    {
        printf("\nnodi adiacenti al nodo %d -> ", indice );

        print_archi ( gr->adj [ indice ] );
        
        printf("NULL\n");
        
    }

    stampa_grafo (gr , indice + 1);
}


int is_empty(grafo gr) 
{ 
    return ( gr == NULL )? 1 : 0;
}


void print_archi ( arco head )
{

    if( !head ) return;

    printf("%d_%d ->  ", head->key, head->peso);

    print_archi ( head->next);
}