#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "hgrafi.h"

#define FIELD_SIZE 20
#define INIT 4

// funzione ricorsiva:
void create_graph( grafo gr, FILE * fp , int *vertici , bool errore )
{
    
    // creo spazio per un arco dove storare i dati di un arco presi da un file
    arco file_data = ( arco ) malloc ( sizeof ( struct archi ) );

    // se il file != null continua
    if( !fp ) 
    {   
        printf("\nErrore scrittura per mappa grafo\n"); 
        return ;
    }
    
    // prendo il primo valore dal file
    fscanf ( fp, "%d" , &file_data->key );
    
    // se siamo alla fine del file o c'è un errore
    // chiudi il file e libera lultimo nodo ( appena ) allocato
    if( feof(fp) || errore )
    {
        free( file_data );
        fclose( fp );
        return;
    }
    
    
    // se il parametro passato in ingresso "*vertici" è maggiore dell' attuale numero di vertici del grafo
    // aggiorna la memoria
    if( *vertici >= INIT )
    {
        //REALLOC MEMORY
        gr->adj = realloc( gr->adj, ( *vertici + 1) * sizeof( struct archi) );
    }

    
    // aggiungo archi al nodo gr->adj[vertici] primo ciclo = 0
    //e passo una viariabile booleana errore impostata inizialmente a false e il nodo appena creato "file_data"
    gr->adj [ *vertici ] = add_archi( file_data, fp, &errore) ;

    // libero la variabile per il prossimo utilizzo 
    free( file_data );
    
    
    // incremente vertici
    *vertici = *vertici +1;
    
    
    // chiamata ricorsiva 
    create_graph( gr,  fp , vertici, errore );

}

arco add_archi( arco file_data , FILE * fp , bool * errore )
{

    //alloco memoria per il nodo
    arco nodo_t = ( arco ) malloc( sizeof( struct archi ) ); 

    // se si è arrivati alla fine del file o si sta analizzando il denominatore della fine di una lista di adiacenza fine constrassegnata con -1 come valore simbolico )
    // si libera il nodo "nodo_t" e si ritorna NULL
    if( file_data->key == -1 || feof( fp ) ) 
    {
     
        free ( nodo_t ); //libero il nodo allocato in precendenza 

        return NULL; // e ritorno null quindi lo stack si chiudera' dando come ultimo elemento un nodo a NULL
        
    }
   
    
    // condizione per capire se nel file mappa_island.txt sono stati scritti bene i valori dei nodi con peso e distanza
    // se sopraggiunge un errore, aggiorno la variabile booleana errore a true e ritorno null
    // la variabile errore serve per fa capire alla funzione che ha chiamato add_archi che si tratta di un errore di scrittura
    // e non di fine lettura riga
    if ( (fscanf (fp,"%d %d",&file_data->peso, &file_data->lunghezza) != 2 ) && file_data->key != -1 )
    {
        
        printf("\n\n\tERRORE NON HAI SCRITTO BENE GRAFO SU FILE\n"
                "\tesempio : (valore nodo) (peso supportato ponte ) (lunghezza ponte) (-1) per concludere inserimento archi \n\n\t");
        
        free( nodo_t );
        
        system("pause");
        
        *errore = true;  

        return NULL;
    }

    // assegnazioni su nodo_t dopo tutti i controlli
    nodo_t->key = file_data->key;
    
    nodo_t->peso = file_data->peso;
    
    nodo_t->lunghezza = file_data->lunghezza;

    // passo induttivo: cerco un nuovo valore da file e richiamo la funzione ricorsivamente 
    fscanf ( fp,"%d",&file_data->key);
    
    nodo_t->next = add_archi( file_data , fp, errore);

    
    // alla fine dei casi ricorsivi ritorno la testa della lista di adiacenze per questo determinato vertice del grafo
    return nodo_t;

}


//funzione che mi ritorna i vertici del grafo
int numero_vertici( grafo gr )
{
    return gr->numero_vertici;
}


// stampa lista d'adiacenza del grafo per il vertice: "indice" 
// per stampare l'intero grafo dovrebbe esser passato come valore di "indice": 0 
void stampa_grafo( grafo gr, int indice )
{

    // se il veritce semplicemente è piu grande della grandezza del grafo
    // altrimenti stampa la lista d'adiacenza
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

    // passo induttivo: chiamta ricorsiva, aggiorno l'indice  
    stampa_grafo (gr , indice + 1);
}

