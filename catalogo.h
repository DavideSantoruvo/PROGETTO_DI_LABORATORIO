/**
* @file catalogo.h
 * @brief Interfaccia del modulo per la gestione di un catalogo di videogiochi.
 *
 * Questo modulo consente di gestire un catalogo di videogiochi includendo
 * funzionalità per inizializzazione, caricamento, visualizzazione, ordinamento,
 * ricerca, modifica, acquisto e recensioni.
 *
 * @author Davide Santoruvo, Diego Mundo
 * @date Giugno 2025
 */

#ifndef CATALOGO_H
#define CATALOGO_H

// ------------------------------
// Costanti di configurazione
// ------------------------------

#define FILE_CATALOGO "catalogo.dat"         // Nome del file contenente i dati
#define MAX_TITOLO 100                       // Lunghezza massima del titolo
#define MAX_EDITORE 50                       // Lunghezza massima dell'editore
#define MAX_SVILUPPATORE 50                  // Lunghezza massima dello sviluppatore
#define MAX_DESC 255                         // Lunghezza massima della descrizione
#define MAX_GENERE 30                        // Lunghezza massima del nome di un genere
#define MAX_GENERI 5                         // Numero massimo di generi per gioco
#define MAX_RECENSIONI 50                    // Numero massimo di recensioni per gioco
#define MAX_VIDEOGIOCHI 100                  // Numero massimo di videogiochi nel catalogo

// ------------------------------
// Strutture dati
// ------------------------------

/**
 * @struct Recensione_t
 * @brief Struttura che rappresenta una recensione.
 *
 * Una recensione è composta da:
 * - voto: valore numerico (intero, es. da 0 a 5)
 * - descrizione: testo libero dell’utente
 */

typedef struct {
    int voto;
    char descrizione[MAX_DESC];
} Recensione_t;

/**
 * @struct Videogioco_t
 * @brief Struttura dati per rappresentare un videogioco nel catalogo.
 *
 * Contiene le informazioni base del videogioco, i generi assegnati, le recensioni,
 * il numero di copie vendute e la media dei voti.
 */

typedef struct {
    char titolo[MAX_TITOLO];
    char editore[MAX_EDITORE];
    char sviluppatore[MAX_SVILUPPATORE];
    char descrizione[MAX_DESC];
    int anno_pubblicazione;
    char generi[MAX_GENERI][MAX_GENERE];
    int num_generi;
    Recensione_t recensioni[MAX_RECENSIONI];
    int num_recensioni;
    int copie_vendute;
    float media_voti;
} Videogioco_t;

// ------------------------------
// Prototipi delle funzioni
// ------------------------------

/**
 * @brief Inizializza il catalogo scrivendo 20 videogiochi predefiniti.
 *
 * Se il file `catalogo.dat` non esiste, crea un file binario e inserisce
 * 20 videogiochi preimpostati. Se il file già esiste, la funzione non fa nulla.
 *
 * @pre Nessun parametro richiesto.
 * @post Il file `catalogo.dat` sarà creato e popolato, se assente.
 * @return Nessun valore di ritorno.
 */
void inizializzaCatalogo();

/**
 * @brief Carica i videogiochi dal file `catalogo.dat` in memoria.
 *
 * @param[out] catalogo Array dove vengono caricati i videogiochi letti dal file.
 * @return Numero di videogiochi effettivamente caricati dal file.
 *
 * @pre Il file `catalogo.dat` deve esistere.
 * @post L'array contiene i videogiochi presenti nel file.
 */
int caricaCatalogo(Videogioco_t catalogo[]);

/**
 * @brief Visualizza a schermo i videogiochi presenti nel catalogo.
 *
 * Stampa tutti i dati disponibili per ogni videogioco caricato dal file.
 *
 * @return Nessun valore di ritorno.
 */
void visualizzaCatalogo();

/**
 * @brief Aggiunge un nuovo videogioco al catalogo.
 *
 * Legge i dati del nuovo videogioco da input standard, li valida e li scrive
 * in coda al file `catalogo.dat`.
 *
 * @return Nessun valore di ritorno.
 * @warning Non viene effettuato alcun controllo su duplicati.
 */
