#include <stdlib.h>
#include "labyrinth_manager.h"

#define max_rozm 21 //czyli w naszej notacji 10x10



/*
 * Czyta labirynt z pliku.
 *
 * Przyjmuje wska�nik na otwarty plik (FILE *)
 * Zwraca:
 * lab_t.real_size!=-1 - powodzenie
 * lab_t.real_size==-1 - nieznany znak (!= ' ', #, P, K, '\n')
 */
lab_t czyt_lab(FILE *plik) {
    labirynt_t lab;
    lab.praw_rozm=-1;
    lab.zawa = malloc(max_rozm * sizeof *lab.zawa);
    for (int i = 0; i < max_rozm; i++)
        lab.zawa[i] = calloc(max_rozm, sizeof **lab.zawa);
    int linia= 0, znak = 0;


    char c;
    while ((c = fgetc(plik)) != EOF) {
        switch (c) {
            case ' ':
                lab.zawa[linia][znak] = 0;
                break;
            case '#':
                lab.zawa[linia][znak] = 1;
                break;
            case 'P':
                lab.zawa[linia][znak] = 2;
                break;
            case 'K':
                lab.zawa[linia][znak] = 3;
                break;
            case '\n':
                linia++;
                if(lab.praw_rozm==-1){
                    lab.praw_rozm=(znak-1)/2;
                    lab.rozm_2=znak;
                }
                znak = 0;
                continue;
            default:
                return (labirynt_t){.praw_rozm=-1};
        }
        znak++;
    }
    if (c == EOF)
        linia++;

   // lab.raw_size = linec;
    //lab.real_size = (linec - 1) / 2;
    return lab;

}


/*
 * Przeszukuje wg��b graf, dodaje kraw�dzie do zbioru.
 *
 * Przyjmuje rz�d w labiryncie, kolumn� (zakres 0-9), ID poprzedniego elementu i wska�niki na: zbi�r kraw�dzi i labirynt.
 */
void dodaj(int praw_r, int praw_z, int praw_wcze, labirynt_t *lab, kraw *kraw2) {


    int praw2 = 10 * praw_r + praw_z;
    int praw3 = praw_r * 2 + 1;
    int praw4 = praw_z * 2 + 1;
    int praw_nast;
    if (praw_wcze != -99)
        if(dod_kra_los(praw_wcze, praw2, kraw2)==2)
            return;

    praw_nast = praw2 - 10;
    if (praw_r != 0 && lab->zawa[praw3 - 1][praw4] == 0 && praw_nast != praw_wcze) //go up
        dodaj(praw_r - 1, praw_z, praw2, lab, kraw2);

    praw_nast = praw2 + 10;
    if (praw_r != lab->praw_rozm - 1 && lab->zawa[praw3 + 1][praw4] == 0 && praw_nast != praw_wcze)  //go down
        dodaj(praw_r + 1, praw_z, praw2, lab, kraw2);

    praw_nast = praw2 - 1;
    if (praw_z != 0 && lab->zawa[praw3 ][praw4 - 1] == 0 && praw_nast != praw_wcze) //go left
        dodaj(praw_r, praw_z - 1, praw2, lab, kraw2);

    praw_nast = praw2 + 1;
    if (praw_z != lab->praw_rozm - 1 && lab->zawa[praw3 ][praw4 + 1] == 0 && praw_nast != praw_wcze) //go right
        dodaj(praw_r, praw_z + 1, praw2, lab, kraw2);


}

/*
 * Rozpoczyna prac� poszukiwania kraw�dzi.
 * Poszukuje pierwszej pozycji po literze 'P' w linii zerowej.
 *
 * Przyjmuje wska�niki na: labirynt i zbi�r kraw�dzi.
 * Zwraca:
 * 0 - powowdzenie
 * 1 - brak pozycji pocz�tkowej
 */
int rozp(labirynt_t *lab, kraw *kraw2){
    int linia=-1;
    for(int i=0; i < lab->praw_rozm; i++)
        if(lab->zawa[0][2 * i + 1] == 2){
            linia=i;
            break;
        }
    if(linia==-1)
        return 1;
    lab->pocz=linia;
    add(0, lab->pocz -99, lab, kraw2);
    return 0;
}
