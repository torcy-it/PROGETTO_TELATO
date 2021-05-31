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

    
    // devo aggiungere un vertice e poi successivamente arco

    
    // se siamo alla fine del file o c'è un errore
    // chiudi il file e librea lultimo nodo ( appena ) allocato
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

    
    // aggiungo un arco tra il vertice del grafo "*vertici" e il nodo appena creato "file_data"
    gr->adj [ *vertici ] = add_archi( file_data, fp, &errore) ;

    // libero la variabile per il prossimo utilizzo 
    free( file_data );
    
    
    // aggiorno il puntatore del vertice 
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
   
    
    // se la funione fscanf non prende corretamente due numeri  e  il "nodo_t"->key contiene il valore di denominazione fine lista di adiacenza per un certo campo 
    // libero il nodo "nodo_t" metto il sistema in pausa, setto la variabile d'erroer true e ritono NULL 
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

void dijkstra(grafo gr,int source,int target , int peso_veicolo)
{
    printf("\n");
    int total_vertici = gr->numero_vertici ;

    //printf("\n%d\n",total_vertici);

    int dist[total_vertici];

    int i = 0, j = 0;

    //non esaminato
    int prev [ total_vertici ] ;
    
    int selected [total_vertici];

    int min, start, distance;

    char path[total_vertici];
    //-------------

    for( i= 0 ; i< total_vertici ; i++ )
    {
        selected [ i ] = 0;
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    
    start = source;
    selected[start] = 1;

    dist[start] = 0;
    
    int loop = 0;

    int key_small_island = 0;


    while( selected[target] == 0)
    {
        min = INT_MAX;

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

        arco pCrawl = gr->adj[start];

        while (pCrawl)
        {
            //printf("%d",pCrawl->key);

            distance = dist[start] + pCrawl->lunghezza;

            //printf(" ++%d_%d_%d++ ", distance, start,pCrawl->key);
            //printf( " %d ", dist[i]);

            if( peso_veicolo <= pCrawl->peso && distance < dist[pCrawl->key] && selected[pCrawl->key] == 0)
            {
                dist[pCrawl->key] = distance;
                prev[pCrawl->key] = start;
                //printf(" ? ");
            }

            if( min > dist[pCrawl->key] && selected[pCrawl->key] == 0)
            {
                min = dist[pCrawl->key];
                key_small_island = pCrawl->key;
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

        start = key_small_island;
        selected[start] = 1;

        loop++;

    }

    start = target;
    j = 0;

    while(start != -1)
    {
        path[j++] = start+65;
        start = prev[start];
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