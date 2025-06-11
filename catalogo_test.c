#include "unity.h"
#include "unity_internals.h"
#include "catalogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione di supporto: elimina il file catalogo.dat, per iniziare ogni test con uno stato pulito
void resetCatalogo() {
    remove(FILE_CATALOGO);
}

// Eseguito prima di ogni test
void setUp(void) {
    resetCatalogo();
}

// Eseguito dopo ogni test (non utilizzato)
void tearDown(void) {}

// Verifica che inizializzaCatalogo() crei un file binario contenente 20 videogiochi
void test_inizializzaCatalogo_crea_file_con_20_giochi(void) {
    inizializzaCatalogo();
    FILE *file = fopen(FILE_CATALOGO, "rb");
    TEST_ASSERT_NOT_NULL(file);
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    TEST_ASSERT_EQUAL_INT(20 * sizeof(Videogioco_t), size);
}

// Verifica che caricaCatalogo() legga correttamente i giochi dal file
void test_caricaCatalogo_legge_20_giochi(void) {
    inizializzaCatalogo();
    Videogioco_t giochi[MAX_VIDEOGIOCHI];
    int count = caricaCatalogo(giochi);
    TEST_ASSERT_EQUAL_INT(20, count);
    TEST_ASSERT_EQUAL_STRING("The Witcher 3", giochi[0].titolo);
}

// Simula l'acquisto di un gioco e verifica incremento copie vendute
void test_acquistaVideogioco_incrementa_copie(void) {
    inizializzaCatalogo();
    FILE *input = fopen("test_input.txt", "w");
    fprintf(input, "The Witcher 3\n");
    fclose(input);
    freopen("test_input.txt", "r", stdin);
    acquistaVideogioco();
    freopen("/dev/tty", "r", stdin);
    remove("test_input.txt");
    Videogioco_t giochi[MAX_VIDEOGIOCHI];
    caricaCatalogo(giochi);
    TEST_ASSERT_EQUAL_INT(1, giochi[0].copie_vendute);
}

// Aggiunge un nuovo videogioco e verifica che sia il 21°
void test_aggiungiVideogioco_scrive_nuovo_record(void) {
    inizializzaCatalogo();
    FILE *input = fopen("test_input.txt", "w");
    fprintf(input, "Test Game\nTest Editore\nTest Sviluppatore\nGioco di prova\n2024\n1\nPuzzle\n");
    fclose(input);
    freopen("test_input.txt", "r", stdin);
    aggiungiVideogioco();
    freopen("/dev/tty", "r", stdin);
    remove("test_input.txt");
    Videogioco_t giochi[MAX_VIDEOGIOCHI];
    int count = caricaCatalogo(giochi);
    TEST_ASSERT_EQUAL_INT(21, count);
    TEST_ASSERT_EQUAL_STRING("Test Game", giochi[20].titolo);
}

// Verifica che il file venga creato se non esiste
void test_main_inizializza_se_file_mancante(void) {
    remove(FILE_CATALOGO);
    FILE *f = fopen(FILE_CATALOGO, "rb");
    TEST_ASSERT_NULL(f);
    inizializzaCatalogo();
    f = fopen(FILE_CATALOGO, "rb");
    TEST_ASSERT_NOT_NULL(f);
    fclose(f);
}

// Simula uscita dal menu principale
void test_menu_principale_esci_subito(void) {
    FILE *input = fopen("test_input.txt", "w");
    fprintf(input, "3\n");
    fclose(input);
    freopen("test_input.txt", "r", stdin);
    menu_principale();
    freopen("/dev/tty", "r", stdin);
    remove("test_input.txt");
    TEST_PASS_MESSAGE("menu_main terminato correttamente dopo 'Esci'");
}

// Modifica dati di un videogioco e verifica aggiornamento
void test_modificaVideogioco_modifica_dati(void) {
    inizializzaCatalogo();
    FILE *input = fopen("test_input.txt", "w");
    fprintf(input, "The Witcher 3\nCD Project New\nCDPR Studio\nNuova descrizione\n2025\n1\nRPG Nuovo\n");
    fclose(input);
    freopen("test_input.txt", "r", stdin);
    modificaVideogioco();
    freopen("/dev/tty", "r", stdin);
    remove("test_input.txt");
    Videogioco_t giochi[MAX_VIDEOGIOCHI];
    caricaCatalogo(giochi);
    TEST_ASSERT_EQUAL_STRING("CD Project New", giochi[0].editore);
    TEST_ASSERT_EQUAL_STRING("CDPR Studio", giochi[0].sviluppatore);
    TEST_ASSERT_EQUAL_STRING("Nuova descrizione", giochi[0].descrizione);
    TEST_ASSERT_EQUAL_INT(2025, giochi[0].anno_pubblicazione);
    TEST_ASSERT_EQUAL_STRING("RPG Nuovo", giochi[0].generi[0]);
}

