/*Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
A. dinamièki dodaje novi element na poèetak liste,
B. ispisuje listu,
C. dinamièki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[20];
	char surname[20];
	int birthYear;
	Position next;
} Person;


Position kreiranjeOsobe() {
	Position newPerson = NULL;
	char name[20] = " ";
	char surname[20] = " ";
	int birthYear = 0;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Krivo alociranje memorije\n");
		exit(1);
	}

	printf("Unesite ime:\n");
	scanf(" %s", name);
	printf("Unesite prezime:\n");
	scanf(" %s", surname);
	printf("Unesite godinu rodenja:\n");
	scanf(" %d", &birthYear);

	//moramo sa strcpy jer kopiramo sadrzaj ne adrese pokazivaca
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;

	return newPerson;
}

int unosNaPocetak(Position p) {
	Position newPerson = NULL;

	newPerson = kreiranjeOsobe();

	if (newPerson != NULL) {
		newPerson->next = p->next;
		p->next = newPerson;
	}

	return 0;
}

int PrintList(Position p) {
	printf("\nIspis\n");
	printf("-------------\n");
	for (; p != NULL; p = p->next) {
		printf("Name: %s\t Surname: %s\t Birth year: %d\t\n", p->name, p->surname, p->birthYear);
	}
	printf("-------------\n");
	return 0;
}

int unosNaKraj(Position p) {
	Position newPerson = NULL;

	newPerson = kreiranjeOsobe();

	if (newPerson != NULL) {
		while (p->next != NULL) {
			p = p->next;
		}
		newPerson->next = p->next;
		p->next = newPerson;
	}

	return 0;
}

int trazi(Position p, char* prezime) {

	while (p != NULL && strcmp(p->surname, prezime) != 0) {
		p = p->next;
	}
	printf("\nPronadena osoba\n");
	printf("-------------\n");
	printf("Name: %s\t Surname: %s\t Birth year: %d\t\n", p->name, p->surname, p->birthYear);
	printf("-------------\n");
	return 0;
}

int brisanje(Position p, char* prezime) {
	Position prev = NULL;

	while (p->next != NULL && strcmp(p->surname, prezime) != 0) {
		//strcmp vraca 0 ako su dva ista chara 
		prev = p;
		p = p->next;
	}

	//printf("%s", prev->name); ovde ispisuje onoga sta ocemo izbacit

	if (p != NULL) {
		prev->next = p->next;
		free(p);
		printf("Obrisano\n");
	}

	return 0;
}

int main()
{
	Person Head = { .next = NULL, .name = " ", .surname = " ", .birthYear = 0 };

	//TESTIRANJE
	//unosNaPocetak(&Head);
	//unosNaKraj(&Head);
	//unosNaKraj(&Head);
	//unosNaPocetak(&Head);
	//PrintList(Head.next);

	//char prezime[20] = " ";
	//printf("Unesite prezime osobe koje zelite pronaci i izbrisati iz liste\n");
	//scanf(" %s", prezime);

	//trazi(&Head, prezime);
	//brisanje(&Head, prezime);
	//PrintList(Head.next);

	unosNaPocetak(&Head);
	unosNaKraj(&Head);
	unosNaPocetak(&Head);
	unosNaKraj(&Head);
	PrintList(Head.next);

	char prezime[20] = " ";
	printf("Unesite prezime osobe koje zelite pronaci\n");
	scanf(" %s", prezime);
	trazi(&Head, prezime);

	printf("Unesite prezime osobe koje zelite izbrisati\n");
	scanf(" %s", prezime);
	brisanje(&Head, prezime);

	PrintList(Head.next);

	return 0;
}