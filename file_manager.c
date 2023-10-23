#include "file_manager.h"

/*
 * Otwiera plik z definicj� obiektu
 *
 * Przyjmuje: liczb� argument�w wywow�ania i ich zawarto�� tekstow�.
 * Zwraca:
 * FILE * - powodzenie
 * NULL - niepowowdzenie
 */
FILE *ot_plik(int argc, char **argv){
    if (argc < 2) {
        printf("Za mala liczba argumentow - podaj sciezke do pliku z definicja obiektu.\n");
        return NULL;
    }
    FILE *in = fopen(argv[1], "r");

    if (in == NULL) {
        printf("Nie udalo sie otworzyc pliku: %s\n", argv[1]);
        return NULL;
    }
    return in;

}
