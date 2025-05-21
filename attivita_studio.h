#ifndef ATTIVITA_STUDIO_H
#define ATTIVITA_STUDIO_H
#include <stdbool.h>
#include <time.h>

typedef struct  
{
	char *descrizione;
	char *corso;
	char *data_scadenza;
	char *data_inizio;
	int tempo_stimato;
	int completamento;
	char *priorita;     
}attivita_studio;

/*
Funzione: inserisci
****************************************
Inserisce una nuova attività di studio nella lista attraverso il puntatore `nuovo`.

Parametri:
nuovo: puntatore a una struttura di tipo attivita_studio contenente i dati dell'attività da inserire.

Pre-condizione:
- Il puntatore `nuovo` deve puntare a una struttura valida e correttamente inizializzata.

Post-condizione:
- L'attività rappresentata da `nuovo` viene inserita nella lista.

Ritorna:
Nessun valore (void).
*/
void inserisci(attivita_studio *nuovo);


/*
Funzione: controlla_data
****************************************
Verifica se la stringa `data` rappresenta una data valida secondo un formato predefinito (gg/mm/aaaa).

Parametri:
data: stringa costante che rappresenta una data.

Pre-condizione:
- `data` deve essere una stringa valida (non NULL).

Post-condizione:
- Viene verificata la correttezza sintattica e logica della data (giorno, mese, anno).

Ritorna:
TRUE (1) se la data è valida, FALSE (0) altrimenti.
*/
bool controlla_data(const char *data);


/*
Funzione: confronta_date
****************************************
Confronta due date fornite come stringhe nel formato "gg/mm/aaaa" e restituisce un valore intero che indica la loro relazione temporale.

Parametri:
data1: prima data da confrontare (stringa).
data2: seconda data da confrontare (stringa).

Pre-condizione:
- Le stringhe `data1` e `data2` devono rappresentare date valide nel formato "gg/mm/aaaa".

Post-condizione:
- Viene eseguito un confronto tra le due date in ordine cronologico (anno, mese, giorno).

Ritorna:
Un intero:
- Valore negativo se `data1` è precedente a `data2`
- 0 se le due date sono uguali
- Valore positivo se `data1` è successiva a `data2`
*/
int confronta_date(const char *data1, const char *data2);
 
#endif