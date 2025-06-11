#include <stdio.h>
#include "catalogo.h"  // Per inizializzaCatalogo() e FILE_CATALOGO

int main() {
    // Verifica se il file del catalogo esiste utilizzando il macro FILE_CATALOGO
    FILE *file = fopen(FILE_CATALOGO, "rb");
    if (!file) {
        // Se il file non esiste, inizializza il catalogo
        inizializzaCatalogo();
        printf("Catalogo inizializzato.\n");
    } else {
        fclose(file);
    }

    menu_principale(); // Avvia il menu principale
    return 0;
}