#include <stdlib.h>
#include "matrix_manager.h"
#include "labyrinth_manager.h"

typedef struct {
    int *zawa;
    int rozm;
} sek_t;

typedef struct{
    sek_t **zawa;
    double *suma_wag;
    int rozm;
} sek_db;

void DFS_roz(int start, kraw *kraw2, macierz *mac_sas, labirynt_t * lab, sek_db *droga);

