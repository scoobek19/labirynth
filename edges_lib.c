#include <stdlib.h>
#include "edges_lib.h"

extern int modul;

/*
 * Wypisuje dane o kraw�dziach.
 *
 * Przyjmuje wska�nik na strumie� i na zbi�r kraw�dzi, liczb� w�z��w i kraw�dzi.
 */
void wydruk_zawa(FILE *out, krawedz_t *kraw2, int wierzch2, int kraw1) {
    printf("V = %d, E = %d\n", wierzch2, kraw1);
    for (int i = 0; i < kraw1; i++)
        printf("E[%d] = %d -> %d; w = %g\n", i, kraw2[i].pocz, kraw2[i].kon, kraw2[i].waga);
    printf("\n");
}

/*
 * Wczytuje list� kraw�dzi z pliku w formacie:
 * Najpierw definiujemy liczb� wierzcho�k�w a p�niej kraw�dzi: <V> <E>\n
 * Nast�pnie definiujemy krawedzie w grafie w formacie: <1-wiercho�ek> <2-wierzcho�ek> [waga]\n
 * Kolejno�� podawania wierzcho�k�w ma znaczenie, gdy� taki b�dzie kierunek w sgrafie.
 * Kolejne kraw�dzie oddzielamy \n
 * Wa�ne, aby dla n wierzcho�k�w u�ywa� indeks�w {0, 1, ..., n-1}.
 * Wszystkie podawane liczby musz� by� ca�kowite, w zakresie |x|<=INT_MAX
 * Oraz ich liczba musi by� <= INT_MAX
 * Waga nal�y wpisa� je�eli random!=1.
 *
 * Przyjmuje wska�nik na strumie�, liczb� kraw�dzi, w�z��w i random - 1 - losowe wagi, 0 - zdefiniowane
 * Zwraca:
 * edge_t* - powowdzenie
 * NULL - niepowowdzenie
 */
krawedz_t *zal_kraw(FILE *plik, int *krw, int *wierzch, int los) {
    double chw;
    int licznik2 = 0, licznik = 0, licz = 0;
    krawedz_t *krw2 = malloc(sizeof *krw2);
    while (fscanf(plik, "%lf", &chw) != EOF) {
        switch (licz) {
            case 0:
                *wierzch = (int) chw;
                licz++;
                continue;
            case 1:
                *krw = (int) chw;
                licz++;
                continue;
        }


        switch (licznik2) {
            case 0:
                krw2 = realloc(krw2, (licznik + 1) * sizeof *krw2);
                krw2[licznik].pocz = (int) chw;
                licznik2++;
                break;
            case 1:
                krw2[licznik].kon = (int) chw;
                if (los == 1) {
                    licznik2 = 0;
                    krw2[licznik].waga = (double) rand() / RAND_MAX * 10.0;
                    licznik++;
                } else
                    licznik2++;
                break;
            case 2:
                krw2[licznik].waga = chw;
                licznik2 = 0;
                licznik++;      //zwi�kszenie ilo�ci kraw�dzi nast�puje jedynie je�eli wczytano wszystkie 3 warot�ci
                break;
            default:
                fprintf(stderr, "Nastapil blad w czytaniu danych (switch).\n");
                return NULL;
        }
        licz++;
    }
    return krw2;
}

//Zwraca: 0 - nie istnieje, 1 - istnieje (nie dodajemy), 2 - istnieje odwrotna (dodajemy z t� sam� wag�)
/*
 * Sprawdza czy w zbiorze kraw�dzi istanieje podana kraw�d�.
 *
 * Przyjmuje: kraw�d� i wska�nik na zbi�r kraw�dzi.
 * Zwraca:
 * 0 - nie istnieje
 * 1 - istnieje identyczna (nie nale�y dodawa�)
 * 2 - istnieje odwrotna (nale�y skopiowa� wag�)
 */
int czy_ist(krawedz_t kra, krawedz_t *kraw2) {
    int ident = 0;
    for (int i = 0; i < kraw2->rozm; i++)
        if (kraw2->zawa[i].pocz == kra.pocz && kraw2->zawa[i].kon == kra.kon) //1 - istnieje identyczna
            return 1;
        else if (kraw2->zawa[i].pocz == kra.kon && kraw2->zawa[i].kon == kra.pocz) //istnieje odwrotna
            ident = 1;

    return ident == 1 ? 2 : 0;
}


/*
 * Zwraca wag� kraw�dzi.
 *
 * Przyjmuje kraw�d� i wska�nik na zbi�r kraw�dzi.
 * Zwraca:
 * wag� do w/w kraw�dzi - powodzenie
 * -1 - niepowodzenie
 */
double dod_waga(krawedz_t krawedz, kraw *kraw2) {
    for (int i = 0; i < kraw2->size; i++)
        if (kraw2->zawa[i].pocz == krawedz.pocz && kraw2->zawa[i].kon == krawedz.kon)
            return kraw2->zawa[i].waga;
    return -1;
}


/*
 * Zwraca wag� odwrotnej kraw�dzi.
 *
 * Przyjmuje kraw�d� i wska�nik na zbi�r kraw�dzi.
 * Zwraca:
 * powodzenie - wag� do kraw�dzi odwrotnej do w/w
 * -1 - niepowodzenie
 */
double odwr_krw(krawedz_t kraw, kraw *kraw2) {
    return wez_waga((krawedz_t) {.pocz=kraw.kon, .kon=kraw.pocz}, kraw2);
}


/*
 * Dodaje now� kraw�d� do zbioru kraw�dzi, przy okzaji generuj�c losow� wag� (0,10)
 *
 * Przyjmuje: w�ze� pocz�tkowy i ko�cowy, wska�nik na zbi�r kraw�dzi
 * Zwraca:
 * 0 - powowdzenie
 * 2 - istnieje identyczna
 */
int dod_kra_los(int od, int do2, kraw *kraw2) {

    krawedz_t krawe = {.pocz=od, .kon=do2, .waga=(double) rand() / RAND_MAX * 10.0};
if (modul==1) {
    printf("%d -> %d (", od, do2);
}
    switch (czy_ist(krawe, kraw2)) {
        case 0: //nie istnieje, czyli nic nie zmieniamy w edge
if (modul==1) {
            printf("Nie istnieje - 0) (Waga: %g)\n", krawe.waga);
}
            break;
        case 1: //istnieje identyczna, czyli wychodzimy z f()
if (modul==1) {
            printf("Identyczna - 1) (Waga: %g)\n", krawe.waga);
}
            return 2;
        case 2: //istnieje odwrotna, czyli kopiujemy weight
            krawe.waga = odwr_krw(krawe, kraw2);
if (modul==1) {
            printf("Odwrotna - 2) (Waga: %g)\n", krawe.weight);
}
            break;
    }



    kraw2->rozm++;
    if (kraw2->rozm == 1)
        kraw2->zawa = malloc(sizeof *kraw2->zawa);
    else
        kraw2->zawa = realloc(kraw2->zawa, kraw2->rozm * sizeof *kraw2->zawa);

    kraw2->zawa[kraw2->rozm - 1] = ;
    return 0;
}
