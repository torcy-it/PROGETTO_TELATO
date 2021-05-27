#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "hgrafi.h"

#define FIELD_SIZE 20
#define INIT 4


void create_graph( grafo gr, FILE * fp , int *vertici , bool errore )
{

    arco file_data =(arco ) malloc ( sizeof ( struct archi ));

    if(!fp) 
    {   
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
        return ;
    }

    fscanf (fp,"%d", &file_data->key );

    //devo aggiungere un vertice e poi successivamente arco

    //fine dati da file per il grafo
    if( feof(fp) || errore )
    {
        free( file_data );
        fclose( fp );
        return;
    }
    
    if( *vertici >= INIT )
    {
        //REALLOC MEMORY
        gr->adj = realloc( gr->adj, ( *vertici + 1) * sizeof( struct archi) );
    }


    gr->adj [ *vertici ] = add_archi( file_data, fp, &errore) ;

    *vertici = *vertici +1;
    
    free( file_data );


    create_graph( gr,  fp , vertici, errore );

}

arco add_archi( arco file_data , FILE * fp , bool * errore )
{

    arco nodo_t = (arco ) malloc( sizeof(struct archi ) ); //alloco memoria per il nodo


    if( file_data->key == -1 || feof( fp )) 
    {
        
        free ( nodo_t ); //libero il nodo allocato in precendenza 

        return NULL; // e ritorno null quindi lo stack si chiudera' dando come ultimo elemento un nodo a NULL
    }
    
    nodo_t->key = file_data->key;


    if ( (fscanf (fp,"%d %d",&file_data->peso, &file_data->lunghezza) != 2 ) && file_data->key != -1 )
    {
        printf("\n\n\tERRORE NON HAI SCRITTO BENE GRAFO SU FILE\n"
                "\tesempio : (valore nodo) (peso supportato ponte ) (lunghezza ponte) (-1) per concludere inserimento archi \n\n\t");

        system("pause");
        *errore = true;  

        return NULL;
    }

    nodo_t->peso = file_data->peso;
    nodo_t->lunghezza = file_data->lunghezza;

    fscanf ( fp,"%d",&file_data->key);
    
    // caso ricorsivo
    nodo_t->next = add_archi( file_data , fp, errore);

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

    printf(" %d__%d__%d ->  ", head->key, head->peso, head->lunghezza);

    print_archi ( head->next);
}

// A utility function to create a new Min Heap Node
min_heapnode* create_new_minHeapNode(int v, int dist)
{
    min_heapnode * minHeapNode = ( min_heapnode*) malloc(sizeof( min_heapnode));

    minHeapNode->v = v;
    minHeapNode->dist = dist;

    return minHeapNode;
}

// A utility function to create a Min Heap
min_heap * create_minHeap(int capacity)
{
    min_heap * minHeap = ( min_heap *) malloc(sizeof( min_heap ));

    minHeap->pos = (int *)malloc(capacity * sizeof(int));

    minHeap->size = 0;
    minHeap->capacity = capacity;

    minHeap->array = ( min_heapnode**) malloc(capacity * sizeof( min_heapnode*));

    return minHeap;
}
 
// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode( min_heapnode** a,  min_heapnode** b)
{
    min_heapnode* t = *a;
    *a = *b;
    *b = t;
}
 
// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()

void minHeapify( min_heap * minHeap, int idx)
{
    int smallest, left, right;

    smallest = idx;

    left = 2 * idx + 1;

    right = 2 * idx + 2;
 
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist )
        smallest = left;
 
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist )
        smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        min_heapnode *smallestNode = minHeap->array[smallest];

        min_heapnode *idxNode = minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A utility function to check if the given minHeap is ampty or not

int isEmpty( min_heap * minHeap)
{
    return minHeap->size == 0;
}
 
// Standard function to extract minimum node from heap

min_heapnode* extractMin( min_heap * minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    min_heapnode* root = minHeap->array[0];
 
    // Replace root node with last node
    min_heapnode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap

void decreaseKey(min_heap * minHeap, int punto_partenza, int distanza)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[ punto_partenza ];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = distanza;
 
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex
// 'v' is in min heap or not

bool isInMinHeap(min_heap  *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 
// A utility function used to print the solution
void printArr(int dist[], int n, int arrivo )
{
    bool puoi_andare = false;
    for (int i = 0; i < n; ++i)
    {
        if( arrivo == i && dist[i] != INT_MAX)
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