# Imposta la versione minima richiesta di CMake
cmake_minimum_required(VERSION 3.31)

# Imposta l'output degli eseguibili (runtime) nella cartella sorgente
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Specifica lo standard del C (in questo caso C11)
set(CMAKE_C_STANDARD 11)


add_executable(CARTELLA_PROGETTO
        main.c
        catalogo.h
        catalogo.c  # Aggiunto per il corretto linking: contiene le definizioni di funzioni fondamentali
)

add_executable(test
        catalogo_test.c
        unity.h
        unity.c
        unity_internals.h
        catalogo.h
        catalogo.c
)