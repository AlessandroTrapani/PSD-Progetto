#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita_studio.h"
#include "lista.h"

// Dichiarazione delle funzioni di test
list test_inserimento(list l);
void test_aggiornamento(list l);
void test_report(list l);

//Main che richiama in successione le singole funzioni di test
int main() 
{
   list l = newList();

    printf("******** INIZIO TEST INSERIMENTO********\n\n");

    l= test_inserimento(l);

    printf("\n******** FINE TEST INSERIMENTO********\n\n");

    printf("******** INIZIO TEST MODIFICA PERCENTUALE********\n\n");

    test_aggiornamento(l);

    printf("\n******** FINE TEST MODIFICA PERCENTUALE********\n\n");

    printf("******** INIZIO TEST GENERAZIONE REPORT SETTIMANALE********\n\n");

    test_report(l);

    printf("\n******** FINE TEST GENERAZIONE REPORT SETTIMANALE********\n");
  
    libera_lista(l);
    return 0;
}