void aggiungiVideogioco();

/**
 * @brief Permette di modificare un videogioco esistente.
 *
 * Chiede il titolo di un videogioco esistente e consente di aggiornare i suoi dati
 * (editore, descrizione, generi, ecc.).
 *
 * @return Nessun valore di ritorno.
 */
void modificaVideogioco();

/**
 * @brief Ricerca videogiochi nel catalogo in base a un criterio.
 *
 * L'utente può selezionare uno dei seguenti criteri:
 * titolo, editore, sviluppatore, genere, anno di pubblicazione.
 * La ricerca è **case-insensitive** e supporta **sottostringhe**.
 *
 * @return Nessun valore di ritorno.
 * @note La funzione stampa i risultati trovati.
 */
void ricercaVideogioco();

/**
 * @brief Aggiunge una recensione a un videogioco esistente.
 *
 * L’utente specifica il titolo del gioco, un voto e una descrizione.
 * Viene aggiornata anche la media dei voti.
 *
 * @return Nessun valore di ritorno.
 * @warning La funzione non consente più recensioni oltre il limite massimo.
 */
void aggiungiRecensione();

/**
 * @brief Modifica una recensione esistente.
 *
 * Dopo aver selezionato il gioco e la recensione desiderata (tramite indice),
 * l’utente può modificare voto e descrizione.
 *
 * @return Nessun valore di ritorno.
 * @pre Il gioco deve avere almeno una recensione.
 */
void modificaRecensione();

/**
 * @brief Ricalcola la media dei voti in base alle recensioni.
 *
 * @param[in,out] gioco Puntatore alla struttura del videogioco da aggiornare.
 * @return Nessun valore di ritorno.
 *
 * @note È chiamata internamente dopo ogni modifica o inserimento di recensione.
 */
void aggiornaMediaRecensioni(Videogioco_t *gioco);

/**
 * @brief Registra l'acquisto di un videogioco.
 *
 * L’utente inserisce il titolo del gioco, e se esiste, il contatore
 * `copie_vendute` viene incrementato.
 *
 * @return Nessun valore di ritorno.
 * @warning Se il gioco non viene trovato, viene mostrato un messaggio di errore.
 */
void acquistaVideogioco();

/**
* @brief Visualizza il menu per l'amministratore.
*
* Offre operazioni di gestione come:
* - inizializzazione
* - aggiunta
* - modifica
* - visualizzazione
* - ricerca
*
* @return Nessun valore di ritorno.
*/
void menu_amministratore();

/**
 * @brief Visualizza il menu per il visitatore.
 *
 * Permette di:
 * - visualizzare il catalogo
 * - effettuare ricerche
 * - ordinare
 * - acquistare giochi
 * - gestire recensioni
 *
 * @return Nessun valore di ritorno.
 */
void menu_visitatore();

/**
 * @brief Avvia il menu principale del programma.
 *
 * L’utente può scegliere se entrare come amministratore o visitatore,
 * oppure uscire dal programma.
 *
 * @return Nessun valore di ritorno.
 */
void menu_principale();

/**
 * @brief Mostra un sottomenu per ordinare il catalogo.
 *
 * Consente di scegliere l’ordinamento per:
 * - media voti
 * - copie vendute
 *
 * @return Nessun valore di ritorno.
 */
void menu_ordinamento_catalogo();

/**
 * @brief Ordina il catalogo per media dei voti in ordine crescente.
 *
 * Carica i videogiochi, li ordina e stampa i risultati ordinati.
 *
 * @return Nessun valore di ritorno.
 */
void ordinamentoPunteggio();

/**
 * @brief Ordina il catalogo per numero di copie vendute in ordine crescente.
 *
 * I dati vengono letti, ordinati e visualizzati.
 *
 * @return Nessun valore di ritorno.
 */
void ordinamentoCopieVendute();

#endif // CATALOGO_H