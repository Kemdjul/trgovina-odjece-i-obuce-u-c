#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

void pretraziPoKategoriji() {}
void pretraziPoImenu() {}
void kosarica() {}

void guestMenu() {
	printf("Dobrodosli, 'guest'.  Za pregled artikala, odaberite izbor 1 ili 2. Za isplatu kosarice, odaberite 3. Za izlaz iz programa, odaberite 4.\n\n");
	printf("1. Pretrazivanje po kategorijama\n2. Pretrazivanje po imenu\n3. Pregled kosarice\n4. Izlaz\n");

	int izbor = 0;

	do {
		scanf(" %d", &izbor);
		if (izbor < 1 || izbor > 4) {
			system("clear");
			printf("Krivi unos. Molim vas da ponovno unesete zeljeni izbor.\n");
			printf("1. Pretrazivanje po kategorijama\n2. Pretrazivanje po imenu\n3. Pregled kosarice\n4. Izlaz\n");
		}
	} while (izbor < 1 || izbor > 4);

	switch (izbor) {
	case 1: pretraziPoKategoriji(); break;
	case 2: pretraziPoImenu(); break;
	case 3: kosarica(); break;
	default: return;
	}
}

void program(int* status) {
	printf("-------------------------------------\nDobrodosli u trgovinu\n-------------------------------------\n");
	printf("Odaberite nacin prijave unosenjem broja pored izbora\n\n");
	printf("1. Guest\n2.Admin\n");

	int izbor = 0;
	do {
		scanf(" %d", &izbor);

		if (izbor < 1 || izbor > 2) {
			system("clear");
			printf("Krivi unos. Odaberite ponovno.\n\n");
			printf("Odaberite nacin prijave unosenjem broja pored izbora\n\n");
			printf("1. Guest\n2. Admin\n");
		}
	} while (izbor < 1 || izbor > 2);

	if (izbor == 1) {
		system("clear");
		guestMenu();
	}

	*status = 0;
}