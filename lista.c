#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "attivita_studio.h" 
#include "lista.h"

// Definizione della struttura node
struct node 
{
    attivita_studio value;
    struct node *next;
};

// Definizione della funzione newList per creare una nuova lista vuota
list newList(void)
{
    return NULL; // Restituisce NULL, indicando una lista vuota
}

// Funzione per verificare se la lista e' vuota
bool emptyList(list l)
{
    return l == NULL; // Restituisce 1 se la lista e' vuota (NULL), altrimenti restituisce 0
}

// Funzione per aggiungere un nuovo elemento in testa alla lista
list consList(attivita_studio val, list l)
{
    struct node *nuovo; // Dichiarazione di un puntatore a un nuovo nodo
    nuovo =(struct node *) malloc(sizeof(struct node)); // Allocazione della memoria per il nuovo nodo
    	if (nuovo == NULL)  // Verifica se l'allocazione della memoria e' riuscita
	{ 
		printf("Errore allocazione di memoria \n");
	    	exit (1);
        }
   	else //Copia dei campi dell'attivita'  nella nuova struttura nodo(nuovo) tramite strdup per allocare nuova memoria e copiare il contenuto delle stringhe in modo che ogni nodo abbia i propri dati indipendenti
   	{
	    nuovo->value.descrizione = strdup(val.descrizione);
	    nuovo->value.corso = strdup(val.corso);
	    nuovo->value.data_scadenza = strdup(val.data_scadenza);
	    nuovo->value.data_inizio = strdup(val.data_inizio);
	    nuovo->value.priorita = strdup(val.priorita);
	    
	    //Copia diretta dei campi di tipo intero
	    nuovo->value.tempo_stimato = val.tempo_stimato;
	    nuovo->value.completamento = val.completamento;
	    
	    //Inserimento in testa alla lista
	    nuovo->next=l;
	    l=nuovo;
    	}
	
    return l; // Restituisce il puntatore alla lista aggiornata
}

//Stampa la lista delle attivita' a schermo
void outputList(list l)
{
    int i=1;
	
	while (l != NULL) 
	{
	        printf("ATTIVITA' NUMERO %d \n",i++);
		printf("Descrizione: %s \n", l->value.descrizione);
	        printf("Corso: %s \n", l->value.corso);
	        printf("Data di inizio: %s \n", l->value.data_inizio);
	        printf("Data di scadenza: %s \n", l->value.data_scadenza);
	        printf("Tempo stimato: %d ore \n", l->value.tempo_stimato);
	        printf("Completamento: %d%% \n", l->value.completamento);
	        printf("Priorita': %s \n", l->value.priorita);
	        printf("\n");
	        l = l->next; // Passa al nodo successivo
        }
}

//Scrive la lista sul file
int output_file(list l,FILE *ptr)
{
    int i=0;
    ptr=fopen(file_registro, "w");
    if(ptr==NULL)
    {
    	printf("Errore apertura file \n");
    	return 0;
    }
    else
    {
	while (l != NULL) 
	{
		fprintf(ptr,"%d \n",++i);
		fprintf(ptr,"%s \n", l->value.descrizione);
		fprintf(ptr,"%s \n", l->value.corso);
		fprintf(ptr,"%s \n", l->value.data_inizio);
		fprintf(ptr,"%s \n", l->value.data_scadenza);
		fprintf(ptr,"%d ore \n", l->value.tempo_stimato);
		fprintf(ptr,"%d%% \n", l->value.completamento);
		fprintf(ptr,"%s \n", l->value.priorita);
		fprintf(ptr,"\n");
		l = l->next; // Passa al nodo successivo
	}
	    	fclose(ptr);
    }
	return i;
}

