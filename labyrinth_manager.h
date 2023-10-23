#include "edges_lib.h"

typedef struct {
    int **zawa;
    int praw_rozm;
    int rozm_2;
    int pocz;
} labirynt_t;



labirynt_t czyt_lab(FILE *plik);

int rozp(labirynt_t *lab, kraw *kraw2);


void lab_do_kra(int **labirynt, int p_rozm, kraw *krawi);
