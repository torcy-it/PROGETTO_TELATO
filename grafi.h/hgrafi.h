#ifndef HGRAF_H
#define HGRAF_H



    // Structure to represent a min heap node
    typedef struct HeapNode
    {
        int  v;
        int dist;

    }min_heapnode;
    
    // Structure to represent a min heap
    typedef struct Heap
    {
        int size;      // Number of heap nodes present currently
        int capacity;  // Capacity of min heap
        int *pos;     // This is needed for decreaseKey()
        struct HeapNode **array;
    }min_heap;
  
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


    min_heap* create_minHeap(int );

    min_heapnode* create_new_minHeapNode(int , int );

    void swapMinHeapNode( min_heapnode** ,  min_heapnode** );

    void minHeapify( min_heap* , int );

    int isEmpty( min_heap* );

    min_heapnode* extractMin( min_heap* );

    void decreaseKey( min_heap* , int , int );

    bool isInMinHeap( min_heap *, int );

    void printArr(int [], int , int  );

    void dijkstra( grafo  , int, int , int );




    void print_archi ( arco  );

    void stampa_grafo( grafo , int );

    int is_empty( grafo ); 

    void create_graph( grafo , FILE * , int *, bool );

    arco add_archi( arco , FILE * , bool * );

    int numero_vertici( grafo  );


#endif