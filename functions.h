#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"

void program(int* status, ARTIKL* skladiste, int* brojProizvoda, KOSARICA* kosarica, int* brojArtikalaUKosarici);
void guestMenu(ARTIKL* skladiste, int* brojProizvoda, int* status, KOSARICA* kosarica, int* brojArtikalaUKosarici);
KOSARICA* listaProizvoda(ARTIKL* skladiste, int* brojProizvoda, char c, KOSARICA* kosarica, int* brojArtikalaUKosarici);
KOSARICA* oProizvodu(ARTIKL* artikl, KOSARICA* kosarica, int* brojArtikalaUKosarici);
KOSARICA* prikaziKosaricu(KOSARICA* kosarica, int* brojArtikalaUKosarici, ARTIKL* skladiste, int* brojProizvoda);
ARTIKL* adminMenu(ARTIKL* skladiste, int* brojProizvoda, int* status);
ARTIKL* dodajProizvod(ARTIKL* skladiste, int* brojProizvoda);

#endif