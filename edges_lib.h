#include <stdio.h>

typedef struct krawedz {
    int pocz;
    int kon;
    double waga;
} krawedz_t;

typedef struct{
    krawedz_t *zawa;
    int rozm;
} kraw;

void wydruk_zawa(FILE *out, krawedz_t *kraw2, int wierzch2, int kraw1);

krawedz_t *zal_kraw(FILE *plik, int *krw, int *wierzch, int los);

int dod_kra_los(int od, int do2, kraw *kraw2);

double dod_waga(krawedz_t krawedz, kraw *kraw2);


