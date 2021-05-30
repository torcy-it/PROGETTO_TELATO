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
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
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

    //////////////////////////////////////////////////////////////////////////////////////////////////////// TERA non capisce perche liberare la memoria
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


// creazione di un nodo di un Heap minimo
min_heapnode* create_new_minHeapNode(int v, int dist)
{
    
    min_heapnode * minHeapNode = ( min_heapnode * ) malloc( sizeof( min_heapnode ) );

    // setto i key e la disanza:
    minHeapNode->v = v;
    minHeapNode->dist = dist;

    // ritorno il nodo
    return minHeapNode;
}

// creazione di un heap minimo
min_heap * create_minHeap( int capacity )
{
    // alloco la memoria della struttura     
    min_heap * minHeap = ( min_heap * ) malloc( sizeof( min_heap ) );
    
    // alloco memoria per l array pos di nodi ( interi ) di grandezza "capacity" 
    minHeap->pos = ( int * )malloc( capacity * sizeof( int ) );

    // setto le caratteristiche del heap
    minHeap->size = 0;
    minHeap->capacity = capacity;

    // alloco un puntatore a lista di nodi di heap dei grandezza "capacity"
    minHeap->array = ( min_heapnode**) malloc(capacity * sizeof( min_heapnode*));

    // ritorno l'heap appena creato e settato
    return minHeap;
}
 

// semplice swap per l'heap minimo
void swapMinHeapNode( min_heapnode** a,  min_heapnode** b)
{
    min_heapnode* t = *a;
    *a = *b;
    *b = t;
}
 


// heapify per un heap minimo 
// il vettore position è necessario per la funzione decreaseKey
void minHeapify( min_heap * minHeap, int idx )
{
    
    int smallest, left, right;

    smallest = idx;

    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    // se il figlio sinistro esiste ed è minore del piu piccolo nell'heap  
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist )
    {
        smallest = left;
    }
    
    // se il figlio destro esite ed  è minore del piu piccolo nell'heap  
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist )
    {
        smallest = right;
    }
    
    // se il piu piccolo è variato nelle righe sopra allora:
    if (smallest != idx)
    {
        
        // swap in minHeap
        min_heapnode *smallestNode = minHeap->array[smallest];
        min_heapnode *idxNode = minHeap->array[idx];
 
        
        // Swap in pos
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        
        // Swap dei nodi
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        // richiamo la funzione sul piu piccolo
        minHeapify(minHeap, smallest);
        
    }
}
 

int isEmpty( min_heap * minHeap)
{
    return minHeap->size == 0;
}
 

// funzione che estrae il minimo nodo dal heap
min_heapnode* extractMin( min_heap * minHeap )
{
    
    
    if ( isEmpty( minHeap ) )
    {
        return NULL;
    }
 
    
    // salvo in root il primo nodo
    min_heapnode* root = minHeap->array[0];
 
    
    // sostituisco il primo nodo con lultimo 
    min_heapnode* lastNode = minHeap->array[ minHeap->size - 1 ];
    minHeap->array[ 0 ] = lastNode;
 
    
    // aggiorno la pos dellultimo nodo 
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    
    // Riduco lheap size e chiamo heapify su root per aggiustare eventuali problemi 
    (minHeap->size)--;
    minHeapify(minHeap, 0);
 
    return root;
}
 

// Funzione per diminuire il valore dist di un dato vertice "punto_partenza"
// uso pos[] di min heap per ottenere l'indice corrente del nodo in minHeap
void decreaseKey(min_heap * minHeap, int punto_partenza, int distanza )
{
    
    // prendo lindice di pos nel punto "punto_partenza" che la prima volta dovrebbe essere davvero la parteza 
    // ( quindi lultimo nodo essendo un heap minimo )
    int i = minHeap->pos[ punto_partenza ];
 
    
    // aggiorno ilv alore di "dist" per quella posizione
    minHeap->array[i]->dist = distanza;
 
    // finche il valroe nella posizione "punto_partenza" è minore del valore di suo padre ( essendo un heap minimo ) 
    // finche i ha un padre
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
       
        // swap del nodo con il padre
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        
        // aggiorno lindice con il padre
        i = (i - 1) / 2;
    }
    
}
 

bool isInMinHeap(min_heap  *minHeap, int v)
{ 
    return ( minHeap->pos[v] < minHeap->size )? true : false ;  
}
 

// stampa l'array 
void printArr(int dist[], int n, int arrivo )
{
    
    // variabile di controllo
    bool puoi_andare = false;
    
    
    // da 0 alla grandezza dell'array 
    for (int i = 0; i < n; ++i)
    {
        
        ///////////////////7////////////////////////////////////////////////////////////////////// Tera non sa che fa 
        if( arrivo == i  &&  dist[ i ] != INT_MAX )
        {
            
            
            puoi_andare = true;
            printf("\n%d \t\t %d\n", i, dist[i]); 
            
        }
        
    }

    if( !puoi_andare )
    {
        printf("\nCon il carico che possiedi non e' possibile andarci al punto %d",arrivo);
    }
    
}
 
// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra( grafo gr, int punto_partenza , int arrivo , int peso_totale )
{
    int total_vertici = gr->numero_vertici ;// Get the number of vertices in graph

    int array_distanze [ total_vertici ];      // utilizzo array_distanze per prendere il il valore minimo tramite la f minheap
 
    // minHeap represents set E
    min_heap * minHeap = create_minHeap( total_vertici );
 
    // Initialize min heap with all vertices. dist value of all vertices 
    for (int indice = 0; indice < total_vertici ; ++indice )
    {
        array_distanze [indice] = INT_MAX; //variabile massima che puo' assumere un intero definita in limits.h

        minHeap->array[indice]  = create_new_minHeapNode(indice, array_distanze [indice]);

        minHeap->pos[indice]    = indice;
    }

    // Make array_distanze value of punto_partenza vertex as 0 so that it is extracted first
    minHeap->array[ punto_partenza ] = create_new_minHeapNode(punto_partenza , array_distanze [ punto_partenza ]);
    minHeap->pos[ punto_partenza ]   = punto_partenza;
    array_distanze[ punto_partenza ] = 0;

    decreaseKey( minHeap, punto_partenza, array_distanze[ punto_partenza ] );
 
    // Initially size of min heap is equal to total_vertici
    minHeap->size = total_vertici ;
 
    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while ( !isEmpty(minHeap) )
    {
        // Extract the vertex with minimum distance value
        min_heapnode* minHeapNode = extractMin( minHeap );
        int vertice_minimo = minHeapNode->v; // Store the extracted vertex number
 
        // Traverse through all adjacent vertices of vertice_minimo (the extracted
        // vertex) and update their distance values

        arco pCrawl = gr->adj[ vertice_minimo ];

        while ( pCrawl != NULL )
        {
            int val_vertice = pCrawl->key;
 
            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
            if (pCrawl->peso >= peso_totale && isInMinHeap(minHeap, val_vertice ) && array_distanze[ vertice_minimo ] != INT_MAX &&
                    pCrawl->lunghezza + array_distanze[ vertice_minimo ] < array_distanze[ val_vertice ])
            {
                array_distanze[ val_vertice ] = array_distanze[ vertice_minimo ] + pCrawl->lunghezza;
 
                // update distance value in min heap also
                decreaseKey(minHeap, val_vertice , array_distanze[ val_vertice ]);
            }

            pCrawl = pCrawl->next;
        }
    }
 
    // print the calculated shortest distances
    printArr( array_distanze , total_vertici , arrivo  );
}
