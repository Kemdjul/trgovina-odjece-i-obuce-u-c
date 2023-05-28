#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "memory.h"

ARTIKL* adminOProizvodu(ARTIKL* skladiste, int** brojProizvoda, int id) {
	int izbor = 0;
	int i = 0;
	
	for (i = 0; i < **brojProizvoda; ++i) {
		if (skladiste[i].id == id) break;
	}

	do {
		printf("-----------------------------------------------------------------------------\n");
		printf("\t\t\tDobrodosli, guest\n");
		printf("-----------------------------------------------------------------------------\n\n");
		printf("Ime proizvoda: %s\n", skladiste[i].ime);
		printf("Cijena: %.2fe\n", skladiste[i].cijena);
		printf("Na zalihi: %d\n", skladiste[i].zaliha);
		printf("Opis proizvoda: \n\n");
		printf("1. Dodaj u kosaricu\n2.Izlaz\n");

		scanf(" %d", &izbor);
		if (izbor < 1 || izbor > 2) {
			system("cls");
			printf("Krivi unos, pokušajte ponovno.\n\n");
		}
	} while (izbor < 1 || izbor > 2);

	system("cls");

	return skladiste;
}

ARTIKL* adminListaProizvoda(ARTIKL* skladiste, int* brojProizvoda, char c) {
	int odabirProizvoda = 0;

	do {
		int brojRazvrstanih = 0;
		ARTIKL* razvrstani = NULL;
		razvrstani = razdvojiKategoriju(c, brojProizvoda, skladiste, &brojRazvrstanih);
		printf("-----------------------------------------------------------------------------\n");
		printf("\t\t\tDobrodosli, admin\n");
		printf("-----------------------------------------------------------------------------\n\n");

		switch (c) {
		case 'g': printf("Ponudjeni gornji dijelovi:\n\n"); break;
		case 'd': printf("Ponudjeni donji dijelovi:\n\n"); break;
		case 'o': printf("Ponudjena obuca:\n\n"); break;
		}

		for (int i = 0; i < brojRazvrstanih; ++i) {
			printf("%d. %s %.2fe\n", razvrstani[i].id, razvrstani[i].ime, razvrstani[i].cijena);
		}

		printf("-1. Natrag\n");

		scanf(" %d", &odabirProizvoda);

		if (odabirProizvoda == -1) {
			return skladiste;
		}

		for (int i = 0; i < brojRazvrstanih; ++i) {
			if (razvrstani[i].id == odabirProizvoda) {
				system("cls");
				skladiste = adminOProizvodu(skladiste, &brojProizvoda, razvrstani[i].id);
				odabirProizvoda = -1;
			}
		}

		if (odabirProizvoda != -1) {
			system("cls");
			printf("Krivi unos, pokusajte ponovno.\n");
		}
	} while (odabirProizvoda != -1);

	return skladiste;
}

ARTIKL* adminPretrazivanjePoKategoriji(ARTIKL* skladiste, int* brojProizvoda) {
	int izbor = 0;

	do {
		printf("-----------------------------------------------------------------------------\n");
		printf("\t\t\tDobrodosli, admin\n");
		printf("-----------------------------------------------------------------------------\n\n");
		printf("Odaberite zeljenu kategoriju.\n\n");
		printf("1. Gornji dio\n2. Donji dio\n3. Obuca\n4. Natrag\n");

		scanf(" %d", &izbor);

		switch (izbor) {
		case 1: system("cls"); skladiste = adminListaProizvoda(skladiste, brojProizvoda, 'g'); break;
		case 2: system("cls"); skladiste = adminListaProizvoda(skladiste, brojProizvoda, 'd'); break;
		case 3: system("cls"); skladiste = adminListaProizvoda(skladiste, brojProizvoda, 'o'); break;
		case 4: system("cls"); break;
		default: printf("Unesite ponovno.\n");
		}

		if (izbor < 1 || izbor > 4) {
			system("cls");
			printf("Krivi unos, pokusajte ponovno.\n");
		}
	} while (izbor < 1 || izbor > 4);

	return skladiste;
}

