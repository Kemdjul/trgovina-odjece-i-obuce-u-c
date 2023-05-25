#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

ARTIKL* preuzimanjeSkladista(int** brojProizvoda) {
	FILE* fp = NULL;
	fp = fopen("skladiste.txt", "r");
	if (fp == NULL) {
		perror("Otvaranje skladista u preuzimanjeSkladista()");
		exit(1);
	}

	ARTIKL* temp = (ARTIKL*)malloc(sizeof(ARTIKL));

	int status = 0;
	int i = 1;

	while ((status = fscanf(fp, "%d %s %f %d", &temp[i - 1].id, &temp[i - 1].ime, &temp[i - 1].cijena, &temp[i - 1].zaliha)) != EOF) {
		++i;

		temp = realloc(temp, i * sizeof(ARTIKL));
		if (temp == NULL) {
			perror("Realociranje memorije u preuzimanjeSkladista()");
			exit(1);
		}
	}

	return temp;
}