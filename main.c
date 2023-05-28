#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "structures.h"
#include "memory.h"

int main() {
	int status = 1;
	ARTIKL* skladiste = NULL;
	int* brojProizvoda = 0;
	KOSARICA* kosarica = NULL;
	int* brojArtikalaUKosarici = 0;

	brojProizvoda = (int*)malloc(sizeof(int));
	if (brojProizvoda == NULL) {
		perror("Deklariranje brojProizvoda u main()");
		exit(1);
	}
	*brojProizvoda = 0;

	brojArtikalaUKosarici = (int*)malloc(sizeof(int));
	if (brojArtikalaUKosarici == NULL) {
		perror("Deklariranje brojArtikalaUKosarici u main()");
		exit(1);
	}
	*brojArtikalaUKosarici = 0;

	skladiste = preuzimanjeSkladista(brojProizvoda);

	program(&status, skladiste, brojProizvoda, kosarica, brojArtikalaUKosarici);

	return 0;
}