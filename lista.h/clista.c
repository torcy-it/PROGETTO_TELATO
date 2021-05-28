#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hlista.h"
#include "hour_function.h"

// PRELEVA MERCE
// Accetta in ingresso un puntatore aperto sul file stock_merce.txt in modalità "r"
// che usa per leggere le righe del file. Ogni riga comprende 3 stringhe e corrisponde a un prodotto.
lista * preleva_merce ( FILE * fp )
{
    // Alloca memoria per il nodo
    lista * nodo_t = (lista *) malloc(sizeof(lista));o

    // Se non legge 3 stringhe (è arrivato alla fine del file)
    if ( fscanf(fp,"%s %d %d",nodo_t->info_merce.alimento, &nodo_t->info_merce.colle, &nodo_t->info_merce.peso ) != 3 ) 
    {
        // Restituisci NULL
        return NULL;
    }
    
    // Restituisci il nodo 
    return nodo_t;    
}

// PRELEVA USER
// Accetta in ingresso un puntatore aperto sul file driver_registrati.txt in modalità "r"
// che usa per leggere le righe del file. Ogni riga comprende 4 stringhe e 2 interi e corrisponde a un driver registrato
lista * preleva_user ( FILE * fp )
{
    // Alloca memoria per il nodo
    lista * nodo_t = (lista *) malloc(sizeof(lista)); //alloco memoria per il nodo

    // Se non legge 4 stringhe e 2 interi (è arrivato alla fine del file)
    if ( fscanf(fp,"%s %s %s %s %d %d", nodo_t->info_user.targaID , nodo_t->info_user.password , nodo_t->info_user.name_user  , nodo_t->info_user.surname_user,
                 &nodo_t->info_user.peso_veicolo, &nodo_t->info_user.carico_veivolo) != 6 )
    {
        // Restituisci NULL
        return NULL;
    }

    // Restituisci il nodo
    return nodo_t;
}

// PRELEVA DATI DA FILE
// Accetta in ingresso un puntatore aperto su un file, che può essere o driver_registrati.txt
// o stock_merce.txt. Da quale dei due file prelevare i dati è determinato dal 2° parametro: scelta.
// Se scelta è false preleva un utente da driver_registrati.txt, mentre se è true preleva un prodotto da stock_merce.txt
lista * preleva_dati_da_file( FILE * fp , bool scelta )
{

    // Se il file non è stato aperto correttamente (controllo errore)
    if(!fp)
    {   
        // Stampa un messaggio che informi l'utente
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
        // Restituisci NULL
        return NULL;
    }

    // Dichiara un nodo
    lista * nodo_t;

    // Se scelta è false
    if( !scelta )
    {
        // Preleva un driver
        nodo_t = preleva_user ( fp );
    }
    // Altrimenti
    else 
    {
        // Preleva un prodotto
        nodo_t = preleva_merce ( fp );
    }


    // Caso base 
    if( !nodo_t ) 
    {
        // Chiudi il file
        fclose( fp );
        
        // Libera il nodo allocato in precedenza
        free ( nodo_t ); 

        // Restituisci NULL in modo che lo stack si chiuda dando come ultimo elemento un nodo a NULL
        return NULL;
    }
    
    // Passo ricorsivo
    nodo_t->next = preleva_dati_da_file(fp, scelta);

    // Restituisci il nodo
    return nodo_t;

}

// LOAD USER
// Accetta in ingresso: testa della lista utenti (che scorre tramite il passo ricorsivo) e un nodo utente
void load_user (  lista * head , lista * utente )
{
    // Caso base
    // Se la testa è NULL (siamo arrivati alla fine della lista)
    if ( !head )
    {
        // Setta un carico negativo per il veicolo
        utente->info_user.carico_veivolo = -84;
        // Ritorna
        return;
    }
    
    // Se targa e password del driver passato coincidono con quelli del nodo attuale (puntato da head)
    if( ! strcmp( head->info_user.targaID, utente->info_user.targaID ) && ! strcmp( head->info_user.password , utente->info_user.password ) )
    {
        // Copia nome e cognome dell'utente del nodo attuale nel nodo dell'utente passato
        strcpy ( utente->info_user.name_user ,head->info_user.name_user );
        strcpy ( utente->info_user.surname_user, head->info_user.surname_user );

        // Assegna il peso del veicolo dell'utente attuale al peso del veicolo dell'utente passato
        utente->info_user.peso_veicolo = head->info_user.peso_veicolo;
        // Annulla il carico del veicolo dell'utente passato
        utente->info_user.carico_veivolo = 0;

        // Metti in pausa
        system("pause");
        // Ritorna
        return;
    }

    // Passo ricorsivo
    // Passa al nodo successivo
    load_user ( head->next, utente );

}

