#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



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
void mergeSort(struPerson** pStart);
void printPerson(struPerson* pStart);

struPerson* sortedMerge(struPerson* a, struPerson* b);
void frontBackSplit(struPerson* source, struPerson** frontRef, struPerson** backRef);
struPerson* checkFirstPerson(struPerson* pStart, char lastname[], char firstname[]);
int printApplicablePerson(struPerson* pPerson[], int number);
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
				mergeSort(&pStart);
				break;

			case 5:
				printPerson(pStart);
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
		//pPerson->firstname[0] = getRandomCharacter();
		char* pFirstname = &pPerson->firstname[0];
		*pFirstname = getRandomCharacter();
		pFirstname++;
		*pFirstname = '\0';
		
		//pPerson->lastname[0] = getRandomCharacter();
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
	struPerson* pFirst = pStart;
	struPerson* pNext = pStart->pNext;
	while (pFirst != NULL) {
		pNext = pFirst->pNext;
		free(pFirst);
		pFirst = pNext;
	}
}

// Löscht die Person mit den selben eingegeben Nach- und Vorname
struPerson* deletePerson(struPerson* pStart) {
	char firstname;
	char lastname;
	char firstnameArray[30];
	char lastnameArray[30];
	struPerson* pApplicablePerson[10];

	// ---------------------------------
	// Einlesen funktioniert nicht!!!
	// ---------------------------------
	printf("Geben sie folgende Angaben der Person an welche sie löschen möchten: \n");
	printf("Vorname: ");
	scanf_s("%c\n", &firstname);
	printf("Nachname: ");
	scanf_s("%c\n", &lastname);

	firstnameArray[0] = firstname;
	lastnameArray[0] = lastname;

	struPerson* pNewStart = checkFirstPerson(pStart, lastnameArray, firstnameArray);

	struPerson* prev = pNewStart;
	while (prev->pNext != NULL) {
		if (prev->pNext->lastname[0] == lastnameArray[0] && prev->pNext->firstname[0] == firstnameArray[0]) {
			struPerson* target = prev->pNext;
			prev->pNext = prev->pNext->pNext;
			free(target);
		}
		prev = prev->pNext;
	}
	return pNewStart;
}


// Liste sortieren
void mergeSort(struPerson** pStart) {
	struPerson* head = *pStart;
	struPerson* a;
	struPerson* b;

	if ((head == NULL) || (head->pNext == NULL)) {
		return;
	}

	frontBackSplit(head, &a, &b);

	mergeSort(&a);
	mergeSort(&b);

	*pStart = sortedMerge(a, b);
}

// überfrüft ob die erste Person in der Sortierung vor der zweiten kommt
bool lessThan(struPerson* a, struPerson* b) {
	if (a->lastname[0] <= b->lastname[0]) {
		if (a->firstname <= b->firstname) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

//
struPerson* sortedMerge(struPerson* a, struPerson* b) {
	struPerson* result = NULL;

	if (a == NULL) {
		return(b);
	}
	else if (b == NULL) {
		return (a);
	}

	if (lessThan(a, b)) {
		result = a;
		result->pNext = sortedMerge(a->pNext, b);
	}
	else
	{
		result = b;
		result->pNext = sortedMerge(a, b->pNext);
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

// Gibt alle Personen aus welche den gleichen Namen haben und gibt die ausgewählte Person zurück
int printApplicablePerson(struPerson* pPerson[], int number) {
	int person = NULL;
	printf("Welche Person moechten sie loeschen?\n\n");

	for (int i = 0; i < number; i++) {
		char *firstname = &pPerson[i]->firstname[0];
		char *lastname = &pPerson[i]->lastname[0];
		printf("[%i] %s %s\n", i, firstname, lastname);
	}

	printf("Nummer: ");
	scanf_s("%i\n", &person);

	return person;
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


