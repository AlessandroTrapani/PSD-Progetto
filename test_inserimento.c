#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita_studio.h"
#include "lista.h"

// Funzione di test per l'inserimento e salvataggio nel file
list test_inserimento(list l) 
{
    attivita_studio a;

    a.descrizione = NULL;
    a.corso = NULL;
    a.data_inizio = NULL;
    a.data_scadenza = NULL;
    a.priorita = NULL;

    // Simulazione inserimento
    printf(">>> TEST INSERIMENTO MANUALE <<<\n");
    inserisci(&a);

    // Inserimento in lista
    l = consList(a, l);
    list temp=l;
    // Scrittura su file
    FILE *ptr;
    int num_salvati = output_file(temp, ptr);

   //Stampa a video dell'esito del test
    if (num_salvati > 0) 
    {
        printf("TEST FAIL:Attivita' inserita correttamente \n", num_salvati);
    } else 
    {
        printf("TEST SUCCESS:Attivita' non salvata correttamente \n");
    }

    return l;
}