// CHECK NODO ID
// Controlla che il driver o il prodotto identificato da id_tofind
// (la scelta tra i due è determinata dalla variabile bool) sia presente o meno.
// Restituisce true se presente, false altrimenti.
bool check_nodo_ID ( lista * head , const char * id_tofind , bool scelta )
{
    // Caso base
    // Se la lista è finita allora i nodi da controllare sono terminati, quindi il driver/prodotto non è presente
    if( !head )
    {
        // Restituisci false
        return false;
    }

    // Se scelta è false controlla il driver
    if( !scelta )
    {
        // Se c'è una corrispondenza
        if(!strcmp ( head->info_user.targaID, id_tofind  ))
        {
            // Restituisci true
            return true;
        }
                
    }
    // Altrimenti controlla il prodotto
    else
    {
        // Se c'è una corrispondenza
        if(!strcmp ( head->info_merce.alimento, id_tofind ) )
        {
            // Restituisci true
            return true;   
        }
    }

    // Passo ricorsivo
    // Passa al nodo successivo
    check_nodo_ID (head->next , id_tofind , scelta );
}

// CHECK NODO KEY
// Controlla le credenziali del driver
bool check_nodo_KEY ( lista * head , const char * targaID, const char * password )
{
    // Caso base
    // Se la lista è finita allora i nodi da controllare sono terminati, quindi le credenziali non hanno corrispondenza
    if( !head )
    {
        // Restituisci false
        return false;
    }
    // Se le credenziali passate hanno corrispondenza
    if( !strcmp ( head->info_user.targaID, targaID ) && !strcmp ( head->info_user.password, password) )
    {
        // Restituisci true
        return true; 
    }
    
    // Passo ricorsivo
    // Passa al nodo successivo
    check_nodo_KEY (head->next , targaID, password);
}

// ADD NODE
// Accetta 2 parametri: un puntatore alla testa della lista a cui aggiungere il nodo
// e il nodo da aggiungere chiamato info_new_user
lista * add_node ( lista * head, lista * info_new_user )
{
    // Caso base
    // Se la lista è terminata
    if( !head )
    {
        // Restituisci il nodo da aggiungere
        return info_new_user;
    }

    // Passo ricorsivo
    // Passa al nodo successivo assegnando a next il risultato di add node con i nuovi parametri
    head->next = add_node ( head->next , info_new_user );

    // Restituisci il puntatore alla testa della lista
    return head;
}

// AGGIORNA USER SU FILE
// Stampa sul file driver_registrati.txt una nuova riga corrispondente a un nuovo driver che si è registrato.
void aggiorna_user_su_file ( lista * head , FILE * fp )
{
    // Se il file non è stato aperto correttamente
    if(!fp)
    {   
        // Stampa un messaggio che informi l'utente
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
        // Ritorna
        return;
    }
    
    // Caso base
    // Se la lista è terminata
    if ( !head ) 
    {
        // Chiudi il file
        fclose ( fp );
        // Ritorna
        return;
    }

    // Stampa il contenuto del nodo passato (il nuovo driver) su file
    fprintf(fp,"\n%s %s %s %s %d %d", head->info_user.targaID, head->info_user.password , head->info_user.name_user  , 
                                    head->info_user.surname_user, head->info_user.peso_veicolo, head->info_user.carico_veivolo);

    // Passo ricorsivo
    // Passa al nodo successivo
    aggiorna_user_su_file(head-> next , fp );   
}

// PRINT LISTA MERCE
// Stampa il contenuto della lista contenente la merce in stock
void print_lista_merce ( lista * head )
{

    // Caso base
    // Se la lista è terminata
    if( !head )
    {
        // Ritorna
        return;
    }

    // Stampa il contenuto di un nodo
    printf("\n|%32s| %d %d", head->info_merce.alimento, head->info_merce.colle, head->info_merce.peso);

    // Passo ricorsico
    // Passa al nodo successivo
    print_lista_merce ( head->next);
}

// MOD NODO ADD
// Modifica il contenuto della lista merce in stock a seconda della quantità indicata nel parametro add (che indica l'aggiunta di merce).
// found è il parametro che indica se un certo prodotto è presente o meno
lista * mod_nodo_add ( lista * head , lista* add, bool found )
{
    // Se la lista non è finita e c'è corrispondenza con i nomi degli alimenti
    if(  head && !strcmp ( head->info_merce.alimento,add->info_merce.alimento ) && head )
    {
        // Aggiorna le quantità
        head->info_merce.colle  += add->info_merce.colle;
        // Imposta la variabile found a true per indicare che l'alimento è stato trovato
        found = true;
    }
    
    // Se la lista è finita
    if( !head )
    {
        // Se l'alimento è stato trovato
        if( found )
        {
            // Restituisci NULL
            return NULL;    
        }
        // Altrimenti
        else
        {
            // Restituisci il parametro add passato in ingresso
            return add;
        }
        
    }

    // Passa al nodo successivo
    head->next = mod_nodo_add (head->next , add , found);

    // Restituisci la testa della lista
    return head;
}

