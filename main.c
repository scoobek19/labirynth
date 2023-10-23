#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "labyrinth_manager.h"
#include "search.h"
#include "file_manager.h"


int main(int argc, char **argv) {

    srand(time(NULL));

    //Otwarcie pliku
    FILE *in = open_file(argc, argv);
    if (in == NULL)
        return 4;

    labirynt_t lab;

    //Czytanie labiryntu z pliku
    if ((lab = czyt_lab(in)).praw_rozm == -1)
        return 2;


    //Wykrywanie kraw�dzi
    kraw *kraw2 = malloc(sizeof *kraw2);
    kraw2->rozm = 0;
    if (rozp(&lab, kraw2) == 1) {
        printf("Brak pozycji pocz�tkowej!");
        return 3;
    }

    //Generowanie macierzy s�siedztwa
   macierz *mac_sas = stworz_mac_sas(*kraw2);

    sek_db *droga = malloc(sizeof *droga);
    droga->rozm = 0;

    //Wyszukiwanie �cie�ek algorytmem DFS
    DFS_roz(lab.pocz, kraw2, mac_sas, &lab, droga);

    int krotk = -1;

    //Wyszukanie najkr�tszej �cie�ki pod wzgl�dem sumy wag kraw�dzi.
    for (int i = 0; i < droga->rozm; i++)
        if (krotk == -1)
            krotk = i;
        else if (droga->suma_wag[i] < droga->suma_wag[krotk])
            krotk = i;

    //Wypisanie najkr�tszej �cie�ki
    if (krotk == -1) {
        puts("Nie znaleziono sciezek!\nMozliwe jest ze nie zdefiniowano punktu koncowego 'K'.");
        return 1;
    } else {
        printf("NAJKR�TSZA:\nP > ");
        for (int i = 0; i < droga->zawa[krotk]->rozm; i++)
            printf("%d > ", droga->zawa[krotk]->rozm[i]);
        printf("K\t(Suma: %g)\n", droga->suma_wag[krotk]);
    }

    return 0;
}


