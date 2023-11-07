#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct pol polinom;
typedef polinom* Position;
struct pol {
	int coefficient;
	int exponent;
	Position next;
};

int readFromFile(Position head1, Position head2);
void stringIntoList(char* buffer, Position head);
void addSorted(Position head, int coef, int expo);
void printList(Position head1);
void addPolinoms(Position head1, Position head2, Position adding_head);
void multiplyPolinoms(Position head1, Position head2, Position multiplyHead);
 
int main() {
	polinom head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	polinom head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	polinom addingHead = { .coefficient = 0, .exponent = 0, .next = NULL };
	polinom multiplyHead = { .coefficient = 0, .exponent = 0, .next = NULL };

	readFromFile(&head1, &head2);

	printf("First polinom:");
	printList(&head1);

	printf("\nSecond polinom:");
	printList(&head2);

	printf("\nAdded polinoms:");
	addPolinoms(&head1, &head2, &addingHead);
	printList(&addingHead);

	printf("\nMultiplied polinoms:");
	multiplyPolinoms(&head1, &head2, &multiplyHead);
	printList(&multiplyHead);
	return 0;
}


int readFromFile(Position head1, Position head2) {
	FILE* filePointer = NULL;
	filePointer = fopen("polinoms.txt", "r");
	if (!filePointer) {
		printf("ERROR FILE COULD NOT OPEN!");
		return 0;
	}
	char buffer[1024] = { 0 };

	fgets(buffer, 1024, filePointer);
	stringIntoList(buffer, head1);

	fgets(buffer, 1024, filePointer);
	stringIntoList(buffer, head2);

	return 0;
}

void stringIntoList(char* buffer, Position head) {
	char* currentBuffer = buffer;
	int numBytes, coef, expo;

	while (strlen(currentBuffer) > 0) {
		sscanf(currentBuffer, "%dx^%d %n", &coef, &expo, &numBytes);
		addSorted(head, coef, expo);
		currentBuffer += numBytes;
	}
}

void addSorted(Position head, int coef, int expo) {
	Position temp = head->next;
	Position previous = head;
	Position newElement = (Position)malloc(sizeof(polinom));

	newElement->coefficient = coef;
	newElement->exponent = expo;

	while (temp != NULL) {
		if (newElement->exponent > temp->exponent) {
			newElement->next = previous->next;
			previous->next = newElement;
			break;
		}
		else if (newElement->exponent == temp->exponent) {
			temp->coefficient = temp->coefficient + newElement->coefficient;
			free(newElement);
			break;
		}
		temp = temp->next;
		previous = previous->next;
	}
	if (temp == NULL) {
		newElement->next = previous->next;
		previous->next = newElement;
	}
}

void printList(Position head) {
	Position temp = head;

	while (temp->next != NULL) {
		temp = temp->next;
		printf("%dx^%d ", temp->coefficient, temp->exponent);
	}
}

void addPolinoms(Position head1, Position head2, Position addingHead) {
	Position temp;
	Position p1 = head1->next;
	Position p2 = head2->next;

	while (p1 != NULL && p2 != NULL) {
		if (p1->exponent == p2->exponent) {
			addSorted(addingHead, p1->coefficient + p2->coefficient, p1->exponent);
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->exponent > p2->exponent) {
			addSorted(addingHead, p1->coefficient, p1->exponent);
			p1 = p1->next;
		}
		else {
			addSorted(addingHead, p2->coefficient, p2->exponent);
			p2 = p2->next;
		}
	}

	if (p1 != NULL) {
		temp = p1;
	}
	else {
		temp = p2;
	}
	while (temp != NULL) {
		addSorted(addingHead, temp->coefficient, temp->exponent);
		temp = temp->next;
	}
}

void multiplyPolinoms(Position head1, Position head2, Position multiplyHead) {
	Position p1, p2;
	for (p1 = head1->next; p1 != NULL; p1 = p1->next) {
		for (p2 = head2->next; p2 != NULL; p2 = p2->next) {
			addSorted(multiplyHead, p1->coefficient * p2->coefficient, p1->exponent + p2->exponent);
		}
	}
}