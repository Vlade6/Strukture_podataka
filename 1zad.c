#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>

/* Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

typedef struct {
	char ime[20];
	char prezime[20];
	int bodovi;
}student;

int brojStudenata() {
	int brojStudenata = 0;
	FILE* fp;
	fp = fopen("TextFile1.txt", "r");
	while (!feof(fp)) {
		if (fgetc(fp) == '\n') {
			brojStudenata++;
		}
	}
	printf("broj studenata je %d", brojStudenata);
	fclose(fp);

	return brojStudenata;
}

student* alokacijaMemorijeCitanje(int brojStd) {
	FILE* fp = NULL;
	student* studenti = NULL;
	int counter = 0;

	studenti = (student*)malloc(brojStd * sizeof(student));

	if (studenti == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		exit(1);
	}

	fp = fopen("TextFile1.txt", "r");
	if (fp == NULL) {
		printf("Neuspjesno otvaranje datoteke!\n");
		exit(1);
	}
	while (!feof(fp)) {
		fscanf(fp, " %s %s %lf", studenti[counter].ime, studenti[counter].prezime, &studenti[counter].bodovi);
		counter++;
	}

	fclose(fp);

	return studenti;
}

int brojBodova(int bodovi) {
	return bodovi / 20 * 100;
}

void ispis(student* studenti, int brojStudenata) {
	for (int i = 0; i < brojStudenata; i++) {
		printf("\nIme studenta: %s\nPrezime studenta: %s\nBroj bodova: %d", studenti[i].ime, studenti[i].prezime, brojBodova(studenti[i].bodovi));
	}
}

int main()
{
	student* studenti;
	int brojStd = 0;

	brojStd = brojStudenata();

	studenti = alokacijaMemorijeCitanje(brojStd);

	ispis(studenti, brojStd);

	return 0;
}