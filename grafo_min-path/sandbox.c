#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define FIELD_SIZE 20
#define INIT 4

    // Structure to represent a min heap node
    struct MinHeapNode
    {
        int  v;
        int dist;
    };
    
    // Structure to represent a min heap
    struct MinHeap
    {
        int size;      // Number of heap nodes present currently
        int capacity;  // Capacity of min heap
        int *pos;     // This is needed for decreaseKey()
        struct MinHeapNode **array;
    };
  
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


struct MinHeap* createMinHeap(int );
struct MinHeapNode* newMinHeapNode(int , int );
void swapMinHeapNode(struct MinHeapNode** , struct MinHeapNode** );
void minHeapify(struct MinHeap* , int );
int isEmpty(struct MinHeap* );
struct MinHeapNode* extractMin(struct MinHeap* );
void decreaseKey(struct MinHeap* , int , int );
bool isInMinHeap(struct MinHeap *, int );
void printArr(int [], int );
void dijkstra( grafo  , int );



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
    

    create_graph( gr, fopen("pocordio.txt","r"), &num_vertici);

    gr->numero_vertici = num_vertici ;

    gr != NULL ? stampa_grafo ( gr, 0 ) : printf("\n\n\tGrafo Vuoto\n")  ;

    gr != NULL ? dijkstra( gr, 0 ) : printf("\n\n\tGrafo Vuoto\n");

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


// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()

void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A utility function to check if the given minHeap is ampty or not

int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
// Standard function to extract minimum node from heap

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
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

void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
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

bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 
// A utility function used to print the solution
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra( grafo gr, int src)
{
    int V = gr->numero_vertici ;// Get the number of vertices in graph

    int dist[V];      // dist values used to pick minimum weight edge in cut
 
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
 
    // Initialize min heap with all vertices. dist value of all vertices 
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    // Initially size of min heap is equal to V
    minHeap->size = V;
 
    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number
 
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        arco pCrawl = gr->adj[u];
        while (pCrawl != NULL)
        {
            int v = pCrawl->key;
 
            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 
                                          pCrawl->peso + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->peso;
 
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
    // print the calculated shortest distances
    printArr(dist, V);
}


/*
// DFS algo
void DFS(struct Graph* graph, int vertex) {
  struct node* adjList = graph->adjLists[vertex];
  struct node* temp = adjList;

  graph->visited[vertex] = 1;
  printf("Visited %d \n", vertex);

  while (temp != NULL) {
    int connectedVertex = temp->vertex;

    if (graph->visited[connectedVertex] == 0) {
      DFS(graph, connectedVertex);
    }
    temp = temp->next;
  }
}

// Create a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create graph
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  graph->visited = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {
  // Add edge from src to dest
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  // Add edge from dest to src
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}


//////////////////////////////////////////////////////////////////// dijskra adiancency matrix

#include<stdio.h>
#include<conio.h>
#define INFINITY 9999
#define MAX 10
 
void dijkstra(int G[MAX][MAX],int n,int startnode);
 
int main()
{
	int G[MAX][MAX],i,j,n,u;
	printf("Enter no. of vertices:");
	scanf("%d",&n);
	printf("\nEnter the adjacency matrix:\n");
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);
	
	printf("\nEnter the starting node:");
	scanf("%d",&u);
	dijkstra(G,n,u);
	
	return 0;
}
 
void dijkstra(int G[MAX][MAX],int n,int startnode)
{
 
	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];
	
	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	
	while(count<n-1)
	{
		mindistance=INFINITY;
		
		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			
			//check if a better path exists through nextnode			
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
 
	//print the path and distance of each node
	for(i=0;i<n;i++)
		if(i!=startnode)
		{
			printf("\nDistance of node%d=%d",i,distance[i]);
			printf("\nPath=%d",i);
			
			j=i;
			do
			{
				j=pred[j];
				printf("<-%d",j);
			}while(j!=startnode);
	}
}
*/