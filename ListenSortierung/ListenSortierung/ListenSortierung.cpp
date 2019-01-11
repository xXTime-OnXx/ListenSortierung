#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Person {
	char firstname[40];
	char lastname[40];
	int year;
	struct Person* pNext;
} struPerson;

// Methoden Prototypen
struPerson* createList();
void deleteList(struPerson* pStart);
struPerson* deletePerson(struPerson* pStart);
void sort(struPerson** pStart);
void mergeSort(struPerson** pStart, int variableOrder[3]);
void quickSort(struPerson** pStart, int variableOrder[3]);
void printPerson(struPerson* pStart);
void shutDown(struPerson* pStart);

struPerson* sortedMerge(struPerson* a, struPerson* b, int variableOrder[3]);
void frontBackSplit(struPerson* source, struPerson** frontRef, struPerson** backRef);
struPerson* getTail(struPerson* cur);
struPerson* quickSortRecur(struPerson* pStart, struPerson* pEnd, int variableOrder[3]);
struPerson* partition(struPerson* pStart, struPerson* pEnd, struPerson** pNewStart, struPerson** pNewEnd, int variableOrder[3]);

struPerson* checkFirstPerson(struPerson* pStart, char lastname[], char firstname[]);
char getRandomCharacter();
int getRandomYear();
void printMenu();

// main Methode
int main() {
	struPerson* pStart = NULL;
	bool isListAvailable = false;
	int input = NULL;
	
	while (input != 6) {
		printMenu();
		printf("Geben sie die Zahl der gewuenschten Aktion ein: ");
		scanf_s("%i", &input);

		switch (input) {
			case 1:
				pStart = createList();
				break;

			case 2:
				deleteList(pStart);
				pStart = NULL;
				break;

			case 3:
				pStart = deletePerson(pStart);
				break;

			case 4:
				sort(&pStart);
				break;

			case 5:
				printPerson(pStart);
				break;

			case 6:
				shutDown(pStart);
				break;

			default:
				input = 0;
				break;
		}

		if (pStart != NULL) {
			isListAvailable = true;
		}

		system("cls");
	}
}

// Erstellt eine Liste mit der Anzahl angegebener Elementen
struPerson* createList() {
	int number = 0;
	struPerson* pStart = NULL;
	struPerson* pLast = NULL;

	printf("Wie viele Personen sollen in ihrer Liste generiert werden? ");
	scanf_s("%i", &number);

	for (int i = 0; i < number; i++) {
		struPerson *pPerson = (struPerson*)malloc(sizeof(struPerson));

		char* pFirstname = &pPerson->firstname[0];
		*pFirstname = getRandomCharacter();
		pFirstname++;
		*pFirstname = '\0';
		
		char* pLastname = &pPerson->lastname[0];
		*pLastname = getRandomCharacter();
		pLastname++;
		*pLastname = '\0';

		pPerson->year = getRandomYear();
		pPerson->pNext = NULL;
		if (pStart == NULL) pStart = pPerson;
		if (pLast != NULL) pLast->pNext = pPerson;
		pLast = pPerson;
	}
	return pStart;
}

// Löscht und entfernt alle Element der angegebene Liste
void deleteList(struPerson* pStart) {
	if (pStart != NULL) {
		struPerson* pFirst = pStart;
		struPerson* pNext = pStart->pNext;
		while (pFirst != NULL) {
			pNext = pFirst->pNext;
			free(pFirst);
			pFirst = pNext;
		}
	}
}

// Löscht die Person mit den selben eingegeben Nach- und Vorname
struPerson* deletePerson(struPerson* pStart) {
	char lastname[30];
	char firstname[30];

	printf("Geben sie folgende Angaben der Person an welche sie löschen möchten: \n");
	printf("Nachname: ");
	scanf_s(" %c", &lastname[0]);
	printf("Vorname: ");
	scanf_s(" %c", &firstname[0]);

	char *pLastname = &lastname[1];
	char *pFirstname = &firstname[1];

	*pLastname = '\0';
	*pFirstname = '\0';

	struPerson* pNewStart = checkFirstPerson(pStart, lastname, firstname);

	struPerson* prev = pNewStart;
	while (prev->pNext != NULL) {
		if (prev->pNext->lastname[0] == lastname[0] && prev->pNext->firstname[0] == firstname[0]) {
			struPerson* target = prev->pNext;
			prev->pNext = prev->pNext->pNext;
			free(target);
		}
		prev = prev->pNext;
	}
	return pNewStart;
}

