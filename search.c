#include "search.h"
#include "edges_lib.h"
#include "labyrinth_manager.h"


/*
 * Dodaje do œcie¿ki.
 *
 * Przyjmuje ID nowego elementu i wskaŸnik na œcie¿kê.
 */
void dodaj_sek(int dar, sek_t *sek) {
    if (sek->rozm++ == 0)
        sek->zawa = malloc(sizeof *sek->zawa);
    else
    sek->zawa = realloc(sek->zawa, sek->rozm * sizeof *sek->zawa;
    sek->zawa[sek->rozm - 1] = dar;
}

/*
 * Dodaje œcie¿kê do zbioru œcie¿ek.
 *
 * Przyjmuje wskaŸniki: na nowy element, na zbiór sekwencji oraz wartoœæ sumy wag krawêdzi scie¿ki.
 */
void dodaj_do_sek_db(sek_t *dar, sek_db *sekdb, double suma_wag) {
    if (sekdb->rozm++ == 0) {
        sekdb->zawa = malloc(sizeof **sekdb->zawa);
        sekdb->suma_wag = malloc(sizeof *sekdb->suma_wag);
    } else {
        sekdb->zawa = realloc(sekdb->zawa, sekdb->rozm * sizeof **sekdb->zawa);
        sekdb->suma_wag = realloc(sekdb->suma_wag, sekdb->rozm * sizeof *sekdb->suma_wag);
    }
    sekdb->zawa[sekdb->rozm - 1] = dar;
    sekdb->suma_wag[sekdb->rozm - 1] = suma_wag;
}

/*
 * Duplikuje sekwencjê - œciezkê.
 *
 * Przyjmuje sequence_t* do zduplikowania.
 * Zwraca w pe³ni skopiowany element sequence_t* (deep copy).
 */
sequence_t *dupl_sek(sek_t *sek_do_dupl) {
    sek_t *nowa_s = malloc(sizeof *nowa_s);
    nowa_s->rozm = sek_do_dupl->rozm;
    nowa_s->zawa = malloc(sek_do_dupl->size * sizeof *nowa_s->zawa);
    for (int i = 0; i < sek_do_dupl->rozm; i++)
        nowa_s->zawa[i] = sek_do_dupl->zawa[i];
    return nowa_s;
}


/*
 * Szuka s¹siadów.
 *
 * Przyjmuje ID elementu dla którego ma znaleŸæ s¹siadów i wskaŸnik an macierz s¹siedztwa.
 * Zwraca (sequence_t *){->size=n}, dla n elementów.
 */
sequence_t *szuk_sas(int to, macierz *mac_sas) {

    sek_t *znaj = malloc(sizeof *znaj);
    znaj->rozm = 0;
    for (int i = 0; i < mac_sas->k; i++)
        if (mac_sas->mac[to][i] == 1)
            dodaj_sek(i, znaj);
    return znaj;
}


/* Sprawdza czy element jest elementem koñcowym w labiryncie wyjœciem z niego.
 *
 * Przyjmuje ID elementu, wskaŸnika na labirynt.
 * Korzysta z globalnej zmiennej labiryntu.
 * Zwraca:
 * 1 - je¿eli jest to ostatni element.
 * 0 - w przeciwnym wypadku
 */
int czy_kon(int to, labirynt_t *lab) {
    int praw_z = to % 10;
    to = to / 10;//this==real_r
    if (lab->zawa[to * 2 + 2][praw_z * 2 + 1] == 3)
        return 1;
    return 0;
}

/*
 * Sprawdza czy dany element istnieje w œcie¿ce.
 *
 * Przyjmuje ID elementu i wskaŸnik na œcie¿kê.
 * Zwraca:
 * 1 - je¿eli istnieje
 * 0 - je¿eli nie istnieje
 */
int czy_ist_sek(int to, sek_t *sek) {
    for (int i = 0; i < sek->rozm; i++)
        if (sek->zawa[i] == to)
            return 1;
    return 0;
}


/*
 * Sumuje wagê (d³ugoœæ) œcie¿ki.
 *
 * Przyjmuje wskaŸniki na: œcie¿kê, zbiór krawêdzi.
 * Zwraca wagê.
 */
double suma_wag1(sek_t *sek, kraw *kraw2) {
    double suma = 0;
    for (int i = 0; i < sek->rozm - 1; i++)
        suma += dod_waga((krawedz_t) {.pocz=sek->zawa[i], .kon=sek->zawa[i + 1]}, kraw2);
    return suma;
}

/*
 * Generalnie DFS przyjmuje dotychczasow¹ sekwencjê i kolejny element.
 * Idzie do ka¿dego nieodwiedzonego w sequence s¹siada.
 *
 * Dodaje œcie¿kê do zbioru œcie¿ek je¿eli nie ma ¿adnych wiêciej s¹siadów, lub dotar³ do koñcowego.
 *
 * Przyjmuje wskaŸnik na dotychczasow¹ œcie¿kê, ID kolejnego elementu, wskaŸniki na: zbiór krawêdzi, macierz s¹siedztwa, zbiór œcie¿ek wynikowych.
 * */
void DFS(sek_t *sek, int nast, kraw *kraw2, macierz *mac_sas, labirynt_t *lab, sek_db *droga) {
    dodaj_sek(nast, sek);
    sek_t *sas = szuk_sas(nast, mac_sas);
    if (czy_kon(nast, lab) == 0)  {//posiada s¹siadów
        for (int i = 0; i < adjacent->size; i++)
            if (czy_ist_sek(sas->zawa[i], sek) == 0)
                DFS(dupl_sek(sek), sas->zawa[i], kraw2, mac_sas, lab, droga);


    } else {//s¹siadów nie ma
        dodaj_do_sek_db(sek, droga, suma_wag1(sek, kraw2));

    }

}

/*
 * Inicjuje dzia³anie algorytmu DFS.
 *
 * Przyjmuje ID pierwszej pozycji, wskaŸniki na: zbiór krawêdzi, macierz s¹siedztwa, labirynt, zbiór œcie¿ek wynikowych.
 */
void DFS_roz(int start, kraw *kraw2, macierz *mac_sas, labirynt_t *lab, sek_db *droga) {
    sek_t *sek = malloc(sizeof *sek);
    sek->rozm = 0;
    DFS(sek, start, kraw2, mac_sas, lab, droga);
}
