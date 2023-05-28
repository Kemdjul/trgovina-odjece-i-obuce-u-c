#ifndef MEMORY_H
#define MEMORY_H
#include "structures.h"

ARTIKL* preuzimanjeSkladista(int* brojProizvoda);
ARTIKL* razdvojiKategoriju(char c, int* brojProizvoda, ARTIKL* skladiste, int* brojRazdvojenih);
KOSARICA* dodajUKosaru(artikl, kolicina, kosarica, brojArtikalaUKosarici);
void upisatiUSkladiste(ARTIKL* skladiste, int* brojProizvoda);
ARTIKL* unosProizvoda(ARTIKL* skladiste, int* brojProizvoda, char ime[20], float* cijena, int* zaliha, char* kategorija);

#endif