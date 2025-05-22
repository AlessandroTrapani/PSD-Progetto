
#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>
#include "attivita_studio.h"
#define file_registro "registro_attivita.txt"
#define file_report "report.txt"

typedef struct node *list;

/*
Funzione: newList
****************************************
Crea una nuova lista vuota e restituisce la lista creata.

Parametri: nessuno.

Pre-condizione: 
-deve esserci abbastanza memoria per la creazione del nodo della lista.

Post-condizione: 
-crea la nuova lista.

Ritorna: 
restituisce la lista nuova.
*/
list newList(void);

/*
Funzione: emptyList
****************************************
Verifica se la lista passata come argomento è vuota e restituisce un intero (1 se la lista è vuota, altrimenti 0).

Parametri: 
l: lista di tipo list.

Pre-condizione: 
-la lista passata deve esistere.

Post-condizione: 
-verifica se la lista sia vuota o contenga dei valori

Ritorna: 
1(TRUE) se la lista è vuota, altrimenti 0(FALSE)
*/
bool emptyList(list l);

/*
Funzione: consList
****************************************
Aggiunge un elemento di tipo `attivita_studio` all'inizio di una lista di tipo `list`, restituendo la nuova lista.

Parametri: 
val: valore da inserire nella lista, di tipo attivita_studio.
l: lista di tipo list a cui aggiungere l'elemento.

Pre-condizione: 
- Il valore `val` deve essere un elemento valido di tipo attivita_studio.
- La lista `l` deve essere una lista esistente (anche eventualmente vuota).

Post-condizione: 
- La lista risultante conterrà il nuovo elemento `val` come primo nodo, seguito dagli elementi originari della lista `l`.

Ritorna: 
Una nuova lista di tipo list con l'elemento `val` in testa.
*/
list consList(attivita_studio val, list l);

/*
Funzione: outputList
****************************************
Stampa sullo standard output tutti gli elementi contenuti nella lista `l`.

Parametri:
l: lista di tipo list da stampare.

Pre-condizione:
- La lista `l` deve esistere (anche eventualmente vuota).

Post-condizione:
- Gli elementi della lista vengono stampati in ordine.

Ritorna:
Nessun valore (void).
*/
void outputList(list l);

/*
Funzione: output_file
****************************************
Scrive tutti gli elementi della lista `l` su un file di testo "registro_attivita.txt", utilizzando il puntatore al file `ptr`.

Parametri:
l: lista di tipo list da scrivere nel file.
ptr: puntatore a FILE aperto in modalità scrittura.

Pre-condizione:
- La lista `l` deve esistere (anche eventualmente vuota).
- Il puntatore `ptr` deve essere valido e riferirsi a un file aperto correttamente.

Post-condizione:
- Gli elementi della lista vengono scritti nel file.

Ritorna:
Un intero che rappresenta il numero di attività salvate.
*/
int output_file(list l, FILE *ptr);

/*
Funzione: modifica_lista
****************************************
Richiede all'utente l'indice dell'attività da modificare e modifica l'elemento "completamento" dell'attività selezionata.

Parametri:
l: lista di tipo list da modificare.

Pre-condizione:
- L'indice dell'attività inserito dall'utente deve essere valido.
- La lista `l` deve esistere e contenere almeno un elemento modificabile.

Post-condizione:
- Il nodo della lista viene modificato.

Ritorna:
Nessun valore (void).
*/
void modifica_lista(list l);

/*
Funzione: report_settimanale
****************************************
La funzione stampa a video e copia sul file "report.txt" l'elenco delle attività presenti nella lista e ne mostra lo stato di completamento.

Parametri:
l: lista di tipo list da visualizzare.
ptr: puntatore al file su cui copiare i dati.

Pre-condizione:
- La lista `l` deve esistere e contenere almeno un elemento modificabile.
-Il puntatore 'ptr' deve essere valido e riferirsi a un file aperto correttamente.

Post-condizione:
-I dati vengono visualizzati a schermo e copiati sul file.

Ritorna:
Nessun valore (void).
*/
void report_settimanale(list l,FILE *ptr);

/*
Funzione: libera_lista
****************************************
La funzione libera la memoria allocata tramite strdup di tutti i nodi della lista

Parametri:
l: lista di tipo list da cui liberare la memoria

Pre-condizione:
-La lista 'l' deve esistere e contenere almeno un attivita' di studio

Post-condizione:
-La memoria viene liberata

Ritorna:
Nessun valore(void).
*/
void libera_lista(list l);

#endif