ARTIKL* dodajProizvod(ARTIKL* skladiste, int* brojProizvoda) {
	char ime[20];
	float cijena = 0.0;
	int zaliha = 0;
	int unos = 0;
	char kategorija;
	printf("-----------------------------------------------------------------------------\n");
	printf("\t\t\tDobrodosli, admin\n");
	printf("-----------------------------------------------------------------------------\n\n");
	printf("Unesite podatke o proizvodu, ili unesite 0 za izlaz.\n");
	
	printf("Naziv proizvoda: ");
	scanf(" %[^\n]s", &ime);

	printf("Cijena proizvoda: ");
	scanf(" %f", &cijena);

	printf("Broj trenutno dostupnog proizvoda: ");
	scanf(" %d", &zaliha);

	printf("Kategorija proizvoda:\n1. Gornji dio\n2. Donji dio\n3. Obuca\n Unesite broj pored zeljene kategorije: ");

	do {
		scanf(" %d", &unos);
		if (unos < 1 || unos > 3) {
			printf("Krivi unos, pokusajte ponovno.\n");
		}
	} while (unos < 1 || unos > 3);

	switch (unos) {
		case 1: kategorija = 'g'; break;
		case 2: kategorija = 'd'; break;
		case 3: kategorija = 'o'; break;
	}

	skladiste = unosProizvoda(skladiste, brojProizvoda, ime, &cijena, &zaliha, &kategorija);

	return skladiste;
}

ARTIKL* adminMenu(ARTIKL* skladiste, int* brojProizvoda, int* status) {
	int izbor = 0;

	do {
		printf("-----------------------------------------------------------------------------\n");
		printf("\t\t\tDobrodosli, admin\n");
		printf("-----------------------------------------------------------------------------\n\n");
		printf("Odaberite radnju:\n\n");
		printf("1. Dodavanje proizvoda\n2. Pretrazivanje po kategoriji\n3. Pretrazivanje po imenu\n4. Izlaz\n");

		scanf(" %d", &izbor);

		switch (izbor) {
		case 1: system("cls"); skladiste = dodajProizvod(skladiste, brojProizvoda); break;
		case 2: system("cls"); skladiste = adminPretrazivanjePoKategoriji(skladiste, brojProizvoda); break;
		case 4: *status = 0;
		default: system("cls"); printf("Krivi unos, pokusajte ponovno.\n"); break;
		}
	} while (*status != 0);
	
	return skladiste;
}

KOSARICA* oProizvodu(ARTIKL* artikl, KOSARICA* kosarica, int* brojArtikalaUKosarici) {
	int izbor = 0;

	do {
		printf("-----------------------------------------------------------------------------\n");
		printf("\t\t\tDobrodosli, guest\n");
		printf("-----------------------------------------------------------------------------\n\n");
		printf("Ime proizvoda: %s\n", artikl->ime);
		printf("Cijena: %.2fe\n", artikl->cijena);
		printf("Na zalihi: %d\n", artikl->zaliha);
		printf("Opis proizvoda: \n\n");
		printf("1. Dodaj u kosaricu\n2.Izlaz\n");

		scanf(" %d", &izbor);
		if (izbor < 1 || izbor > 2) {
			system("cls");
			printf("Krivi unos, pokušajte ponovno.\n\n");
		}
	} while (izbor < 1 || izbor > 2);

	int kolicina = 0;
	if (izbor == 1) {
		do {
			printf("\nKoliko?\n");
			scanf(" %d", &kolicina);

			if (kolicina == -1) {
				system("cls");
				return kosarica;
			}

			else if (kolicina > artikl->zaliha) {
				system("cls");
				printf("Krivi unos, pokusajte ponovno.\n");
			}

		} while (kolicina > artikl->zaliha);

		if (kolicina != -1) {
			kosarica = dodajUKosaru(artikl, &kolicina, kosarica, brojArtikalaUKosarici);
		}
	}

	system("cls");
	return kosarica;
}

KOSARICA* listaProizvoda(ARTIKL* skladiste, int* brojProizvoda, char c, KOSARICA* kosarica, int* brojArtikalaUKosarici) {
	int odabirProizvoda = 0;

	do {
		int brojRazvrstanih = 0;
		ARTIKL* razvrstani = NULL;
		razvrstani = razdvojiKategoriju(c, brojProizvoda, skladiste, &brojRazvrstanih);
		printf("-----------------------------------------------------------------------------\n");
		printf("\t\t\tDobrodosli, guest\n");
		printf("-----------------------------------------------------------------------------\n\n");

		switch (c) {
		case 'g': printf("Ponudjeni gornji dijelovi:\n\n"); break;
		case 'd': printf("Ponudjeni donji dijelovi:\n\n"); break;
		case 'o': printf("Ponudjena obuca:\n\n"); break;
		}

		for (int i = 0; i < brojRazvrstanih; ++i) {
			printf("%d. %s %.2fe\n", razvrstani[i].id, razvrstani[i].ime, razvrstani[i].cijena);
		}

		printf("-1. Natrag\n");

		scanf(" %d", &odabirProizvoda);

		if (odabirProizvoda == -1) {
			return kosarica;
		}

		for (int i = 0; i < brojRazvrstanih; ++i) {
			if (razvrstani[i].id == odabirProizvoda) {
				system("cls");
				kosarica = oProizvodu(&razvrstani[i], kosarica, brojArtikalaUKosarici);
				odabirProizvoda = -1;
			}
		}

		if (odabirProizvoda != -1) {
			system("cls");
			printf("Krivi unos, pokusajte ponovno.\n");
		}
	} while (odabirProizvoda != -1);

	return kosarica;
}

