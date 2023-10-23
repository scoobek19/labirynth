#include "matrix_manager.h"


/*
 * Tworzy now� macierz bez wyzerowania element�w.
 *
 * Przyjmuje ilo�� rz�d�w i kolumn.
 * Zwraca wska�nik na now� macierz (Matrix *).
 */
Matrix *stworz_macierz_malloc(int w, int k) {
    macierz *maci = malloc(sizeof *maci);
    maci->w=w;
    maci->k=k;
    maci->mac = malloc(w * sizeof *maci->mac);
    for (int i = 0; i < w; i++)
        maci->mac[i] = malloc(k * sizeof **maci->mac);
    return maci;
}

/*
 * Tworzy now� macierz z wyzerowanymi elementami.
 *
 * Przyjmuje ilo�� rz�d�w i kolumn.
 * Zwraca wska�nik na now� macierz (Matrix *).
 */
Matrix stworz_macierz_calloc(int w, int k) {
    Matrix *maci = malloc(sizeof *maci);
    maci->w=w;
    maci->k=k;
    maci->mac = malloc(w * sizeof *maci->mac);
    for (int i = 0; i < w; i++)
        maci->mac[i] = calloc(k , sizeof **maci->mac);
    return maci;
}


/*
 * Wypisuje na FILE* macierz.
 *
 * Przyjmuje wska�niki na: plik/strumie� i macierz.
 */
void wyp_mac(FILE *out, macierz *mac2) {
    fprintf(out,"\t\t");
    for (int i = 0; i < mac2->k; i++)
        fprintf(out,"%d\t",i);
    fprintf(out, "\n\t----");
    for (int i = 0; i < mac2->k; i++)
        fprintf(out,"----");
    fprintf(out,"\n");
    for (int i = 0; i < mac2->w; i++) {
        fprintf(out,"%d\t|\t",i);
        for (int j = 0; j < mac2->k; j++)
            fprintf(out,"%d\t", mac2->mac[i][j]);
        fprintf(out,"\n");
    }
}

/*
 * Szuka w zbiorze kraw�dzi maksymalnego ID w�z�a w grafie.
 *
 * Przyjmuje zbi�r kraw�dzi.
 * Zwraca maksymalne ID w�z�a.
 */
int max_wierz(kraw kraw2) {
    int max_wie = -1;
    for (int i = 0; i < kraw2.rozm; i++) {
        if (kraw2.zawa[i].pocz > max_wie)
            max_wie = kraw2.zawa[i].pocz;
        if (kraw2.zawa[i].kon > max_wie)
            max_wie = kraw2.zawa[i].kon;
    }
    return max_wie;
}


/*
 * Generuje macierz s�siedztwa.
 *
 * Przyjmuje zbi�r kraw�dzi.
 * Zwraca wska�nik na macierz.
 */
macierz *stworz_mac_sas(kraw kraw2) {

int wierzch2=max_wierz(kraw2)+1;
    /*int **adjacency_matrix = (int **) malloc(vertex_cnt * sizeof *adjacency_matrix);
    for (int i = 0; i < vertex_cnt; i++)
        adjacency_matrix[i] = (int *) calloc(vertex_cnt, sizeof **adjacency_matrix);
*/
    macierz *mac_sas= stworz_mac_calloc(wierzch2, wierzch2);

    for (int i = 0; i < kraw2.size; i++)
        mac_sas->mat[kraw2.zawa[i].pocz][kraw2.zawa[i].kon] = 1;

    return mac_sas;
}

/*
 * Generuje macierz incydencji.
 *
 * Przyjmuje zbi�r kraw�dzi grafu.
 * Zwraca wska�nik na macierz.
 */
Matrix *stworz_mac_inc(kraw kraw2) {
    int wierzch2=max_wierz(kraw2)+1;
    /*int **incidence_matrix = (int **) malloc(vertex_cnt * sizeof *incidence_matrix);
    for (int i = 0; i < vertex_cnt; i++)
        incidence_matrix[i] = (int *) calloc(edges.size, sizeof **incidence_matrix);
*/
    Matrix *mac_inc= stworz_macierz_calloc(wierzch2, kraw2.rozm);

    for (int i = 0; i < kraw2.rozm; i++) {
        if (kraw2.zawa[i].pocz == kraw2.zawa[i].kon) {
            max_inc>mac[kraw2.zawa[i].pocz][i] = 2;
            continue;
        }
        mac_inc->mac[kraw2.zawa[i].pocz][i] = 1;
        mac_inc->mac[kraw2.zawa[i].kon][i] = -1;
    }


    return mac_inc;
}

