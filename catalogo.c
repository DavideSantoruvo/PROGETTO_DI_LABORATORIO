/**
* @file catalogo.c
 * @brief Implementazione delle funzioni per la gestione del catalogo dei videogiochi.
 * @author Davide Santoruvo, Diego Mundo
 * @date Giugno 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "catalogo.h"

#include <stdio.h>
#include <string.h>
#include "catalogo.h"
#include <ctype.h>

// Funzione: inizializzaCatalogo
// Descrizione: Inizializza il file binario del catalogo con 20 videogiochi predefiniti.
// Se il file esiste già, la funzione non lo sovrascrive e termina subito.

void inizializzaCatalogo() {
    // Apro il file in modalità "read binary" per controllare se esiste già.
    FILE *file = fopen(FILE_CATALOGO, "rb");
    if (file) {
        // Il file esiste, quindi lo chiudo e non procedo con la sovrascrittura.
        fclose(file);
        return;
    }

    // Il file non esiste: apro in modalità "write binary" per crearlo da zero.
    file = fopen(FILE_CATALOGO, "wb");
    if (!file) {
        // Se c'è un errore nell'apertura del file, stampo un messaggio e termino.
        printf("Errore apertura file.\n");
        return;
    }

    // Definisco un array contenente solo i 20 videogiochi reali da inserire nel catalogo iniziale.
    // Ogni videogioco ha: titolo, editore, sviluppatore, descrizione, anno di pubblicazione,
    // lista dei generi, numero di generi, nessuna recensione iniziale, 0 copie vendute,
    // 0 recensioni, media voti = 0.0.
    Videogioco_t giochi[] = {
        {"The Witcher 3", "CD Projekt", "CD Projekt RED", "RPG open world", 2015, {"RPG"}, 1, {}, 0, 0, 0.0},
        {"Cyberpunk 2077", "CD Projekt", "CD Projekt RED", "Action RPG futuristico", 2020, {"RPG", "Action"}, 2, {}, 0, 0, 0.0},
        {"Elden Ring", "Bandai Namco", "FromSoftware", "Action RPG fantasy", 2022, {"RPG", "Adventure"}, 2, {}, 0, 0, 0.0},
        {"God of War", "Sony", "Santa Monica Studio", "Action game mitologico", 2018, {"Action", "Adventure"}, 2, {}, 0, 0, 0.0},
        {"Red Dead Redemption 2", "Rockstar Games", "Rockstar Studios", "Western open world", 2018, {"Action", "Adventure"}, 2, {}, 0, 0, 0.0},
        {"Horizon Forbidden West", "Sony", "Guerrilla Games", "Action RPG post-apocalittico", 2022, {"Action", "RPG"}, 2, {}, 0, 0, 0.0},
        {"Dark Souls III", "Bandai Namco", "FromSoftware", "Action RPG difficile", 2016, {"RPG", "Adventure"}, 2, {}, 0, 0, 0.0},
        {"Sekiro: Shadows Die Twice", "Activision", "FromSoftware", "Action con combattimenti precisi", 2019, {"Action", "Adventure"}, 2, {}, 0, 0, 0.0},
        {"Resident Evil 4 Remake", "Capcom", "Capcom", "Survival horror", 2023, {"Horror", "Action"}, 2, {}, 0, 0, 0.0},
        {"Bloodborne", "Sony", "FromSoftware", "Action RPG gotico", 2015, {"RPG", "Adventure"}, 2, {}, 0, 0, 0.0},
        {"Grand Theft Auto V", "Rockstar Games", "Rockstar North", "Open world criminale", 2013, {"Action", "Adventure"}, 2, {}, 0, 0, 0.0},
        {"Minecraft", "Mojang", "Mojang Studios", "Sandbox creativo", 2011, {"Sandbox", "Adventure"}, 2, {}, 0, 0, 0.0},
        {"Stardew Valley", "ConcernedApe", "ConcernedApe", "Simulazione agricola", 2016, {"Simulation", "RPG"}, 2, {}, 0, 0, 0.0},
        {"The Legend of Zelda: Breath of the Wild", "Nintendo", "Nintendo", "Action RPG open world", 2017, {"Adventure", "Action"}, 2, {}, 0, 0, 0.0},
        {"Super Mario Odyssey", "Nintendo", "Nintendo", "Platform 3D", 2017, {"Platform"}, 1, {}, 0, 0, 0.0},
        {"Metroid Prime Remastered", "Nintendo", "Retro Studios", "FPS esplorativo", 2023, {"Shooter", "Adventure"}, 2, {}, 0, 0, 0.0},
        {"Halo Infinite", "Xbox Game Studios", "343 Industries", "FPS fantascientifico", 2021, {"Shooter", "Action"}, 2, {}, 0, 0, 0.0},
        {"DOOM Eternal", "Bethesda", "id Software", "FPS frenetico", 2020, {"Shooter", "Action"}, 2, {}, 0, 0, 0.0},
        {"Final Fantasy VII Remake", "Square Enix", "Square Enix", "RPG giapponese", 2020, {"RPG", "Action"}, 2, {}, 0, 0, 0.0},
        {"The Last of Us Part II", "Sony", "Naughty Dog", "Action-drama post-apocalittico", 2020, {"Action", "Adventure"}, 2, {}, 0, 0, 0.0}
    };

    // Calcolo quanti videogiochi ci sono nell'array
    size_t n = sizeof(giochi) / sizeof(giochi[0]);

    // Scrivo tutti i videogiochi effettivamente presenti (solo i 20 reali) nel file.
    fwrite(giochi, sizeof(Videogioco_t), n, file);
    fclose(file);

    // Avviso l’utente che l’inizializzazione è avvenuta correttamente.
    printf("Catalogo inizializzato con %zu videogiochi!\n", n);
}







// Funzione: caricaCatalogo
// Descrizione: Carica i videogiochi presenti nel file catalogo.dat nell'array passato come argomento.
// Restituisce il numero di videogiochi letti effettivamente dal file.
int caricaCatalogo(Videogioco_t catalogo[]) {
    // Apro il file catalogo.dat in modalità "read binary"
    FILE *file = fopen(FILE_CATALOGO, "rb");
    if (!file) {
        // Se il file non esiste o non è accessibile, stampo un errore.
        printf("Errore nell'apertura del file catalogo.\n");
        return 0;
    }

    // Variabile per contare quanti videogiochi sono stati letti.
    int count = 0;

    // Leggo dal file tutti i videogiochi presenti, fino a raggiungere il massimo consentito.
    while (count < MAX_VIDEOGIOCHI &&
           fread(&catalogo[count], sizeof(Videogioco_t), 1, file) == 1) {
        count++;
    }

    // Chiudo il file.
    fclose(file);

    // Restituisco il numero di giochi letti.
    return count;
}







// Funzione per visualizzare l'intero catalogo dei videogiochi.
// La funzione apre il file in modalità binaria e stampa i dati di ogni videogioco presente.
void visualizzaCatalogo() {
    // Apro il file del catalogo in modalità "read binary".
    FILE *file = fopen(FILE_CATALOGO, "rb");
    if (!file) {
        // Se il file non viene aperto, può essere dovuto a varie ragioni (ad esempio, il file non esiste
        // o l'utente non ha i permessi necessari).
        // uso perror() per stampare un messaggio d'errore su stderr basato sul valore corrente di errno.
        // Il messaggio che passo a perror() viene stampato, seguito da una breve descrizione dell'errore.
        perror("Errore nell'apertura del file. Il catalogo potrebbe non esistere");
        return;
    }

    // Variabile per contenere i dati di un singolo videogioco, letti dal file.
    Videogioco_t gioco;
    // Flag per verificare se il catalogo è vuoto.
    int vuoto = 1;

    printf("\n--- CATALOGO VIDEOGIOCHI ---\n");
    // Leggo i record uno per uno dal file.
    while (fread(&gioco, sizeof(Videogioco_t), 1, file)) {
        // Se entro nel ciclo, significa che almeno un videogioco è stato letto.
        vuoto = 0;
        // Stampo i dati principali del videogioco.
        printf("Titolo: %s\n", gioco.titolo);
        printf("Editore: %s\n", gioco.editore);
        printf("Sviluppatore: %s\n", gioco.sviluppatore);
        printf("Anno di pubblicazione: %d\n", gioco.anno_pubblicazione);
        printf("Copie vendute: %d\n", gioco.copie_vendute);
        // Stampo la media dei voti e il numero di recensioni registrate.
        printf("Media recensioni: %.2f (%d recensione/i)\n", gioco.media_voti, gioco.num_recensioni);
        printf("--------------------------\n");
    }

    // Se non è stato trovato nessun record (catalogo vuoto), avverto l'utente.
    if (vuoto) {
        printf("Nessun videogioco presente nel catalogo.\n");
    }

    // Chiudo il file per liberare le risorse.
    fclose(file);
}






// Permette di aggiungere un nuovo videogioco al catalogo verificando
// che il titolo non sia già presente. Raccoglie i dati necessari dall'utente (editore,
// sviluppatore, descrizione, anno, generi) e li memorizza nel file catalogo.dat.
void aggiungiVideogioco() {
    // Carico l'intero catalogo per verificare se il titolo è già presente
    Videogioco_t catalogo[MAX_VIDEOGIOCHI];
    int num_videogiochi = caricaCatalogo(catalogo);

    // Richiedo all'utente il titolo del nuovo videogioco
    char titolo_temp[MAX_TITOLO];
    printf("Titolo: ");
    scanf(" %[^\n]", titolo_temp);

    // Controllo se il titolo è già presente
    for (int i = 0; i < num_videogiochi; i++) {
        if (strcmp(catalogo[i].titolo, titolo_temp) == 0) {
            printf("Errore: videogioco già presente nel catalogo.\n");
            return;
        }
    }

    // Apro il file per aggiungere un nuovo videogioco
    FILE *file = fopen(FILE_CATALOGO, "ab");
    if (!file) {
        perror("Errore nell'apertura del file per aggiungere il videogioco");
        return;
    }

    // Inizializzo la struttura con il titolo inserito e raccolgo i restanti dati
    Videogioco_t nuovo;
    strcpy(nuovo.titolo, titolo_temp);

    printf("Editore: ");
    scanf(" %[^\n]", nuovo.editore);

    printf("Sviluppatore: ");
    scanf(" %[^\n]", nuovo.sviluppatore);

    printf("Descrizione: ");
    scanf(" %[^\n]", nuovo.descrizione);

    printf("Anno di pubblicazione: ");
    scanf("%d", &nuovo.anno_pubblicazione);

    do {
        printf("Numero di generi (max %d): ", MAX_GENERI);
        scanf("%d", &nuovo.num_generi);
        if (nuovo.num_generi < 1 || nuovo.num_generi > MAX_GENERI)
            printf("Numero di generi non valido. Deve essere tra 1 e %d.\n", MAX_GENERI);
    } while (nuovo.num_generi < 1 || nuovo.num_generi > MAX_GENERI);

    for (int i = 0; i < nuovo.num_generi; i++) {
        printf("Genere %d: ", i + 1);
        scanf(" %[^\n]", nuovo.generi[i]);
    }

    nuovo.num_recensioni = 0;
    nuovo.copie_vendute = 0;
    nuovo.media_voti = 0.0;

    // Scrivo il nuovo videogioco nel file
    if (fwrite(&nuovo, sizeof(Videogioco_t), 1, file) != 1) {
        perror("Errore nella scrittura del videogioco");
    } else {
        printf("Videogioco aggiunto al catalogo con successo!\n");
    }

    fclose(file);
}







// Permette all'utente di modificare i dettagli di un videogioco esistente
// nel catalogo. L'utente inserisce il titolo del videogioco da modificare e, se trovato,
// vengono richiesti e aggiornati i nuovi dati (editore, sviluppatore, descrizione, anno,
// generi, ecc.). Il record aggiornato viene riscritto nel file.
void modificaVideogioco() {
    // Apro il file catalogo in modalità "rb+" (lettura e scrittura in binario)
    FILE *file = fopen(FILE_CATALOGO, "rb+");
    if (!file) {
        printf("Errore apertura file.\n");
        return;
    }

    // Richiedo all'utente il titolo del videogioco che si desidera modificare
    char titolo[MAX_TITOLO];
    printf("Inserisci il titolo del videogioco da modificare: ");
    scanf(" %[^\n]", titolo);

    Videogioco_t gioco;      // Variabile per memorizzare ciascun record letto dal file
    int trovato = 0;       // Flag che indica se il videogioco è stato trovato

    // Scorro il file record per record per cercare il videogioco
    while (fread(&gioco, sizeof(Videogioco_t), 1, file)) {
        if (strcmp(gioco.titolo, titolo) == 0) {
            // Se il titolo corrisponde a quello inserito, segnalo che è stato trovato
            trovato = 1;
            // Riporto il puntatore all'inizio del record corrente per poterlo aggiornare
            fseek(file, (long long) -sizeof(Videogioco_t), SEEK_CUR);

            // Richiedo il nuovo editore e lo memorizzo nel record
            printf("Inserisci nuovo editore: ");
            scanf(" %[^\n]", gioco.editore);

            // Richiedo il nuovo sviluppatore e lo memorizzo nel record
            printf("Inserisci nuovo sviluppatore: ");
            scanf(" %[^\n]", gioco.sviluppatore);

            // Richiedo la nuova descrizione del videogioco
            printf("Inserisci nuova descrizione: ");
            scanf(" %[^\n]", gioco.descrizione);

            // Richiedo il nuovo anno di pubblicazione
            printf("Inserisci nuovo anno di pubblicazione: ");
            scanf("%d", &gioco.anno_pubblicazione);

            // Modifica dei generi:
            // Richiedo il numero di generi associati al videogioco, garantendo un input valido
            printf("Numero di generi (max %d): ", MAX_GENERI);
            while (1) {
                scanf("%d", &gioco.num_generi);
                if (gioco.num_generi >= 1 && gioco.num_generi <= MAX_GENERI) {
                    break;
                }
                // Se l'input non è valido, richiedo nuovamente
                printf("Numero di generi non valido. Deve essere tra 1 e %d.\n", MAX_GENERI);
                printf("Riprova: ");
            }

            // Richiedo all'utente l'inserimento di ciascun genere
            for (int i = 0; i < gioco.num_generi; i++) {
                printf("Genere %d: ", i + 1);
                scanf(" %[^\n]", gioco.generi[i]);
            }

            // Scrivo il record aggiornato nel file (sovrascrivendo il vecchio record)
            fwrite(&gioco, sizeof(Videogioco_t), 1, file);
            printf("Modifica completata.\n");
            break;
        }
    }

    // Se il videogioco non è stato trovato, informo l'utente
    if (!trovato) {
        printf("Videogioco non trovato.\n");
    }

    // Chiudo il file per liberare le risorse
    fclose(file);
}







// Funzione di supporto: converte una stringa in minuscolo.
// Descrizione: Prende una stringa in input e la copia nella stringa 'destinazione',
// convertendo ogni carattere in minuscolo, per permettere confronti insensibili al maiuscolo/minuscolo.
void convertiInMinuscolo(const char *sorgente, char *destinazione) {
    while (*sorgente) {
        *destinazione = tolower(*sorgente);
        sorgente++;
        destinazione++;
    }
    *destinazione = '\0';  // Terminazione della stringa
}








// Funzione: ricercaVideogioco
// Descrizione: Permette all’utente di cercare videogiochi nel catalogo usando uno dei seguenti criteri:
// - titolo, editore, sviluppatore, genere o anno di pubblicazione.
// Il confronto è insensibile al maiuscolo/minuscolo e funziona anche su sottostringhe.
void ricercaVideogioco() {
    Videogioco_t catalogo[MAX_VIDEOGIOCHI];
    int numero_videogiochi = caricaCatalogo(catalogo);

    // Stampa dei criteri disponibili
    printf("Criteri di ricerca disponibili:\n");
    printf("1. Titolo\n");
    printf("2. Editore\n");
    printf("3. Sviluppatore\n");
    printf("4. Genere\n");
    printf("5. Anno di pubblicazione\n");
    printf("Scegli un criterio (1-5): ");

    int scelta;
    scanf("%d", &scelta);
    getchar(); // Consuma il newline residuo

    if (scelta < 1 || scelta > 5) {
        printf("Criterio non valido.\n");
        return;
    }

    char chiave[100];
    printf("Inserisci la stringa o valore da cercare: ");
    fgets(chiave, sizeof(chiave), stdin);
    chiave[strcspn(chiave, "\n")] = '\0';  // Rimuove il newline

    // Conversione della chiave di ricerca in minuscolo
    char chiave_minuscola[100];
    convertiInMinuscolo(chiave, chiave_minuscola);

    int trovati = 0;

    // Scorro ogni videogioco nel catalogo per confrontare il criterio selezionato
    for (int i = 0; i < numero_videogiochi; i++) {
        char campo_da_confrontare[100];
        int corrispondenza = 0;

        switch (scelta) {
            case 1:  // Titolo
                convertiInMinuscolo(catalogo[i].titolo, campo_da_confrontare);
                if (strstr(campo_da_confrontare, chiave_minuscola))
                    corrispondenza = 1;
                break;
            case 2:  // Editore
                convertiInMinuscolo(catalogo[i].editore, campo_da_confrontare);
                if (strstr(campo_da_confrontare, chiave_minuscola))
                    corrispondenza = 1;
                break;
            case 3:  // Sviluppatore
                convertiInMinuscolo(catalogo[i].sviluppatore, campo_da_confrontare);
                if (strstr(campo_da_confrontare, chiave_minuscola))
                    corrispondenza = 1;
                break;
            case 4:  // Genere (controlla ogni genere nella lista del videogioco)
                for (int j = 0; j < catalogo[i].num_generi; j++) {
                    convertiInMinuscolo(catalogo[i].generi[j], campo_da_confrontare);
                    if (strstr(campo_da_confrontare, chiave_minuscola)) {
                        corrispondenza = 1;
                        break;
                    }
                }
                break;
            case 5:  // Anno di pubblicazione
            {
                char anno_str[10];
                sprintf(anno_str, "%d", catalogo[i].anno_pubblicazione);
                if (strstr(anno_str, chiave_minuscola))
                    corrispondenza = 1;
            }
                break;
        }

        if (corrispondenza) {
            // Se il videogioco corrisponde al criterio, viene stampato
            printf("\n--- RISULTATO TROVATO ---\n");
            printf("Titolo: %s\n", catalogo[i].titolo);
            printf("Editore: %s\n", catalogo[i].editore);
            printf("Sviluppatore: %s\n", catalogo[i].sviluppatore);
            printf("Anno: %d\n", catalogo[i].anno_pubblicazione);
            printf("Descrizione: %s\n", catalogo[i].descrizione);
            printf("Generi: ");
            for (int j = 0; j < catalogo[i].num_generi; j++) {
                printf("%s", catalogo[i].generi[j]);
                if (j < catalogo[i].num_generi - 1)
                    printf(", ");
            }
            printf("\n");

            // Stampa delle recensioni, se presenti
            if (catalogo[i].num_recensioni > 0) {
                printf("Recensioni:\n");
                for (int r = 0; r < catalogo[i].num_recensioni; r++) {
                    printf("  %d: Voto: %d - %s\n", r + 1,
                           catalogo[i].recensioni[r].voto,
                           catalogo[i].recensioni[r].descrizione);
                }
                printf("Media recensioni: %.2f (%d recensione/i)\n",
                       catalogo[i].media_voti, catalogo[i].num_recensioni);
            } else {
                printf("Nessuna recensione presente.\n");
            }
            printf("--------------------------\n");
            trovati++;
        }
    }

    if (trovati == 0) {
        printf("Nessun videogioco trovato corrispondente al criterio inserito.\n");
    }
}








// La funzione aggiungiRecensione() permette all'utente di aggiungere una recensione
// a un videogioco specifico. Cerca il videogioco nel file, poi richiede voto e descrizione.
// Alla fine, aggiorna la media dei voti e riscrive il record aggiornato nel file.
void aggiungiRecensione() {
    // Apro il file del catalogo in modalità lettura/scrittura binaria.
    FILE *file = fopen(FILE_CATALOGO, "rb+");
    if (!file) {
        printf("Errore apertura file.\n");
        return;
    }

    // Richiedo all'utente il titolo del videogioco per cui inserire la recensione.
    char titolo[MAX_TITOLO];
    printf("Inserisci il titolo del videogioco per mettere la recensione: ");
    scanf(" %[^\n]", titolo);

    Videogioco_t gioco;
    int trovato = 0;  // Flag per verificare se il videogioco è stato trovato nel file.

    // Scorro il file record per record fino a trovare il videogioco con il titolo inserito.
    while (fread(&gioco, sizeof(Videogioco_t), 1, file)) {
        if (strcmp(gioco.titolo, titolo) == 0) {
            trovato = 1;
            // Reposiziono il puntatore all'inizio del record corrente per poterlo riscrivere.
            fseek(file, - (long) sizeof(Videogioco_t), SEEK_CUR);

            // Verifico se è possibile aggiungere un'altra recensione (rispetto al massimo ammesso).
            if (gioco.num_recensioni < MAX_RECENSIONI) {
                int voto;
                // Richiedo all'utente di inserire un voto valido (0-5), con possibilità di annullare (-1).
                do {
                    printf("Inserisci voto (0-5), oppure -1 per annullare: ");
                    scanf("%d", &voto);
                    if (voto == -1) {
                        // Se l'utente annulla, chiudo il file e termino la funzione.
                        printf("Operazione annullata.\n");
                        fclose(file);
                        return;
                    }
                    if (voto < 0 || voto > 5) {
                        printf("Voto non valido. Deve essere tra 0 e 5.\n");
                    }
                } while (voto < 0 || voto > 5);

                // Assegno il voto valido alla nuova recensione.
                gioco.recensioni[gioco.num_recensioni].voto = voto;

                // Consumo eventuali newline rimasti nel buffer.
                getchar();

                // Richiedo una descrizione per la recensione (input opzionale).
                printf("Inserisci descrizione (opzionale): ");
                fgets(gioco.recensioni[gioco.num_recensioni].descrizione, MAX_DESC, stdin);
                // Rimuovo il newline finale se presente.
                gioco.recensioni[gioco.num_recensioni].descrizione[strcspn(gioco.recensioni[gioco.num_recensioni].descrizione, "\n")] = '\0';

                // Incremento il numero di recensioni per il videogioco.
                gioco.num_recensioni++;

                // Aggiorno la media dei voti per il videogioco.
                aggiornaMediaRecensioni(&gioco);

                // Riscrivo il record modificato nel file.
                fwrite(&gioco, sizeof(Videogioco_t), 1, file);
                printf("Recensione aggiunta con successo.\n");
            } else {
                // Se il numero massimo di recensioni è già stato raggiunto, informo l'utente.
                printf("Numero massimo di recensioni raggiunto.\n");
            }
            break;  // Uscita dal ciclo una volta elaborato il videogioco trovato.
        }
    }

    if (!trovato) {
        // Se il videogioco non è stato trovato nel file, stampo un messaggio informativo.
        printf("Videogioco non trovato.\n");
    }

    fclose(file);  // Chiudo il file per liberare le risorse.
}








// La funzione modificaRecensione() consente di modificare una recensione esistente per un videogioco.
// Dopo aver cercato il videogioco, mostra all'utente le recensioni disponibili, permette la selezione
// e quindi richiede il nuovo voto e la nuova descrizione, aggiornando infine la media dei voti.
void modificaRecensione() {
    // Apro il file in modalità lettura/scrittura binaria.
    FILE *file = fopen(FILE_CATALOGO, "rb+");
    if (!file) {
        printf("Errore apertura file.\n");
        return;
    }

    // Richiedo il titolo del videogioco per cui si intende modificare una recensione.
    char titolo[MAX_TITOLO];
    printf("Inserisci il titolo del videogioco di cui vuoi modificare la recensione: ");
    scanf(" %[^\n]", titolo);

    Videogioco_t gioco;
    int trovato = 0;

    // Scorro il file record per record per trovare il videogioco.
    while (fread(&gioco, sizeof(Videogioco_t), 1, file)) {
        if (strcmp(gioco.titolo, titolo) == 0) {
            trovato = 1;
            // Reposiziono il puntatore per poter riscrivere il record aggiornato.
            fseek(file, (long long) -sizeof(Videogioco_t), SEEK_CUR);

            if (gioco.num_recensioni > 0) {
                // Visualizzo le recensioni disponibili con indice e dettagli.
                printf("Recensioni disponibili:\n");
                for (int i = 0; i < gioco.num_recensioni; i++) {
                    printf("%d. Voto: %d - %s\n", i, gioco.recensioni[i].voto, gioco.recensioni[i].descrizione);
                }

                int index;
                // Richiedo all'utente l'indice della recensione da modificare, con validazione dell'input.
                do {
                    printf("Inserisci il numero della recensione da modificare (0-%d): ", gioco.num_recensioni - 1);
                    scanf("%d", &index);
                    if (index < 0 || index >= gioco.num_recensioni) {
                        printf("Numero recensione non valido.\n");
                    }
                } while (index < 0 || index >= gioco.num_recensioni);

                int voto;
                // Richiedo il nuovo voto con controllo di validità (tra 0 e 5).
                do {
                    printf("Inserisci nuovo voto (0-5): ");
                    scanf("%d", &voto);
                    if (voto < 0 || voto > 5) {
                        printf("Voto non valido. Deve essere tra 0 e 5.\n");
                    }
                } while (voto < 0 || voto > 5);

                // Aggiorno il voto della recensione selezionata.
                gioco.recensioni[index].voto = voto;
                // Richiedo e salvo la nuova descrizione per la recensione.
                printf("Inserisci nuova descrizione: ");
                scanf(" %[^\n]", gioco.recensioni[index].descrizione);

                // Aggiorno la media dei voti dopo la modifica.
                aggiornaMediaRecensioni(&gioco);

                // Riscrivo il record aggiornato nel file.
                fwrite(&gioco, sizeof(Videogioco_t), 1, file);
                printf("Recensione modificata. Media aggiornata: %.2f\n", gioco.media_voti);
            } else {
                // Se il videogioco non ha recensioni, non c'è nulla da modificare.
                printf("Nessuna recensione da modificare.\n");
            }
            break;
        }
    }

    if (!trovato) {
        // Se il videogioco non viene trovato, informo l'utente.
        printf("Videogioco non trovato.\n");
    }

    fclose(file);  // Chiudo il file per liberare le risorse.
}







// La funzione aggiornaMediaRecensioni() calcola la media dei voti per un videogioco.
// Se non ci sono recensioni, imposta la media a 0; altrimenti somma tutti i voti e calcola la media.
void aggiornaMediaRecensioni(Videogioco_t *gioco) {
    if (gioco->num_recensioni == 0) {
        // Se non ci sono recensioni, la media dei voti è 0.
        gioco->media_voti = 0.0f;
        return;
    }

    int somma_voti = 0;  // Variabile per contenere la somma dei voti.
    for (int i = 0; i < gioco->num_recensioni; i++) {
        somma_voti += gioco->recensioni[i].voto;
    }

    // Calcolo la media dividendo la somma dei voti per il numero di recensioni.
    gioco->media_voti = (float)somma_voti / gioco->num_recensioni;
    printf("Media delle recensioni aggiornata: %.2f\n", gioco->media_voti);
}







// Funzione: acquistaVideogioco
// Descrizione: La funzione permette all'utente di registrare l'acquisto di un videogioco.
// Legge dal file "catalogo.dat" i record dei videogiochi e, se trova quello richiesto,
// incrementa il campo "copie_vendute" per quel videogioco e riscrive il record aggiornato.
void acquistaVideogioco() {
    // Apro il file "catalogo.dat" in modalità "rb+" (lettura e scrittura in binario)
    FILE *file = fopen("catalogo.dat", "rb+");
    if (!file) {
        // Se il file non si apre, stampo un messaggio di errore e termino la funzione
        printf("Errore apertura file.\n");
        return;
    }

    // Richiedo all'utente il titolo del videogioco da acquistare
    char titolo[MAX_TITOLO];
    printf("Inserisci il titolo del videogioco da acquistare: ");
    scanf(" %[^\n]", titolo);

    Videogioco_t gioco;  // Variabile per contenere temporaneamente il record letto dal file
    int trovato = 0;   // Flag per verificare se il videogioco è stato trovato nel file

    // Scorro il file record per record
    while (fread(&gioco, sizeof(Videogioco_t), 1, file)) {
        // Confronto il titolo del videogioco corrente con quello inserito dall'utente
        if (strcmp(gioco.titolo, titolo) == 0) {
            trovato = 1;  // Segno che il videogioco è stato trovato

            // Riporto il puntatore del file all'inizio del record attuale per poterlo riscrivere
            fseek(file, (long long) -sizeof(Videogioco_t), SEEK_CUR);

            // Incremento il numero di copie vendute
            gioco.copie_vendute++;

            // Riscrivo il record aggiornato nel file
            fwrite(&gioco, sizeof(Videogioco_t), 1, file);

            // Comunico all'utente che l'acquisto è stato registrato con successo
            printf("Acquisto registrato! Ora '%s' ha %d copie vendute.\n", gioco.titolo, gioco.copie_vendute);
            break;
        }
    }

    // Se il videogioco non è stato trovato nel file, lo informo all'utente
    if (!trovato) {
        printf("Videogioco non trovato nel catalogo.\n");
    }

    // Chiudo il file per liberare le risorse
    fclose(file);
}







// Funzione: menu_principale
// Descrizione: Visualizza il menu principale per selezionare il ruolo: Amministratore, Visitatore oppure Esci.
void menu_principale() {
    int ruolo;
    do {
        printf("\n--- MENU PRINCIPALE ---\n");
        printf("1. Amministratore\n");
        printf("2. Visitatore\n");
        printf("3. Esci\n");
        printf("Seleziona il tuo ruolo: ");
        scanf("%d", &ruolo);

        switch (ruolo) {
            case 1:
                menu_amministratore();
                break;
            case 2:
                menu_visitatore();
                break;
            case 3:
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida.\n");
        }
    } while (ruolo != 3);
}







// Funzione: menu_amministratore
// Descrizione: Mostra le funzionalità disponibili per l’amministratore del catalogo.
void menu_amministratore() {
    int scelta;
    do {
        printf("\n--- MENU AMMINISTRATORE ---\n");
        printf("1. Inizializza catalogo\n");
        printf("2. Visualizza catalogo\n");
        printf("3. Aggiungi videogioco\n");
        printf("4. Modifica videogioco\n");
        printf("5. Ricerca videogioco\n");
        printf("6. Esci\n");
        printf("Inserisci scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                inizializzaCatalogo();
                break;
            case 2:
                visualizzaCatalogo();
                break;
            case 3:
                aggiungiVideogioco();
                break;
            case 4:
                modificaVideogioco();
                break;
            case 5:
                ricercaVideogioco();
                break;
            case 6:
                printf("Uscita dal menu amministratore.\n");
                break;
            default:
                printf("Scelta non valida. Riprova.\n");
        }
    } while (scelta != 6);
}







// Funzione: menu_visitatore
// Descrizione: Mostra le opzioni disponibili per il visitatore del catalogo.
void menu_visitatore() {
    int scelta;
    do {
        printf("\n--- MENU VISITATORE ---\n");
        printf("1. Visualizza catalogo\n");
        printf("2. Ricerca videogioco\n");
        printf("3. Ordina catalogo\n");
        printf("4. Aggiungi recensione\n");
        printf("5. Acquista videogioco\n");
        printf("6. Modifica recensione\n");
        printf("7. Esci\n");
        printf("Inserisci scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                visualizzaCatalogo();
                break;
            case 2:
                ricercaVideogioco();
                break;
            case 3:
                menu_ordinamento_catalogo();
                break;
            case 4:
                aggiungiRecensione();
                break;
            case 5:
                acquistaVideogioco();
                break;
            case 6:
                modificaRecensione();
                break;
            case 7:
                printf("Uscita dal menu visitatore.\n");
                break;
            default:
                printf("Scelta non valida. Riprova.\n");
        }
    } while (scelta != 7);
}







// Funzione: menu_ordinamento_catalogo
// Descrizione: Permette di scegliere un criterio di ordinamento per il catalogo.
void menu_ordinamento_catalogo() {
    int scelta;
    do {
        printf("\n--- SOTTOMENU ORDINA CATALOGO ---\n");
        printf("1. Ordina per media voti (crescente)\n");
        printf("2. Ordina per copie vendute (crescente)\n");
        printf("3. Esci\n");
        printf("Inserisci scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                ordinamentoPunteggio();
                break;
            case 2:
                ordinamentoCopieVendute();
                break;
            case 3:
                printf("Ritorno al menu precedente.\n");
                break;
            default:
                printf("Scelta non valida. Riprova.\n");
        }
    } while (scelta != 3);
}







// Funzione: ordinamentoPunteggio
// Descrizione: Ordina il catalogo dei videogiochi (caricato in un array) in base alla media dei voti
// delle recensioni in ordine crescente. Se il catalogo è vuoto, informa l'utente.
void ordinamentoPunteggio() {
    // Dichiaro un array di Videogioco che può contenere fino a MAX_VIDEOGIOCHI elementi.
    Videogioco_t catalogo[MAX_VIDEOGIOCHI];

    // La funzione caricaCatalogo() legge i record dal file e li salva nell'array 'catalogo'.
    // Restituisce il numero di record letti.
    int count = caricaCatalogo(catalogo);

    // Se il catalogo è vuoto, stampo un messaggio e termino l'esecuzione della funzione.
    if (count == 0) {
        printf("Catalogo vuoto.\n");
        return;
    }

    // Applico l'algoritmo bubble sort per ordinare i videogiochi in base alla media dei voti.
    // Confronto l'elemento corrente con il successivo, e se l'elemento corrente ha una media maggiore,
    // scambio i due elementi.
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (catalogo[j].media_voti > catalogo[j + 1].media_voti) {
                // Scambio di due record: usiamo una variabile temporanea per salvare l'elemento corrente.
                Videogioco_t temp = catalogo[j];
                catalogo[j] = catalogo[j + 1];
                catalogo[j + 1] = temp;
            }
        }
    }

    // Visualizzo il catalogo ordinato in base alla media dei voti.
    // Ad ogni iterazione, stampo il titolo del videogioco e la sua media di voti.
    printf("\n--- CATALOGO ORDINATO PER MEDIA VOTI (CRESCENTE) ---\n");
    for (int i = 0; i < count; i++) {
        printf("Titolo: %s\n", catalogo[i].titolo);
        printf("Media recensioni: %.2f\n", catalogo[i].media_voti);
        printf("----------------------------------------------------\n");
    }
}

/*
 * Funzione: ordinamentoCopieVendute
 * Descrizione: Ordina l'array dei videogiochi in base al campo copie_vendute
 *              (numero di copie vendute) in ordine crescente e visualizza il catalogo ordinato.
 */






