#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "attivita_studio.h"

void inserisci(attivita_studio *nuovo) 
{
    char buffer[1024]; //Buffer temporaneo per la lettura degli input
    size_t lunghezza; //Variabile per contenere la lunghezza dell'input

	do
	{	
	    printf("Inserisci la descrizione: ");
	    fgets(buffer, sizeof(buffer), stdin); //Legge l'intera riga, incluso il '\n'
	    lunghezza = strlen(buffer);
	    if(lunghezza<2)
	    {
	    	printf("La descrizione non puo' essere vuota. \n");
	    }
    	}while(lunghezza<2);
	if (lunghezza > 0 && buffer[lunghezza - 1] == '\n') 
	{
		buffer[--lunghezza] = '\0'; //Rimuove il '\n'
	}
	//Riallocazione della memoria per il campo descrizione
	char *tmp = realloc(nuovo->descrizione, lunghezza + 1);
    if (tmp == NULL) 
	{
	        printf("Errore allocazione memoria.\n");
	        exit(1);
        }
    nuovo->descrizione = tmp;
    strcpy(nuovo->descrizione, buffer); //Copia della stringa nel campo della struttura

	do
	{
	    printf("Inserisci il corso: ");
	    fgets(buffer, sizeof(buffer), stdin);//Legge l'intera riga, incluso il '\n'
	    lunghezza = strlen(buffer);
	    if(lunghezza<2)
	    {
	    	printf("Il nome del corso non puo' essere vuoto. \n");
	    }
	}while(lunghezza<2);
    if (lunghezza > 0 && buffer[lunghezza - 1] == '\n')
	{
		buffer[--lunghezza] = '\0';//Rimuove il '\n'
	}
	tmp = realloc(nuovo->corso, lunghezza + 1);
    if (tmp == NULL) 
	{
        printf("Errore allocazione memoria.\n");
        exit(1);
        }
    nuovo->corso = tmp;
    strcpy(nuovo->corso, buffer);//Copia della stringa nel campo della struttura

do //Ciclo per chiedere la data di inizio e di scadenza 
{
    do //Ciclo per la data di inizio e controllo del formato
	{
	        printf("Inserisci la data di inizio (GG/MM/AAAA): ");
	        fgets(buffer, sizeof(buffer), stdin);
	        lunghezza = strlen(buffer);
	        if (lunghezza > 0 && buffer[lunghezza - 1] == '\n') buffer[--lunghezza] = '\0';
	
	        if (!controlla_data(buffer)) //Richiama la funzione controlla_data per verificare il formato della data inserita
		{
	            printf("Data non valida o formato errato.\n");
	            continue;
	        }
	
	        tmp = realloc(nuovo->data_inizio, lunghezza + 1);
	        if (tmp == NULL) 
			{ 
				printf("Errore allocazione memoria.\n"); 
				exit(1); 
			}
	        nuovo->data_inizio = tmp;
	        strcpy(nuovo->data_inizio, buffer); //Copia della stringa nel campo della struttura
	        break;
        } while (1);

    do //Ciclo per la data di scadenza e controllo del formato + controllo che sia successiva alla data di inizio
	{
	        printf("Inserisci la data di scadenza (GG/MM/AAAA): ");
	        fgets(buffer, sizeof(buffer), stdin);
	        lunghezza = strlen(buffer);
	        if (lunghezza > 0 && buffer[lunghezza - 1] == '\n') buffer[--lunghezza] = '\0';
	
	        if (!controlla_data(buffer)) //Richiama la funzione controlla_data per verificare il formato della data inserita
		{
	            printf("Data non valida o formato errato.\n");
	            continue;
	        }
	
	        if (confronta_date(nuovo->data_inizio, buffer) > 0) //Richiama la funzione confronta_date per verificare che la data di scadenza non sia prima della data di inizio 
		{
	            printf("La data di scadenza non puo' essere precedente alla data di inizio.\n");
	            continue;
	        }
	
	        tmp = realloc(nuovo->data_scadenza, lunghezza + 1);
	        if (tmp == NULL) 
		{ 
		    printf("Errore allocazione memoria.\n"); 
		    exit(1); 
		}
	        nuovo->data_scadenza = tmp;
	        strcpy(nuovo->data_scadenza, buffer); //Copia della stringa nel campo della struttura
	        break;
    } while (1);
    break;
} while (1);

    
    char *priorita1="BASSA";
    char *priorita2="MEDIA";
    char *priorita3="ALTA";
    do //Ciclo per inserire la priorit  dell'attivit  con controllo per il formato
    {
	    printf("Inserisci la priorita' (utilizza questo formato: BASSA,MEDIA,ALTA): ");
	    fgets(buffer, sizeof(buffer), stdin);
	    lunghezza = strlen(buffer);
	    if (lunghezza > 0 && buffer[lunghezza - 1] == '\n')
		{
			buffer[--lunghezza] = '\0';
		}
	    tmp = realloc(nuovo->priorita, lunghezza + 1);
	    if (tmp == NULL) 
	    {
	        printf("Errore allocazione memoria.\n");
	        exit(1);
	    }
	    nuovo->priorita = tmp;
	}while(strcmp(buffer,priorita1)!=0&&strcmp(buffer,priorita2)!=0&&strcmp(buffer,priorita3)!=0); //L'input viene confrontato con le stringhe priorita1,priorita2,priorita3 per verificare che il formato sia corretto
        strcpy(nuovo->priorita, buffer); //Copia della stringa nel campo della struttura
	
	do //Ciclo per il tempo stimato (in ore) e controllo per verificare che non sia minore di 0
	{
	    char buffer[100]; //Buffer locale per leggere la stringa
	    printf("Inserisci il tempo stimato in ore (maggiore o uguale a 0): ");
	    fgets(buffer, sizeof(buffer), stdin);
	    
	    if (sscanf(buffer, "%d", &nuovo->tempo_stimato) != 1 || nuovo->tempo_stimato < 0)
	    {
	    	printf("Valore o formato non valido \n");
	    	nuovo->tempo_stimato=-1;
	    }
	}while (nuovo->tempo_stimato < 0);

	do //Ciclo per il completamento e controllo che sia compreso tra 0 e 100
	{
		char buffer[100]; //Buffer locale per leggere la stringa
		printf("Inserisci il completamento (percentuale 0-100): ");
		fgets(buffer, sizeof(buffer), stdin);
    
	    	if(sscanf(buffer, "%d",&nuovo->completamento)!=1||nuovo->completamento<0||nuovo->completamento>100)
	    	{
	    		printf("Valore o formato non valido,inserisci un valore tra 0 e 100 \n");
	    		nuovo->completamento=-1;
		}
	}while(nuovo->completamento<0||nuovo->completamento>100);
}