KOSARICA* pretraziPoKategoriji(ARTIKL* skladiste, int* brojProizvoda, KOSARICA* kosarica, int* brojArtikalaUKosarici) {
	int izbor = 0;

	do {
		printf("-----------------------------------------------------------------------------\n");
		printf("\t\t\tDobrodosli, guest\n");
		printf("-----------------------------------------------------------------------------\n\n");
		printf("Odaberite zeljenu kategoriju.\n\n");
		printf("1. Gornji dio\n2. Donji dio\n3. Obuca\n4. Natrag\n");
	
		scanf(" %d", &izbor);

		switch (izbor) {
		case 1: system("cls"); kosarica = listaProizvoda(skladiste, brojProizvoda, 'g', kosarica, brojArtikalaUKosarici); break;
		case 2: system("cls"); kosarica = listaProizvoda(skladiste, brojProizvoda, 'd', kosarica, brojArtikalaUKosarici); break;
		case 3: system("cls"); kosarica = listaProizvoda(skladiste, brojProizvoda, 'o', kosarica, brojArtikalaUKosarici); break;
		case 4: system("cls"); break;
		default: printf("Unesite ponovno.\n");
		}

		if (izbor < 1 || izbor > 4) {
			system("cls");
			printf("Krivi unos, pokusajte ponovno.\n");
		}
	} while (izbor < 1 || izbor > 4);

	return kosarica;
}
KOSARICA* pretraziPoImenu(ARTIKL* skladiste, int* brojProizvoda, KOSARICA* kosarica, int* brojArtikalaUKosarici) {
	printf("-----------------------------------------------------------------------------\n");
	printf("\t\t\tDobrodosli, guest\n");
	printf("-----------------------------------------------------------------------------\n\n");
	printf("Unesite ime trazenog proizvoda (do 20 znakova).\n\n");
	char unos[20];

	scanf(" %s", &unos);

	system("cls");

	printf("-----------------------------------------------------------------------------\n");
	printf("\t\t\tDobrodosli, guest\n");
	printf("-----------------------------------------------------------------------------\n\n");

	printf("Pronadjeni proizvodi:\n\n");

	for (int i = 0; i < *brojProizvoda; ++i) {
		if (strstr(skladiste[i].ime, unos) != NULL) {
			printf("%d. %s %.2fe\n", skladiste[i].id, skladiste[i].ime, skladiste[i].cijena);
		}
	}

	int odabir = 0;
	scanf(" %d", &odabir);

	for (int i = 0; i < *brojProizvoda; ++i) {
		if (skladiste[i].id == odabir) {
			system("cls");
			kosarica = oProizvodu(&skladiste[i], kosarica, brojArtikalaUKosarici);
		}
	}

	return kosarica;
}