// Um den Sortier Alogrythmus mit den gewünschten Angaben aus zu führen
void sort(struPerson** pStart) {
	int aNumber = 0;
	int vNumber = 0;
	int numericalOrder[3] = { 0, 0, 0 };
	printf("Wählen sie einen Sortieralgorythmus:\n");
	printf("[1] Merge-Sort Algorythmus\n");
	printf("[2] Quick-Sort Algorythmus\n");
	printf("Geben sie die Nummer des Algorythmus ein: ");
	scanf_s("%i", &aNumber);

	printf("\n\nNach Welchen Variablen soll die Liste sortiert werden?:\n");
	printf("[1] Standard (Nachname, Vorname)\n");
	printf("[2] Benutzerdefiniert\n");
	printf("Geben sie die Nummer der gewünschten Art ein: ");
	scanf_s("%i", &vNumber);

	if (vNumber == 2) {
		printf("\n\nNach welcher Reihenfolge der Variablen soll die Liste sortiert werden?\n");
		printf("[1] Nachname\n");
		printf("[2] Vorname\n");
		printf("[3] Jahr\n");
		printf("Erste Variable: ");
		scanf_s("%i", &numericalOrder[0]);
		printf("Zweite Variable: ");
		scanf_s("%i", &numericalOrder[1]);
		printf("Dritte Variable: ");
		scanf_s("%i", &numericalOrder[2]);
	}

	switch (aNumber)
	{
	case 1:
		mergeSort(pStart, numericalOrder);
		break;

	case 2:
		quickSort(pStart, numericalOrder);
		break;

	default:
		aNumber = 0;
		break;
	}
}


// Sortiert die Liste nach dem Merge-Sort Prinzip
void mergeSort(struPerson** pStart, int variableOrder[3]) {
	struPerson* head = *pStart;
	struPerson* a;
	struPerson* b;

	if ((head == NULL) || (head->pNext == NULL)) {
		return;
	}

	frontBackSplit(head, &a, &b);

	mergeSort(&a, variableOrder);
	mergeSort(&b, variableOrder);

	*pStart = sortedMerge(a, b, variableOrder);
}

// überfrüft ob die erste Person in der Sortierung vor der zweiten kommt
bool lessThan(struPerson* a, struPerson* b, int variableOrder[3]) {
	if (variableOrder[0] == 0) {
		if (a->lastname[0] < b->lastname[0]) {
			return true;
		}
		else if (a->lastname[0] == b->lastname[0]) {
			if (a->firstname[0] <= b->firstname[0]) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			if (variableOrder[i] == 1) {
				if (a->lastname[0] < b->lastname[0]) {
					return true;
				}
				else if (a->lastname[0] < b->lastname[0]) {
					continue;
				}
				else {
					return false;
				}
			}
			else if (variableOrder[i] == 2) {
				if (a->firstname[0] < b->firstname[0]) {
					return true;
				}
				else if (a->firstname[0] == b->firstname[0]) {
					continue;
				}
				else {
					return false;
				}
			}
			else if (variableOrder[i] == 3) {
				if (a->year < b->year) {
					return true;
				}
				else if (a->year == b->year) {
					continue;
				}
				else {
					return false;
				}
			}
			else {
				continue;
			}
		}
		return true;
	}
}

// 
struPerson* sortedMerge(struPerson* a, struPerson* b, int variableOrder[3]) {
	struPerson* result = NULL;

	if (a == NULL) {
		return(b);
	}
	else if (b == NULL) {
		return (a);
	}

	if (lessThan(a, b, variableOrder)) {
		result = a;
		result->pNext = sortedMerge(a->pNext, b, variableOrder);
	}
	else
	{
		result = b;
		result->pNext = sortedMerge(a, b->pNext, variableOrder);
	}
	return (result);
}

//
void frontBackSplit(struPerson* source, struPerson** frontRef, struPerson** backRef) {
	struPerson* pFast;
	struPerson* pSlow;
	pSlow = source;
	pFast = source->pNext;

	while (pFast != NULL) {
		pFast = pFast->pNext;
		if (pFast != NULL) {
			pSlow = pSlow->pNext;
			pFast = pFast->pNext;
		}
	}

	*frontRef = source;
	*backRef = pSlow->pNext;
	pSlow->pNext = NULL;
}

// Sortiert die liste nach dem Quick-Sort Prinzip
void quickSort(struPerson** pStart, int variableOrder[3]) {
	(*pStart) = quickSortRecur(*pStart, getTail(*pStart), variableOrder);
}