//Modifica il completamento di una specifica attivita' 
void modifica_lista(list l)
{
    int i,indice;
    int lunghezza=0;
    list temp=l;
	
	//Conta il numero di attivita' 
	while(temp!=NULL)
	{
		lunghezza++;
		temp=temp->next;
	}
	
	//Richiede l'indice dell'attivita'  da modificare
	do
	{
	    printf("Inserisci il numero dell'attivita' da modificare: ");
	    if(scanf("%d",&indice)==1)
	    {
	    	getchar();
	    
	    	if(indice<1||indice>lunghezza)
	    	{
	    		printf("Numero attivita' non valido. Inserisci un numero compreso tra 1 e %d \n",lunghezza);
	    	}
	    }
	    else //Se viene inserito un carattere non valido, viene richiesto un nuovo input 
	    {
		printf("Carattere non valido \n");
		indice= -1;
		while(getchar()!='\n'); //Svuota il buffer
	    }

	}while(indice<1||indice>lunghezza);
	
    //Arriva alla posizione specificata
    for(i=1;i<indice;i++)
    {
    	l=l->next;
    }
	
	//Modifica il campo "completamento"
	do
	{
		char buffer[100];
		printf("Inserisci la nuova percentuale di completamento (percentuale 0-100): ");
		fgets(buffer, sizeof(buffer), stdin);
    
	    	if(sscanf(buffer, "%d",&l->value.completamento)!=1||l->value.completamento<0||l->value.completamento>100)
	    	{
	    		printf("Valore o formato non valido,inserisci un valore tra 0 e 100 \n");
	    		l->value.completamento=-1;
		}
	}while(l->value.completamento<0||l->value.completamento>100);
}

//Funzione per visualizzare e copiare sul file le attivita'  presenti nella lista
void report_settimanale(list l)
{
    FILE *ptr;
    int i=1;
    time_t t=time(NULL); 
    struct tm *oggi=localtime(&t); //Dichiarazione di una struct per memorizzare la data di sistema
    char *stato=NULL;
    ptr=fopen(file_report, "a");
    if(ptr==NULL) //Viene segnalato che il file non viene aperto,ma il programma esegue ugualmente la stampa a video della lista attivita' 
    {
    	printf("Errore apertura file \n");
    }
	printf("REPORT DEL GIORNO: %d/%d/%d \n",oggi->tm_mday,oggi->tm_mon+1,oggi->tm_year+1900);
	fprintf(ptr,"REPORT DEL GIORNO: %d/%d/%d \n",oggi->tm_mday,oggi->tm_mon+1,oggi->tm_year+1900);
	while (l != NULL) 
	{
		printf("ATTIVITA' NUMERO %d \n",i);
	        printf("Corso: %s \n", l->value.corso);
	        printf("Data di scadenza: %s \n", l->value.data_scadenza);
	        printf("Completamento: %d%% \n", l->value.completamento);
	        printf("Priorita': %s \n", l->value.priorita);
       	
                //Controlli per lo stato dell'attività  
	   	if(l->value.completamento==100)
        	{
        		stato="STATO: COMPLETATO";
		}
		else
		{
			int giorno,mese,anno;
			
			sscanf(l->value.data_scadenza,"%d/%d/%d",&giorno,&mese,&anno);
			
			//Confronta con data odierna
			if((anno<oggi->tm_year+1900)||(anno==oggi->tm_year+1900&&mese<oggi->tm_mon+1)||(anno==oggi->tm_year+1900&&mese==oggi->tm_mon+1&&giorno<oggi->tm_mday))
			{
				stato="STATO: IN RITARDO";
			}
			else
			{
				stato="STATO: IN CORSO";
			}
		}
		printf("%s \n",stato);
		printf("\n");
		
		//Se il puntatore al file non e' NULL, copia sul file ogni attivita'  della lista. 
		if(ptr!=NULL)
		{	    
			fprintf(ptr,"ATTIVITA' NUMERO %d \n",i);
			fprintf(ptr,"Corso: %s \n", l->value.corso);
			fprintf(ptr,"Data di scadenza: %s \n", l->value.data_scadenza);
			fprintf(ptr,"Completamento: %d%% \n", l->value.completamento);
			fprintf(ptr,"Priorita': %s \n", l->value.priorita);
			fprintf(ptr,"%s \n",stato);
			fprintf(ptr,"\n");	
		}
        
		i++;
		l = l->next; // Passa al nodo successivo
    	}
    	fclose(ptr);
}

// Funzione per liberare tutta la memoria della lista
void libera_lista(list l) 
{
    while (l != NULL)
    {
        list temp = l;
        l = l->next;
        // Libera tutte le stringhe allocate con strdup
        free(temp->value.descrizione);
        free(temp->value.corso);
        free(temp->value.data_scadenza);
        free(temp->value.data_inizio);
        free(temp->value.priorita);
        // Libera il nodo
        free(temp);
    }
}