// funzione che mi avverte se il grafo e' vuoto
int is_empty(grafo gr) 
{ 
    return ( gr == NULL )? 1 : 0;
}

// stampa archi: finche il nodo non è NULL stmapa i sui dati: key - peso - lunghezza 
void print_archi ( arco head )
{
    
    if( !head ) return;

    printf(" ( %d - %d - %d ) -> ", head->key, head->peso, head->lunghezza);

    print_archi ( head->next);
}


// Algoritmo di dijsktra, un algoritmo che ti calcola il min path dalla source al target
// andando a sommare gli archi dei nodi che va a studiare
void dijkstra(grafo gr,int source,int target , int peso_veicolo)
{
    printf("\n");
    
    // asseggno  alla variabile total_vertici il totale dei vertici del grafo
    int total_vertici = gr->numero_vertici ;
    
    // dichiaro un vettore dist dove andro' a salvare le distanze di tutti i nodi della source
    int dist [ total_vertici ];
    
    // dichiarazione variabili
    int min_path, start_index, distance;   // minimo per aggiornare il percorso con meno archi, start -> source e la distanza per secondo ciclo while
    int i = 0, j = 0;           //indici

    // vettore prev per salvarmi il path degli indici con dist minore
    int prev [ total_vertici ] ;
    
    // vettore utilizzato per capire gli indici toccati
    int selected [ total_vertici ];
    
    // vettore path per stampare il percorso migliore
    char path [ total_vertici ];


    for( i= 0 ; i< total_vertici ; i++ )
    {
        selected [ i ] = 0;             // inizializzo selected a 0 o false as u prefer
        dist[i] = INT_MAX;              // inizializzo dist ad il piu grande valore che puo' assumere un int
        prev[i] = -1;                   // inizializzo il prev a -1 ( spiegato successivamente a riga 282 )
    }

    
    // inizializzo la variabile start con la source
    start_index = source;
    
    // e successivamente imposto l'indice del nodo da esamire a 1 cosi che sia gia controllato
    selected [ start_index ] = 1;
    
    // ovviamente la distanza del vertice A ad un ipotetico A e' sempre uguale a 0 quindi lo inizializzo a tale distanza
    dist [ start_index ] = 0;
    
    // varibile loop per uscire da un ipotetico pozzo ( spiegato a riga 223 )
    int loop = 0;
    
    
    int index_min_path = 0;


    while( selected [ target ] == 0)
    {
        min_path = INT_MAX;

        if ( loop > total_vertici + 2 ) 
        {
            for( int i = 0; i < total_vertici; i++)
            {
                if( selected[i] != 1 )
                {
                    start = i;
                    loop = 0;
                }
                    

            }
        }

        arco pCrawl = gr->adj[ start_index ];

        while ( pCrawl )
        {
            //printf("%d",pCrawl->key);

            distance = dist[ start_index ] + pCrawl->lunghezza;

            //printf(" ++%d_%d_%d++ ", distance, start,pCrawl->key);
            //printf( " %d ", dist[i]);

            if( peso_veicolo <= pCrawl->peso && distance < dist [ pCrawl->key ] && selected [ pCrawl->key ] == 0)
            {
                dist [ pCrawl->key ] = distance;
                prev [ pCrawl->key ] = start_index;
                //printf(" ? ");
            }

            if( min_path > dist [ pCrawl->key ] && selected [ pCrawl->key ] == 0)
            {
                min_path = dist [ pCrawl->key ];
                index_min_path = pCrawl->key;
                //printf(" ! ");
            }

            //printf(" %d_%d_%d --> ", distance, start,pCrawl->key);
            pCrawl = pCrawl->next; 
            
            /*
                for( i= 0 ; i< total_vertici ; i++ )
                {
                    printf("%d",selected[i]);
                }
            */
            
            
        }

        //printf("\n%d\n",key_small_island);

        start_index = index_min_path;
        selected [ start_index ] = 1;

        loop++;

    }

    start_index = target;
    j = 0;

    while(start != -1)
    {
        path[j++] = start+65;
        start = prev[ start_index ];
    }

    path[j]='\0';

    strrev(path);

    printf("\n\t");
    printf(" %c ",path[0]);

    for( j = 1, i = 0; path[j] != 0 ; i++ )
    {
    
        sleep( 1 );

        printf( " - " );

        if( i%3 == 0 )
        {
            printf(" %c ",path[j]);

            j++;
        }
    }

    printf("\n\tIl percorso piu' breve e' %s con %d ponti attraversati.\n\t", path,dist[target]);

    //system("pause");

}