KOSARICA* prikaziKosaricu(KOSARICA* kosarica, int* brojArtikalaUKosarici, ARTIKL* skladiste, int* brojProizvoda) { 
	int izbor = 0;
	float ukupno = 0.0;
	KOSARICA* temp = NULL;

	temp = (KOSARICA*)malloc(sizeof(KOSARICA));

	do {
		printf("-----------------------------------------------------------------------------\n");
		printf("\t\t\tDobrodosli, guest\n");
		printf("-----------------------------------------------------------------------------\n\n");

		printf("Vasa kosarica sadrzi:\n\n");
		printf("ID:\tNaziv:\t\tKolicina:\tUkupna cijena:\n");

		for (int i = 0; i < *brojArtikalaUKosarici; ++i) {
			printf("%d.\t%s\t\t%d\t\t%.2fe\n", kosarica[i].id, kosarica[i].ime, kosarica[i].kolicina, kosarica[i].cijena);
			ukupno += kosarica[i].cijena;
		}

		printf("\nUkupno: %.2f\n\n", ukupno);

		printf("\n1. Isplati kosaricu\n2. Mici iz kosarice\n3. Izlaz\n");
		scanf(" %d", &izbor);

		if (izbor < 1 || izbor > 3) {
			system("cls");
			printf("Krivi unos, pokusajte ponovno.\n");
		}
	} while (izbor < 1 || izbor > 3);

	switch (izbor) {
	case 1: {
		do {
			system("cls");
			printf("-----------------------------------------------------------------------------\n");
			printf("\t\t\tDobrodosli, guest\n");
			printf("-----------------------------------------------------------------------------\n\n");

			printf("Ukupan iznos vase kosarice je %.2f. Jeste li sigurni da hocete isplatiti kosaricu?\n\n", ukupno);
			printf("1. Da\n2.Ne\n");

			scanf(" %d", &izbor);
			switch (izbor) {
			case 1: 
				upisatiUSkladiste(skladiste, brojProizvoda);
				kosarica = NULL; 
				*brojArtikalaUKosarici = 0; 
				ukupno = 0; system("cls"); 
				printf("Vasa kosarica je isplacena.\n");
				return kosarica;
			case 2: system("cls"); break;
			default: system("cls"); printf("Krivi unos, pokusajte ponovno.\n"); break;
			}
		} while (izbor < 1 || izbor > 2);
		break;
	};
	case 2: {
		do {
			system("cls");
			printf("-----------------------------------------------------------------------------\n");
			printf("\t\t\tDobrodosli, guest\n");
			printf("-----------------------------------------------------------------------------\n\n");

			printf("Koji artikl zelite ukloniti?");
			for (int i = 0; i < *brojArtikalaUKosarici; ++i) {
				printf("%d. %s\n", kosarica[i].id, kosarica[i].ime);
			}

			scanf(" %d", &izbor);
			for (int i = 0; i < *brojArtikalaUKosarici; ++i) {
				if (izbor == kosarica[i].id) {
					for (int j = i; j < *brojArtikalaUKosarici; ++j) {
						*temp = *(kosarica + j + 1);
						*(kosarica + j + 1) = *(kosarica + j);
						*(kosarica + j) = *temp;
					}

					kosarica = (KOSARICA*)realloc(kosarica, (*brojArtikalaUKosarici - 1) * sizeof(KOSARICA));
					if (kosarica == NULL) {
						perror("Realociranje kosarice u prikaziKosaricu()");
						exit(1);
					}

					*brojArtikalaUKosarici = *brojArtikalaUKosarici - 1;
				}
			} 
		} while (izbor < 0);

		system("cls");
		printf("Artikl uspjesno uklonjen.\n");
		break;
	}
	case 3: system("cls"); free(temp); return kosarica;
	default: break;
	}

	free(temp);
	return kosarica;
}

void guestMenu(ARTIKL* skladiste, int* brojProizvoda, int* status, KOSARICA* kosarica, int* brojArtikalaUKosarici) {
	int izbor = 0;

	do {
		printf("-----------------------------------------------------------------------------\n");
		printf("\t\t\tDobrodosli, guest\n");
		printf("-----------------------------------------------------------------------------\n\n");
		printf("Unosenjem broja pored navedenih opcija odabirate zeljenu radnju.\n\n");
		printf("1. Pretrazivanje po kategorijama\n2. Pretrazivanje po imenu\n3. Pregled kosarice\n4. Izlaz\n");

		scanf(" %d", &izbor);
		if (izbor < 1 || izbor > 4) {
			system("cls");
			printf("Krivi unos. Molim vas da ponovno unesete zeljeni izbor.\n");
		}

		switch (izbor) {
		case 1: system("cls"); kosarica = pretraziPoKategoriji(skladiste, brojProizvoda, kosarica, brojArtikalaUKosarici); break;
		case 2: system("cls"); kosarica = pretraziPoImenu(skladiste, brojProizvoda, kosarica, brojArtikalaUKosarici); break;
		case 3: system("cls"); kosarica = prikaziKosaricu(kosarica, brojArtikalaUKosarici, skladiste, brojProizvoda); break;
		case 4: *status = 0; return;
		default: break;
		}
	} while (status != 0);
}

void program(int* status, ARTIKL* skladiste, int* brojProizvoda, KOSARICA* kosarica, int* brojArtikalaUKosarici) {
	int izbor = 0;

	do {
		printf("-----------------------------------------------------------------------------\n");
		printf("\t\t\tDobrodosli u trgovinu\n");
		printf("-----------------------------------------------------------------------------\n\n");
		printf("Prijavljate se kao:\n\n");
		printf("1. Guest\n2. Admin\n");
	
		scanf(" %d", &izbor);

		if (izbor < 1 || izbor > 2) {
			system("cls");
			printf("Krivi unos. Odaberite ponovno.\n\n");
		}
	} while (izbor < 1 || izbor > 2);

	if (izbor == 1) {
		system("cls");
		guestMenu(skladiste, brojProizvoda, status, kosarica, brojArtikalaUKosarici);
	}
	
	else if (izbor == 2) {
		system("cls");
		adminMenu(skladiste, brojProizvoda, status);
	}
}