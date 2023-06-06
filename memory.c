#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void unosProizvoda(ARTIKL* skladiste, int* brojProizvoda) {
	FILE* fp = NULL;
	fp = fopen("skladiste.txt", "w+");
	if (fp == NULL) {
		perror("Otvaranje datoteke 'skladiste.txt' u unosProizvoda()");
		exit(1);
	}

	for (int i = 0; i < *brojProizvoda; ++i) {
		fprintf(fp, "%d %s %f %d %c\n", skladiste[i].id, skladiste[i].ime, skladiste[i].cijena, skladiste[i].zaliha, skladiste[i].kategorija);
	}

	fclose(fp);
}

ARTIKL* noviProizvod(ARTIKL* skladiste, int* brojProizvoda, char ime[20], float* cijena, int* zaliha, char* kategorija) {
	*brojProizvoda += 1;
	skladiste = (ARTIKL*)realloc(skladiste, *brojProizvoda * sizeof(ARTIKL));
	if (skladiste == NULL) {
		perror("Realociranje memorije za skladiste u unosProizvoda()");
		exit(1);
	}

	skladiste[*brojProizvoda - 1].id = *brojProizvoda - 1;
	for (int i = 0; i < 20; i++) {
		skladiste[*brojProizvoda - 1].ime[i] = ime[i];
	}
	skladiste[*brojProizvoda - 1].cijena = *cijena;
	skladiste[*brojProizvoda - 1].zaliha = *zaliha;
	skladiste[*brojProizvoda - 1].kategorija = *kategorija;

	FILE* fp = NULL;
	fp = fopen("skladiste.txt", "a");
	if (fp == NULL) {
		perror("Otvaranje datoteke 'skladiste.txt' u unosProizvoda()");
		exit(1);
	}

	fprintf(fp, "%d %s %f %d %c\n", skladiste[*brojProizvoda - 1].id, skladiste[*brojProizvoda - 1].ime, skladiste[*brojProizvoda - 1].cijena, skladiste[*brojProizvoda - 1].zaliha, skladiste[*brojProizvoda - 1].kategorija);

	fclose(fp);

	return skladiste;
}

void upisatiUSkladiste(ARTIKL* skladiste, int* brojProizvoda) {
	FILE* fp = NULL;
	fp = fopen("skladiste.txt", "w+");

	for (int i = 0; i < *brojProizvoda; ++i) {
		fprintf(fp, "%d %s %f %d %c\n", skladiste[i].id, skladiste[i].ime, skladiste[i].cijena, skladiste[i].zaliha, skladiste[i].kategorija);
	}

	fclose(fp);
}

KOSARICA* dodajUKosaru(ARTIKL* artikl, int* kolicina, KOSARICA* kosarica, int* brojArtikalaUKosarici) {
	if (*brojArtikalaUKosarici == 0) {
		(*brojArtikalaUKosarici)++;
		kosarica = (KOSARICA*)malloc(sizeof(KOSARICA));
		kosarica->id = artikl->id;
		for (int i = 0; i < 20; ++i) {
			kosarica->ime[i] = artikl->ime[i];
		}
		kosarica->kolicina = *kolicina;
		kosarica->cijena = *kolicina * artikl->cijena;
	}
	else {
		(*brojArtikalaUKosarici)++;
		kosarica = (KOSARICA*)realloc(kosarica, *brojArtikalaUKosarici * sizeof(KOSARICA));
		if (kosarica == NULL) {
			perror("Realociranje memorije za kosaricu u dodajUKosaru()");
			exit(1);
		}
		kosarica[*brojArtikalaUKosarici - 1].id = artikl->id;
		for (int i = 0; i < 20; ++i) {
			kosarica[*brojArtikalaUKosarici - 1].ime[i] = artikl->ime[i];
		}
		kosarica[*brojArtikalaUKosarici - 1].kolicina = *kolicina;
		kosarica[*brojArtikalaUKosarici - 1].cijena = *kolicina * artikl->cijena;
	}

	return kosarica;
}

ARTIKL* razdvojiKategoriju(char c, int* brojProizvoda, ARTIKL* skladiste, int* brojRazdvojenih) {
	ARTIKL* temp = (ARTIKL*)malloc(sizeof(ARTIKL));

	for (int i = 0; i < *brojProizvoda; ++i) {
		if (skladiste[i].kategorija == c) {
			temp = (ARTIKL*)realloc(temp, (i + 1) * sizeof(ARTIKL));
			temp[*brojRazdvojenih] = skladiste[i];
			(*brojRazdvojenih)++;
		}
	}
	
	return temp;
}

ARTIKL* preuzimanjeSkladista(int* brojProizvoda) {
	FILE* fp = NULL;
	fp = fopen("skladiste.txt", "r");
	if (fp == NULL) {
		perror("Otvaranje skladista u preuzimanjeSkladista()");
		exit(1);
	}

	ARTIKL* skladiste = NULL;
	skladiste = (ARTIKL*)malloc(sizeof(ARTIKL));
	if (skladiste == NULL) {
		perror("Zauzimanje memorije za skladiste u preuzimanjeSkladista()");
		exit(1);
	}

	int status = 0;
	int i = 1;

	while ((status = fscanf(fp, "%d %s %f %d %c", &skladiste[i - 1].id, &skladiste[i - 1].ime, &skladiste[i - 1].cijena, &skladiste[i - 1].zaliha, &skladiste[i - 1].kategorija)) != EOF) {
		++i;
		(*brojProizvoda)++;

		skladiste = realloc(skladiste, i * sizeof(ARTIKL));
		if (skladiste == NULL) {
			perror("Realociranje memorije za skladiste u preuzimanjeSkladista()");
		}
	}

	return skladiste;
}