#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita_studio.h"
#include "lista.h"

//Dichiarazione struct node per accedere agli attributi contenuti in ciascun nodo della lista
struct node 
{
    attivita_studio value;
    struct node *next;
};

//Funzione che richiama le funzioni modifica_lista e output_file del programma principale
void test_aggiornamento(list l)
{
	FILE *ptr;	
	printf("Valore di completamento attuale: %d \n",l->value.completamento); //Stampa a video della percentuale non aggiornata
	modifica_lista(l);
	printf("Valore di completamento modificato: %d \n",l->value.completamento);//Stampa a video della percentuale aggiornata
	output_file(l, ptr);
}