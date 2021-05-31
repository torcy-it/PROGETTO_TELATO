#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "hgrafi.h"

#define INIT 4

// funzione ricorsiva:
void create_graph( grafo * gr, FILE * fp , int *vertici , bool errore )
{
    
    // creo spazio per un arco dove storare i dati di un arco presi da un file
    arco * file_data = ( arco * ) malloc ( sizeof ( arco ) );

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
        gr->adj = realloc( gr->adj, ( *vertici + 1) * sizeof( arco ) );
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

arco * add_archi( arco * file_data , FILE * fp , bool * errore )
{

    //alloco memoria per il nodo
    arco * nodo_t = ( arco * ) malloc( sizeof( arco ) ); 

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



int numero_vertici( grafo * gr )
{
    return gr->numero_vertici;
}


// stampa lista d'adiacenza del grafo per il vertice: "indice" 
// per stampare l'intero grafo dovrebbe esser passato come valore di "indice": 0 
void stampa_grafo( grafo * gr, int indice )
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


int is_empty(grafo * gr) 
{ 
    return ( gr == NULL )? 1 : 0;
}

// stampa archi: finche il nodo non è NULL stmapa i sui dati: key - peso - lunghezza 
void print_archi ( arco * head )
{
    
    if( !head ) return;

    printf(" ( %d - %d - %d ) -> ", head->key, head->peso, head->lunghezza);

    print_archi ( head->next);
}


// Algoritmo di dijsktra, un algoritmo che ti calcola il min path dalla source al target
// andando a sommare gli archi dei nodi che va a studiare
void dijkstra(grafo * gr,int source,int target , int peso_veicolo)
{
    printf("\n");
    
    // asseggno  alla variabile total_vertici il totale dei vertici del grafo
    int total_vertici = gr->numero_vertici ;
    
    // dichiaro un vettore dist dove andro' a salvare le distanze di tutti i nodi della source
    int dist [ total_vertici ];
    
    // dichiarazione variabili
    int min_path, start_index, distance;       // minimo per aggiornare il percorso con meno archi, start -> source e la distanza per secondo ciclo while
    int i = 0, j = 0;                        //indici   
    int loop = 0;                           // varibile loop per uscire da un ipotetico pozzo ( spiegato a riga 223 )
    int index_min_path = 0;                 // variabile per aggiornare l'index con il min path

    // vettore prev per salvarmi il path degli indici con dist minore
    int prev_index [ total_vertici ] ;
    
    // vettore utilizzato per capire gli indici toccati
    int selected [ total_vertici ];
    
    // vettore path per stampare il percorso migliore
    char path [ total_vertici ];


    for( i= 0 ; i< total_vertici ; i++ )
    {
        selected [ i ] = 0;             // inizializzo selected a 0 o false as u prefer
        dist[i] = INT_MAX;              // inizializzo dist ad il piu grande valore che puo' assumere un int
        prev_index[i] = -1;                   // inizializzo il prev a -1 ( spiegato successivamente a riga 306 )
    }

    
    // inizializzo la variabile start con la source
    start_index = source;
    
    // e successivamente imposto l'indice del nodo da esamire a 1 cosi che sia gia controllato
    selected [ start_index ] = 1;
    
    // ovviamente la distanza del vertice A ad un ipotetico A e' sempre uguale a 0 quindi lo inizializzo a tale distanza
    dist [ start_index ] = 0;

    // ciclo finche' non ho esaminato tutti i vertici
    while( selected [ target ] == 0)
    {

        // inizializzo min_path ad una variabile alta affinchè faccia i dovuti controlli nel ciclo while annidato
        min_path = INT_MAX; 


        // ciclo creato affinche' riesca ad uscire da un pozzo 
        // se loop cioe' i tentativi di cercare un indice superano i totali vertici allora ti trovi in un pozzo
        if ( loop > total_vertici + 2  ) 
        {
            // scorro selected finche' non trovo un indice che non ho studiato
            for( int i = 0; i < total_vertici; i++)
            {
                // se l'indice non e' stato studiato 
                if( selected[i] != 1 )
                {
                    start_index = i;    // aggiorno start index con l'indice non studiato
                    loop = 0;           // e riemposto loop a zero per un eventuale secondo pozzo
                }
            }
        }

        arco * adj_list = gr->adj[ start_index ];

        while ( adj_list )
        {

            // aggorno la variabile distance con la distanza di dist del'indice che sto esaminando e la lunghezza dell'arco che sto esaminando
            distance = dist[ start_index ] + adj_list->lunghezza;

            // DEBUG THING
            //printf("%d",adj_list->key);
            //printf(" ++%d_%d_%d++ ", distance, start,adj_list->key);
            //printf( " %d ", dist[i]);

            // !primo controllo! ( if peso veicolo riesce a passare sul ponte ) go ahead ( if la distance aggiornata precedentemente e' minore del vet dist[indice del nodo della adj list])
            // go ahead ( if vet selected [ indice del nodo della adj list] non e' stato studiato ) go ahead nel 'if
            if( peso_veicolo <= adj_list->peso && distance < dist [ adj_list->key ] && selected [ adj_list->key ] == 0)
            {
                dist [ adj_list->key ] = distance;      // aggiorno dist[indice del nodo della adj list] con la distanza calcolata precedentemente
                prev_index [ adj_list->key ] = start_index;   // aggiorno vet prev [indice del nodo della adj list] con l'indice con il min percorso esaminato

                // DEBUG THING
                //printf(" ? ");
            }

            // !secondo controllo! ( if min path e' maggiore della dist[ indice del nodo della adj list ] cosa che accade ad ogni primo ciclo) go ahed 
            // ( if  if vet selected [ indice del nodo della adj list] non e' stato studiato ) go ahead nel 'if
            if( min_path > dist [ adj_list->key ] && selected [ adj_list->key ] == 0)
            {
                min_path = dist [ adj_list->key ];      // aggiorno min_path con la variabile distanza presente in dist [ adj_list->key ]
                index_min_path = adj_list->key;         // aggiorno a sua volta anche l'indice 

                // DEBUG THING
                //printf(" ! ");
            }


            // DEBUG THING
            //printf(" %d_%d_%d --> ", distance, start,adj_list->key);
            /*
                for( i= 0 ; i< total_vertici ; i++ )
                {
                    printf("%d",selected[i]);
                }
            */


            adj_list = adj_list->next; 
            
        }

        // DEBUG THING
        //printf("\n%d\n",key_small_island);


        // aggiorno l'array selected del vertice appena esaminato 
        start_index = index_min_path;
        selected [ start_index ] = 1;

        // incremento loop
        loop++;

    }
    // dijsktra completato

    // procedo alla stampa del percorso
    start_index = target;               // inizializzo start index con il target 
    j = 0;                              // inizializzo j ovviamente hahaha



    // utilizzo la variabile -1 come se fosse il carattere di terminazione della stringa
    // non ho utilizzato '\0' perchè se no mi avrebbe ciclato anche i valori con -1 enon andava bene
    // perchè ho inizializzato un vet di dim tot_vertici e quindi se il percorso fosse stato di dim 1
    // allora mi avrebbe ciclato tot_vertici-1 di valori che non mi servivano 
    while( start_index != -1)
    {
        path[j++] = start_index +65;            //utilizzo l'aritmetica ascii per decifrare i valori int ad char ( if start index = 0 -> +65 = 65 -> ascii 65 = 'A' )
        start_index = prev_index [ start_index ];     // aggiorno start index conm il prossimo valore presente in prev
    }

    path[j]='\0'; // inserisco il carattere separatore a fine stringa

    strrev(path); // utilizzo la funzione reverse stringa presente in string.h

    // simulo un procedimento di ricerca del miglior path 
    printf("\n\t");
    printf(" %c ",path[0]);

    for( j = 1, i = 1; path[j] != 0 ; i++ )
    {
    
        sleep( 1 );

        printf( " - " );

        if( i%3 == 0 )
        {
            printf(" %c ",path[j++]);
        }
    }

    printf("\n\tIl percorso piu' breve e' %s con %d ponti attraversati.\n\t", path,dist[target]);

}