//Funzione per verificare che la data inserita sia valida
bool controlla_data(const char *data) 
{
    int giorno, mese, anno;
    if (sscanf(data, "%d/%d/%d", &giorno, &mese, &anno) != 3)
    {
        return false;
    }
    
	if (anno < 1900 || mese < 1 || mese > 12 || giorno < 1 || giorno > 31)
	{
	        return false;
	}
    
	// Controlli sui giorni massimi per ogni mese
        int giorni_per_mese[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    //Controllo per anno bisestile
    if (mese == 2 && ((anno % 4 == 0 && anno % 100 != 0) || anno % 400 == 0))
    {
        giorni_per_mese[1] = 29; 
    }  
	return giorno <= giorni_per_mese[mese - 1];
}

//Funzione per controllare che la data di scadenza non sia precedente alla data di inizio
int confronta_date(const char *data1, const char *data2) 
{
    int giorno1, mese1, anno1, giorno2, mese2, anno2;
    sscanf(data1, "%d/%d/%d", &giorno1, &mese1, &anno1);
    sscanf(data2, "%d/%d/%d", &giorno2, &mese2, &anno2);

    //Confronta anno, poi mese, poi giorno
    if (anno1 != anno2) return anno1 - anno2;
    if (mese1 != mese2) return mese1 - mese2;
    return giorno1 - giorno2;
}
