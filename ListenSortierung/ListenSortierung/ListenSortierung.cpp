#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Person {
	char firstname[40];
	char lastname[40];
	int year;
	struct Person* pNext;
} struPerson;

char getRandomCharacter();
int getRandomYear();
struPerson* createList(int number);

int main() {
	struPerson* pStart = createList(5);


	system("pause");
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

// Gibt einen Zufallsbuchstaben von typ char zurück
char getRandomCharacter() {
	return rand() % 26 + 65;
}

int getRandomYear() {
	return rand() % 119 + 1900;
}