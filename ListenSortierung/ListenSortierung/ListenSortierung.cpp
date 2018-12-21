#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char getRandomCharacter();
void printMenu(bool AnyAvaiableList);

int main() {
	bool AnyAvaiableList = false;

	printMenu(AnyAvaiableList);
	
}

void printMenu(bool AnyAvaiableList) {
	if (AnyAvaiableList == false) {
		printf("******************************");
		printf("\n\tVerkette Liste");
		printf("\n******************************");

		printf("\n\n\n[1] Liste erstellen");
		printf("\n[2] Liste loeschen ");
		printf("\n[3] Person loeschen");
		printf("\n[4] Liste sortieren");
		printf("\n[5] Liste ausgeben");
		printf("\n[6] Programm beenden\n");
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
		printf("\n[6] Programm beenden\n");
		system("pause");
	}
}

char getRandomCharacter() {
	return rand() % 26 + 65;
}