// Ordina il catalogo dei videogiochi in base al numero di copie vendute
// utilizzando l'algoritmo Bubble Sort. Dopo l'ordinamento, stampa il catalogo in ordine crescente.
void ordinamentoCopieVendute() {
    // Dichiaro un array che potrà contenere fino a MAX_VIDEOGIOCHI elementi.
    Videogioco_t catalogo[MAX_VIDEOGIOCHI];

    // Carico il catalogo dal file nel nostro array.
    // La funzione caricaCatalogo() restituisce il numero di record letti dal file.
    int count = caricaCatalogo(catalogo);

    // Se non sono stati letti record, comunico che il catalogo è vuoto e termino la funzione.
    if (count == 0) {
        printf("Catalogo vuoto.\n");
        return;
    }

    // Applico l'algoritmo bubble sort per ordinare i videogiochi in base a copie_vendute.
    // Il ciclo esterno controlla quante volte effettuare il passaggio
    for (int i = 0; i < count - 1; i++) {
        // Il ciclo interno confronta coppie di elementi adiacenti e li scambia se non sono in ordine.
        for (int j = 0; j < count - 1 - i; j++) {
            // Se il numero di copie vendute del videogioco corrente è maggiore
            // di quello del videogioco successivo, eseguo lo scambio dei due record.
            if (catalogo[j].copie_vendute > catalogo[j + 1].copie_vendute) {
                Videogioco_t temp = catalogo[j];       // Salvo il record corrente in una variabile temporanea.
                catalogo[j] = catalogo[j + 1];         // Sposto l'elemento successivo nella posizione corrente.
                catalogo[j + 1] = temp;                // Posiziono il record originale nella posizione successiva.
            }
        }
    }

    // Visualizzazione del catalogo ordinato: per ogni videogioco stampo il titolo e il numero di copie vendute.
    printf("\n--- CATALOGO ORDINATO PER COPIE VENDUTE (CRESCENTE) ---\n");
    for (int i = 0; i < count; i++) {
        printf("Titolo: %s\n", catalogo[i].titolo);
        printf("Copie vendute: %d\n", catalogo[i].copie_vendute);
        printf("----------------------------------------------------\n");
    }
}
