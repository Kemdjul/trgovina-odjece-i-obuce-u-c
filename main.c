#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "structures.h"

int main() {
	int status = 1;
	int *brojProizvoda = 0;
	ARTIKL* skladiste = preuzimanjeSkladista(&brojProizvoda);

	do {
		program(&status);
	} while (status != 0);

	return 0;
}