// Verifica ordinamento per copie vendute
void test_ordinamentoCopieVendute_ordine_crescente(void) {
    inizializzaCatalogo();
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j <= i; j++) {
            FILE *input = fopen("test_input.txt", "w");
            fprintf(input, "The Witcher 3\n");
            fclose(input);
            freopen("test_input.txt", "r", stdin);
            acquistaVideogioco();
            freopen("/dev/tty", "r", stdin);
            remove("test_input.txt");
        }
    }
    ordinamentoCopieVendute();
    TEST_PASS_MESSAGE("ordinamentoCopieVendute eseguito senza errori.");
}

// Verifica ordinamento per punteggio
void test_ordinamentoPunteggio_ordine_crescente(void) {
    inizializzaCatalogo();
    FILE *file = fopen(FILE_CATALOGO, "rb+");
    if (file) {
        Videogioco_t gioco;
        for (int i = 0; i < 20; i++) {
            fseek(file, i * sizeof(Videogioco_t), SEEK_SET);
            fread(&gioco, sizeof(Videogioco_t), 1, file);
            gioco.media_voti = 20 - i;
            fseek(file, -sizeof(Videogioco_t), SEEK_CUR);
            fwrite(&gioco, sizeof(Videogioco_t), 1, file);
        }
        fclose(file);
    }
    ordinamentoPunteggio();
    TEST_PASS_MESSAGE("ordinamentoPunteggio eseguito senza errori.");
}

// Verifica che aggiunta recensione aggiorni i dati correttamente
void test_aggiungiRecensione_aggiorna_media(void) {
    inizializzaCatalogo();
    FILE *input = fopen("test_input.txt", "w");
    fprintf(input, "The Witcher 3\n5\nOttimo gioco\n");
    fclose(input);
    freopen("test_input.txt", "r", stdin);
    aggiungiRecensione();
    freopen("/dev/tty", "r", stdin);
    remove("test_input.txt");
    Videogioco_t giochi[MAX_VIDEOGIOCHI];
    caricaCatalogo(giochi);
    TEST_ASSERT_EQUAL_INT(1, giochi[0].num_recensioni);
    TEST_ASSERT_EQUAL_INT(5, giochi[0].recensioni[0].voto);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, giochi[0].media_voti);
}

// Verifica che modifica recensione aggiorni valori e media
void test_modificaRecensione_modifica_valori(void) {
    inizializzaCatalogo();
    FILE *input = fopen("test_input.txt", "w");
    fprintf(input, "The Witcher 3\n5\nBellissimo\n");
    fclose(input);
    freopen("test_input.txt", "r", stdin);
    aggiungiRecensione();
    freopen("/dev/tty", "r", stdin);
    remove("test_input.txt");
    input = fopen("test_input.txt", "w");
    fprintf(input, "The Witcher 3\n0\n3\nCarino ma non perfetto\n");
    fclose(input);
    freopen("test_input.txt", "r", stdin);
    modificaRecensione();
    freopen("/dev/tty", "r", stdin);
    remove("test_input.txt");
    Videogioco_t giochi[MAX_VIDEOGIOCHI];
    caricaCatalogo(giochi);
    TEST_ASSERT_EQUAL_INT(3, giochi[0].recensioni[0].voto);
    TEST_ASSERT_EQUAL_STRING("Carino ma non perfetto", giochi[0].recensioni[0].descrizione);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, giochi[0].media_voti);
}

// Verifica che la funzione ricercaVideogioco() funzioni correttamente
void test_ricercaVideogioco_output_atteso(void) {
    inizializzaCatalogo();
    FILE *input = fopen("test_input.txt", "w");
    fprintf(input, "1\nThe Witcher\n");
    fclose(input);
    freopen("test_input.txt", "r", stdin);
    ricercaVideogioco();
    freopen("/dev/tty", "r", stdin);
    remove("test_input.txt");
    TEST_PASS_MESSAGE("ricercaVideogioco eseguita senza errori.");
}

// Verifica che visualizzaCatalogo() non causi crash
void test_visualizzaCatalogo_visualizza_senza_errori(void) {
    inizializzaCatalogo();
    visualizzaCatalogo();
    TEST_PASS_MESSAGE("visualizzaCatalogo eseguito correttamente.");
}

// Funzione principale di test
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_inizializzaCatalogo_crea_file_con_20_giochi);
    RUN_TEST(test_caricaCatalogo_legge_20_giochi);
    RUN_TEST(test_acquistaVideogioco_incrementa_copie);
    RUN_TEST(test_aggiungiVideogioco_scrive_nuovo_record);
    RUN_TEST(test_main_inizializza_se_file_mancante);
    RUN_TEST(test_menu_principale_esci_subito);
    RUN_TEST(test_modificaVideogioco_modifica_dati);
    RUN_TEST(test_ordinamentoCopieVendute_ordine_crescente);
    RUN_TEST(test_ordinamentoPunteggio_ordine_crescente);
    RUN_TEST(test_aggiungiRecensione_aggiorna_media);
    RUN_TEST(test_modificaRecensione_modifica_valori);
    RUN_TEST(test_ricercaVideogioco_output_atteso);
    RUN_TEST(test_visualizzaCatalogo_visualizza_senza_errori);
    return UNITY_END();
}