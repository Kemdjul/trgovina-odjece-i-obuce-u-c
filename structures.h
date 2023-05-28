#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
	int id;
	char ime[20];
	float cijena;
	int zaliha;
	char kategorija;
}ARTIKL;

typedef struct {
	int id;
	char ime[20];
	int kolicina;
	float cijena;
}KOSARICA;

#endif