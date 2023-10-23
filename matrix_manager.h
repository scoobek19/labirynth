#include "edges_lib.h"
#include <stdlib.h>


typedef struct {
    int **mac;
    int w;
    int k;
} macierz;


macierz *stworz_mac_malloc(int w, int k) ;

macierz *stworz_mac_calloc(int w, int k) ;

macierz *stworz_mac_inc(kraw kraw2);

macierz *stworz_mac_sas(kraw kraw2);

void wyp_mac(FILE *out, Matrix *ptr);

