
int dijkstra(grafo gr,int source,int target)
{
    printf("\n");
    int total_vertici = gr->numero_vertici;

    int dist[total_vertici];

    int i = 0, j = 0;

    //non esaminato
    int prev [ total_vertici ] ;
    
    int selected [total_vertici];

    int m,min,start,d;

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

    int count = 0;

    while( selected[target] == 0)
    {
        min = INT_MAX;
        m = 0;

        arco pCrawl = gr->adj[start];


        while (pCrawl)
        {
            //printf("%d",pCrawl->key);

            d = dist[start] + pCrawl->lunghezza;


            //printf( " %d ", dist[i]);

            if(d < dist[pCrawl->key] && selected[pCrawl->key] == 0)
            {
                dist[pCrawl->key] = d;
                prev[pCrawl->key] = start;
            }
            if( min > dist[pCrawl->key] && selected[pCrawl->key] == 0)
            {
                min = dist[pCrawl->key];
                m = pCrawl->key;
            }

            pCrawl = pCrawl->next; 
            
            
            printf(" %d_%d_%d ", d, i, start);
            
        }

        printf("\n%d\n",m);
        count++;
        start = m;
        selected[start] = 1;

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

    printf("%s\n\n", path);

    system("pause");

    return dist[target];
}