// Gibt die letzte Person der Liste zurück
struPerson* getTail(struPerson* cur) {
	while (cur != NULL && cur->pNext != NULL) {
		cur = cur->pNext;
	}
	return cur;
}

//
struPerson* quickSortRecur(struPerson* pStart, struPerson* pEnd, int variableOrder[3]) {
	if (!pStart || pStart == pEnd) {
		return pStart;
	}

	struPerson* pNewStart = NULL;
	struPerson* pNewEnd = NULL;

	struPerson* pivot = partition(pStart, pEnd, &pNewStart, &pNewEnd, variableOrder);

	if (pNewStart != pivot) {
		struPerson* tmp = pNewStart;
		while (tmp->pNext != pivot) {
			tmp = tmp->pNext;
		}
		tmp->pNext = NULL;

		pNewStart = quickSortRecur(pNewStart, tmp, variableOrder);

		tmp = getTail(pNewStart);
		tmp->pNext = pivot;
	}

	pivot->pNext = quickSortRecur(pivot->pNext, pNewEnd, variableOrder);

	return pNewStart;
}

// 
struPerson* partition(struPerson* pStart, struPerson* pEnd, struPerson** pNewStart, struPerson** pNewEnd, int variableOrder[3]) {
	struPerson* pivot = pEnd;
	struPerson* prev = NULL;
	struPerson* cur = pStart;
	struPerson* tail = pivot;

	while (cur != pivot) {
		if (lessThan(cur, pivot, variableOrder)) {
			if ((*pNewStart) == NULL) {
				(*pNewStart) = cur;
			}

			prev = cur;
			cur = cur->pNext;
		}
		else {
			if (prev) {
				prev->pNext = cur->pNext;
			}
			struPerson* tmp = cur->pNext;
			cur->pNext = NULL;
			tail->pNext = cur;
			tail = cur;
			cur = tmp;
		}
	}

	if ((*pNewStart) == NULL) {
		(*pNewStart) = pivot;
	}

	(*pNewEnd) = tail;

	return pivot;
}

void shutDown(struPerson* pStart) {
	deleteList(pStart);
	exit(0);
}

// Überprüft ob die erste Person der Liste gelöscht werden soll
struPerson* checkFirstPerson(struPerson* pStart, char lastname[], char firstname[]) {
	 if (pStart->lastname[0] == lastname[0] && pStart->firstname[0] == firstname[0]) {
		 if (pStart->pNext == NULL) {
			 printf("Es existiert nur 1 Element. Um die Liste zu löschen wählen sie die dafür zuständige Funktion.");
			 system("pause");
			 return pStart;
		 }

		 struPerson* pNewStart = pStart->pNext;
		 free(pStart);

		 pNewStart = checkFirstPerson(pNewStart, lastname, firstname);

		 return pNewStart;
	 }
	 return pStart;
}

void printPerson(struPerson* pStart) {
	int number = 0;
	printf("Wie viele Personen der Liste sollen angezeigt werden? (0 = alle): ");
	scanf_s("%i", &number);


	if (number == 0) {
		int i = 1;
		system("cls");
		printMenu();
		printf("\n");
		for (struPerson* pPerson = pStart; pPerson != NULL; pPerson = pPerson->pNext) {
			printf("Nachname: %s\tVorname: %s\t Jahrgang: %i\n", pPerson->lastname, pPerson->firstname, pPerson->year);
			i++;
		}
	}
	else {
		struPerson* pPerson = pStart;
		for (int i = 0; i < number; i++) {
			printf("Nachname: %s\tVorname: %s\t Jahrgang: %i\n", pPerson->lastname, pPerson->firstname, pPerson->year);
			pPerson = pPerson->pNext;
		}
	}

	system("pause");
}

// Gibt einen Zufallsbuchstaben von typ char zurück
char getRandomCharacter() {
	return rand() % 26 + 65;
}

// Gibt eine Zufallszahl zwischen 1900 und 2018 zurück
int getRandomYear() {
	return rand() % 119 + 1900;
}

// Gibt das Menu in der Konsole aus
void printMenu() {
	printf("******************************");
	printf("\n\tVerkette Liste");
	printf("\n******************************");

	printf("\n\n\n[1] Liste erstellen");
	printf("\n[2] Liste loeschen ");
	printf("\n[3] Person loeschen");
	printf("\n[4] Liste sortieren");
	printf("\n[5] Liste ausgeben");
	printf("\n[6] Programm beenden\n\n");
}