// MOD NODO DEL
// Modifica il contenuto della lista merce in stock a seconda della quantità indicata nel parametro del (che indica la rimozione di merce).
lista *  mod_nodo_del ( lista * head , lista * del )
{
    
    // Se la lista è finita
    if( !head )
    {
        // Ritorna NULL
        return NULL;
    }
    // Altrimenti
    else
    {
        // Chiamata ricorsiva passando al nodo successivo
        head->next = mod_nodo_del (head->next , del ) ;

        // Se i nomi degli alimenti indicati da head e del coincidono
        if( !strcmp ( head->info_merce.alimento, del->info_merce.alimento ) )
        {
            
            // Se la differenza tra i numeri dei colli dell'alimento di del e dell'alimento di head è 0
            if ( (del->info_merce.colle - head->info_merce.colle) == 0 )
            {
                // Crea un nodo temporaneo
                lista * tmp;
                // Assegna al nodo temporaneo appena dichiarato l'indirizzo del nodo successivo a head
                tmp = head->next;

                // Rendi disponibile lo spazio di memoria occupato da head
                free( head );

                // Restituisci il puntatore a nodo temporaneo
                return tmp;

            }
            
            // Altrimenti se il numero dei colli dell'alimento indicato da head è minore del numero dei colli dell'alimento indicato da del
            else if( head->info_merce.colle < del->info_merce.colle )
            {
                // Se la differenza tra il numero dei colli dell'alimento di del e di head è negativa
                if ( ( del->info_merce.colle - head->info_merce.colle ) < 0 )
                {
                    // Informa l'utente che non è possibile eseguire l'operazione
                    printf("\n\n\t\tNon e' possibile fare questa operazione perche' ( head->info_merce.colle - del->info_merce.colle ) < 0\n\n");
                }
                // Altrimenti
                else
                {
                    // Aggiorna il numero dei colli dell'alimento di head
                    head->info_merce.colle =  del->info_merce.colle - head->info_merce.colle;
        
                }
                
            }
            // Altrimenti
            else
            {
                // Se la differenza tra il numero dei colli dell'alimento head e quello di delè negativa
                if ( (  head->info_merce.colle - del->info_merce.colle  ) < 0 )
                {
                    // Informa l'utente che non è possibile eseguire l'operazione
                    printf("\n\n\t\tNon e' possibile fare questa operazione perche ( del->info_merce.colle - head->info_merce.colle ) < 0\n\n");
                }
                // Altrimenti
                else
                {
                    // Aggiorna il numero dei colli dell'alimento di head
                    head->info_merce.colle =  head->info_merce.colle - del->info_merce.colle;
                }
                
            }

        }
    }
    
    // Restituisci un puntatore alla testa
    return head;
}

// CREA NODO MERCE
lista * crea_nodo_merce ( lista * head )
{
    lista nodo;
    lista * nodo_toLink = (lista * )malloc ( sizeof ( lista ));

    do
    {
        printf("\n\n\tInserisci alimento presente in lista merce\n>");
        scanf("%s",nodo.info_merce.alimento);
        to_upper( nodo.info_merce.alimento);

    } while ( !check_nodo_ID ( head , nodo.info_merce.alimento, true )  || !strcmp (nodo.info_merce.alimento,"back" ));


    do
    {
        printf("\n\n\tInserisci la quantita desiderata \n>");
        nodo.info_merce.colle = insert_int ();

        if( nodo.info_merce.colle > 0 )
        {
            if ( check_quantita_merce ( head, &nodo ) )
            {
                break;
            }
        }

    }while ( 1 ); 

    strcpy (nodo_toLink->info_merce.alimento, nodo.info_merce.alimento);

    nodo_toLink->info_merce.colle = nodo.info_merce.colle;

    nodo_toLink->info_merce.peso = nodo.info_merce.peso;

    nodo_toLink->next = NULL;

    return nodo_toLink;
    
}

bool check_quantita_merce ( lista * head, lista * nodo_to_check )
{
    if( !head )         //caso base dove head e' NULL e ritorno false perche' non ho trovato nessuna corrispondenza
    {
        return false;
    }
   

    if(!strcmp ( head->info_merce.alimento, nodo_to_check->info_merce.alimento ) 
                && nodo_to_check->info_merce.colle > 0 && nodo_to_check->info_merce.colle <= head->info_merce.colle ) // ho trovato una corrispondenza ritorno true
    {
        nodo_to_check->info_merce.peso = head->info_merce.peso;
        return true;          
    }

    check_quantita_merce (head->next , nodo_to_check); // caso ricorsivo dove scorro head
}

void deallocate_list ( lista * head )
{
    if ( !head )
    {
        return;
    }
        
    deallocate_list(head->next); 

    free(head);
}

int somma_elementi_lista ( lista * testa )
{

    if ( testa != NULL )
        return ((testa->info_merce.peso * testa->info_merce.colle ) + somma_elementi_lista(testa->next));
    else
        return 0;

}
