#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Person {
	char firstname[40];
	char lastname[40];
	int year;
	struct Person* pNext;
} struPerson;

// Methoden Prototypen
char getRandomCharacter();
int getRandomYear();
struPerson* createList(int number);
void printMenu(bool AnyAvaiableList);

// main Methode
int main() {
	struPerson* pStart = createList(5);
	bool isListAvailable = false;

	printMenu(isListAvailable);
}

// Erstellt eine Liste mit der Anzahl angegebener Elementen
struPerson* createList(int number) {
	struPerson* pStart = NULL;
	struPerson* pLast = NULL;

	for (int i = 0; i < number; i++) {
		struPerson *pPerson = (struPerson*)malloc(sizeof(struPerson));
		pPerson->firstname[0] = getRandomCharacter();
		pPerson->lastname[0] = getRandomCharacter();
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
	struPerson* pFirst = pStart;
	struPerson* pNext = pStart->pNext;
	while (pFirst != NULL) {
		pNext = pFirst->pNext;
		free(pFirst);
		pFirst = pNext;
	}
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
void printMenu(bool isListAvailable) {
	if (!isListAvailable) {
		printf("******************************");
		printf("\n\tVerkette Liste");
		printf("\n******************************");

		printf("\n\n\n[1] Liste erstellen");
		printf("\n[2] Liste loeschen ");
		printf("\n[3] Person loeschen");
		printf("\n[4] Liste sortieren");
		printf("\n[5] Liste ausgeben");
		printf("\n[6] Programm beenden\n\n");
		system("pause");
	}
	else
	{
		printf("******************************");
		printf("\n\tVerkette Liste");
		printf("\n******************************");

		printf("\n\n\n[1] Liste erstellen");
		printf("\n[2] Liste loeschen ");
		printf("\n[3] Person loeschen");
		printf("\n[4] Liste sortieren");
		printf("\n[5] Liste ausgeben");
		printf("\n[6] Programm beenden\n\n");
		system("pause");
	}
}