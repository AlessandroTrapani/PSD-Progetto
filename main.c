#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "attivita_studio.h"
#include "lista.h"

int main()
{
	FILE *registro;
	FILE *report;
	int salvate;
	int conta_righe;
	int scelta,modifica;
	char buffer[1024];
    	size_t lunghezza;
    	char *tmp;
    
    //Allocazione dinamica per una nuova attività
	attivita_studio *nuovo=(attivita_studio *) malloc(sizeof(attivita_studio));
	if (nuovo == NULL) 
	{
        printf("Errore allocazione di memoria. \n");
        return 1;
    	}
    
    //Inizializzazione dei puntatori a NULL
    nuovo->descrizione =NULL;
    nuovo->corso =NULL;
    nuovo->data_scadenza =NULL;
    nuovo->data_inizio =NULL;
    nuovo->priorita =NULL;
	
	//Creazione di una nuova lista vuota
	list l = newList();   
	
	//Apertura del file per leggere le attività salvate in precedenza
	registro=fopen(file_registro,"r");	
	if(registro==NULL)
	{
		printf("File non trovato, nessuna attivita' caricata. \n");
	}
	else
	{
		printf("File caricato correttamente,esci dal programma premendo 0 per salvare correttamente le attivita' di studio. \n");
		conta_righe=0;
		
		//Lettura riga per riga del file
		while(fgets(buffer,sizeof(buffer),registro)!=NULL)
		{
		    lunghezza = strlen(buffer);
		    if (lunghezza > 0 && buffer[lunghezza - 1] == '\n') 
			{
				buffer[--lunghezza] = '\0';
			}
			
			//Assegna i dati letti ai rispettivi campi
			switch(conta_righe)
			{
				case 0:
						break;
				case 1: 
						tmp = realloc(nuovo->descrizione, lunghezza + 1);
					    if (tmp == NULL) 
						{
					        printf("Errore allocazione memoria.\n");
					        exit(1);
					    	}
					    nuovo->descrizione = tmp;
					    strcpy(nuovo->descrizione, buffer);
					    break;
				case 2:
						tmp = realloc(nuovo->corso, lunghezza + 1);
					    if (tmp == NULL) 
						{
					        printf("Errore allocazione memoria.\n");
					        exit(1);
					    	}
					    nuovo->corso = tmp;
					    strcpy(nuovo->corso, buffer);
					    break;
				case 3:
						tmp = realloc(nuovo->data_inizio, lunghezza + 1);
				        if (tmp == NULL) 
						{ 
							printf("Errore allocazione memoria.\n"); 
							exit(1); 
						}
				        nuovo->data_inizio = tmp;
				        strcpy(nuovo->data_inizio, buffer);
				        break;
				case 4:
						tmp = realloc(nuovo->data_scadenza, lunghezza + 1);
				        if (tmp == NULL) 
						{ 
							printf("Errore allocazione memoria.\n"); 
							exit(1); 
						} 
				        nuovo->data_scadenza = tmp;
				        strcpy(nuovo->data_scadenza, buffer);
				        break;
				case 5:
						sscanf(buffer, "%d", &nuovo->tempo_stimato);
						break;
				case 6:
						sscanf(buffer, "%d%%",&nuovo->completamento);
						break;
				case 7:
						tmp = realloc(nuovo->priorita, lunghezza + 1);
						if (tmp == NULL) 
						{
							printf("Errore allocazione memoria.\n");
							exit(1);
						}
						nuovo->priorita = tmp;
					    strcpy(nuovo->priorita, buffer);
					    break;
				case 8:
						break;	
			}
			conta_righe++;
			if(conta_righe==9)
			{
				conta_righe=0;
				l = consList(*nuovo, l); //Aggiunta attività alla lista
			}
		}
		fclose(registro);
	}
	
	//Menù interattivo per l'utente
	do
	{
		printf("0 - ESCI \n");
		printf("1 - INSERISCI ATTIVITA' \n");
		printf("2 - VISUALIZZA ATTIVITA' \n");
		printf("3 - REPORT SETTIMANALE \n");

		if(scanf("%d",&scelta)==1)
		{
			getchar(); //Rimuove il newLine dal buffer
			switch(scelta)
			{
				case 0: //Il programma termina e richiama la funzione output_file per leggere a schermo il numero di attività salvate nel file
						salvate=output_file(l,registro);
						printf("Numero di attivita' salvate: %d \n",salvate);
						break;
				case 1: //Permette all'utente di inserire un'attività nella lista richiamando la funzione inserisci e successivamente consList
						inserisci(nuovo);
						l = consList(*nuovo, l);  // Aggiunge l'attività inserita nella lista
						break;	
				case 2: //Controlla se la lista è vuota con la funzione emptyList, se contiene dei valori richiama la funzione outputList e stampa le attività a video
						if(emptyList(l))
						{
							printf("Lista attivita' vuota. \n");
						}
						else
						{
							outputList(l);
							
							//Altro menù interattivo per l'utente
							printf("0 - TORNA AL MENU' PRINCIPALE \n");
							printf("1 - MODIFICA COMPLETAMENTO ATTIVITA' \n"); //Permette di modificare la percentuale di completamento di un'attività specifica
							scanf("%d", &modifica);
							getchar();
							
							switch(modifica)
							{
								case 0:
										break;
								case 1: //Richiama la funzione modifica_lista per modificare la percentuale
										modifica_lista(l);
										break;
								default:
										printf("Scelta non valida \n");
							}
						}
						break;
				case 3:
						if(emptyList(l))
						{
							printf("Lista attivita' vuota. \n");
						}
						else
						{
							report_settimanale(l,report); //Viene richiamata la funzione report_settimanale,stampa a video il contenuto della lista e lo salva nel file report
						}
						break;		
				default: //In caso di scelta non valida, il programma richiede di nuovo l'input della scelta
						printf("Scelta non valida \n");
			}
		}
		else //Se viene inserito un carattere non valido, viene richiesto un nuovo input 
		{
			printf("Carattere non valido \n");
			scelta= -1;
			while(getchar()!='\n'); //Svuota il buffer
		}
	}while(scelta!=0);
	
	//Libera la memoria allocata
	free(nuovo->descrizione);
	free(nuovo->corso);
	free(nuovo->data_scadenza);
	free(nuovo->data_inizio);
	free(nuovo->priorita);
	free(nuovo);

	//Richiama al funzione per liberare la memoria allocata per tutti i nodi della lista
	libera_lista(l);
	
	return 0;
}
