#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char getRandomCharacter();

int main() {
	system("pause");
}

char getRandomCharacter() {
	return rand() % 26 + 65;
}