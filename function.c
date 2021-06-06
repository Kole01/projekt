#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>




int id = 0;
int mines = 0;
int fieldUser[20][20];
int field[20][20];
int score = 0;
int size = 0;
int debug = 1;
int scoreMultiplier = 0;
int timeInSeconds;
clock_t start, end, total;
PLAYER* userField;


void menu() { // Izbornik
	system("cls");
	int choice;
	char exitCheck[3];
	int temp;

	//Printanje izbornika!
	printf("\n");
	printf("\n\t\tOdaberite jednu od opcija:");
	printf("\n");
	printf("\n\t\t1. Nova igra!");
	printf("\n\t\t2. Najbolji rezultati!");
	printf("\n\t\t3. Izlazak iz igre!");
	printf("\n");

	// Provjera unosa izbora!
	do {
		printf("\nOdaberite opciju :");
		scanf("%d", &choice);
		if (choice < 1 || choice>3) printf("Ta opcija ne postoji!");
	} while (choice < 1 || choice>3);

	//Odabir opcija!
	switch (choice) {
	case 1:

		boardDifficulty();
		break;

	case 2:
		system("cls");
		menuScores();
		break;

	case 3://Izlaz iz programa!
		printf("Zelite izaci?");
		do {
			scanf("%2s", exitCheck);
			if (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1) printf("\nUnos nije dobar\n");

		} while (strcmp(exitCheck, "da") == 1 && strcmp(exitCheck, "ne") == 1);

		if (strcmp(exitCheck, "da") == 0) {
			temp = 0;

		}
		else temp = 1;

		switch (temp) {
		case 1:
			menu();
			break;
		case 0:
			exit(EXIT_FAILURE);
		}
	}

}

void boardDifficulty() {
	system("cls");
	int choice;
	//Printanje podizbornika!
	printf("\n");
	printf("\nOdaberite tezinu igre!\n");
	printf("1. Polje velicine 8x8 i 10 mina!\n");
	printf("2. Polje velicine 16x16 i 40 mina!\n");
	printf("3. Nazad na glavni izbornik\n");
	printf("\n");

	//provjera unosa
	do {
		printf("Odaberite opciju:");
		scanf("%d", &choice);
		if (choice < 1 || choice>3) printf("Unos nije ispravan!");
	} while (choice < 1 || choice>3);

	// izbor!
	switch (choice) {
	case 1:
		mines = 10;
		size = 8;
		scoreMultiplier = 1;
		boardGenerate();
		boardPrintBlank();
		start = clock();
		boardGuess();

		break;

	case 2:
		scoreMultiplier = 2;
		size = 16;
		mines = 40;
		boardGenerate();
		boardPrintBlank();
		start = clock();
		boardGuess();
		break;

	case 3:

		system("cls");
		menu();
		break;
	}


}


void boardGenerate() {
	srand(time(NULL));

	int i, j;
	int minesCheck = 0;

	//Postavljanje praznog boarda
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			field[i][j] = 48;

		}
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			fieldUser[i][j] = 45;
		}
	}



	//Postavljanje mina
	do {

		i = rand() % size;
		j = rand() % size;
		if (field[i][j] == 66) {
			i = rand() % size;
			j = rand() % size;
		}
		else {
			field[i][j] = 66;

			minesCheck++;
		}


	} while (minesCheck != mines);


	//Postavljanje brojeva koji oznacuju broj mina oko njih
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (field[i][j] != 66)
			{
				field[i][j] = 48;
			}
			if ((field[i - 1][j - 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i - 1][j] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i][j - 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i - 1][j + 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i + 1][j - 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i + 1][j] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i][j + 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}
			if ((field[i + 1][j + 1] == 66) && (field[i][j] != 66))
			{
				field[i][j]++;
			}

		}
	}
}





void boardGuess() {
	int x, y;
	int i, j;
	int match = 0;


	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (fieldUser[i][j] == field[i][j]) match++;
		}
	}
	if (match == (size * size) - mines) win();



	do { // korisnik odabire koje polje ce se pogledati!
		printf("\n");
		printf("Zadaj koordinatu x: ");
		scanf("%d", &x);

		printf("Zadaj koordinatu y: ");
		scanf("%d", &y);
		if (x < 0 || (x > size - 1) && y<0 || y>size - 1) printf("\nUnesena vrijednost nije ispravana, unesite valjane koordiante!");
	} while (x<0 || x>size - 1 && y<0 || y>size - 1);


	boardMatch(x, y);




}

void boardMatch(int x, int y) {
	


	if (field[x][y] == 66) {
		fieldUser[x][y] = field[x][y];
		end = clock();
		total = end - start;
		timeInSeconds = total / CLOCKS_PER_SEC;
		finalBoard();
		endGame();
	}
	if (fieldUser[x][y] != 45) {
		printf("Odabrali ste polje koje je vec otkriveno!");
		boardGuess();

	}
	else {
		fieldUser[x][y] = field[x][y];
		score += 10;
		if (field[x][y] == 48) {


			//polja iznad odabranog polja
			if (field[x - 1][y - 1] == field[x][y])
			{
				fieldUser[x - 1][y - 1] = field[x - 1][y - 1];
				score += 10;
			}
			if (field[x - 1][y] == field[x][y])
			{
				fieldUser[x - 1][y] = field[x - 1][y];
				score += 10;
			}
			if (field[x - 1][y + 1] == field[x][y])
			{
				fieldUser[x - 1][y + 1] = field[x - 1][y + 1];
				score += 10;
			}
			//polja u ravnini zadanog polja
			if (field[x][y - 1] == field[x][y])
			{
				fieldUser[x][y - 1] = field[x][y - 1];
				score += 10;
			}
			if (field[x][y + 1] == field[x][y])
			{
				fieldUser[x][y + 1] = field[x][y + 1];
				score += 10;
			}
			//polja ispod odabrnog polja 
			if (field[x + 1][y - 1] == field[x][y])
			{
				fieldUser[x + 1][y - 1] = field[x + 1][y - 1];
				score += 10;
			}
			if (field[x + 1][y] == field[x][y])
			{
				fieldUser[x + 1][y] = field[x + 1][y];
				score += 10;
			}
			if (field[x + 1][y + 1] == field[x][y])
			{
				fieldUser[x + 1][y + 1] = field[x + 1][y + 1];
				score += 10;
			}
		}
		boardPrint(x, y);
	}
}

void win() {
	char check[3];
	int temp;
	printf("Pobjeda!");
	end = clock();
	total = end - start;
	timeInSeconds = total / CLOCKS_PER_SEC;
	score += timeInSeconds * 10;
	printf("Za igru vam je trebalo %d", timeInSeconds);
	writeFile();
	printf("\nZelite li odigrati jos jednu igru?");
	do {
		scanf("%2s", check);
		if (strcmp(check, "da") == 1 && strcmp(check, "ne") == 1) printf("\nUnos nije dobar\n");

	} while (strcmp(check, "da") == 1 && strcmp(check, "ne") == 1);

	if (strcmp(check, "da") == 0) {
		temp = 1;
	}
	else temp = 0;

	switch (temp) {
	case 1:
		boardDifficulty();
		break;
	case 0:
		exit(EXIT_FAILURE);
	}

}




void finalBoard() {
	int i = 0, j = 0, k = 0;
	printf("\n");
	system("cls");
	for (i = 0; i < size; i++) {

		if (i < 9)printf("    %d", i);
		else if (i == 9)printf("    %d ", i);
		else printf("   %d", i);


	}
	printf("\n");
	printf("  ");
	for (i = 0; i < size; i++) {

		printf("+----");
	}
	printf("+\n");

	for (i = 0; i < size; i++)
	{
		printf("%d", i);
		if (i < 10)printf(" ");
		for (j = 0; j < size; j++)
		{
			printf("|  %c ", fieldUser[i][j], fieldUser[i][j]);

		}
		printf("|\n");
		printf("  ");
		for (k = 0; k < size; k++) {

			printf("+----");

		}


		printf("+\n");
	}
}

//Pritntanje polja s odabranim poljima

void boardPrint(int x, int y) {
	int i = 0, j = 0, k = 0;
	int debugMines = 0;
	printf("\n");
	system("cls");
	if (debug == 1) {
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				if (field[i][j] == 66) {
					debugMines++;
					printf("%d. mina se nalazi na: %d,%d\n", debugMines, i, j);

				}
			}
		}
	}
	printf("\n");
	printf("\n");
	printf("\n");
	for (i = 0; i < size; i++) {

		if (i < 9)printf("    %d", i);
		else if (i == 9)printf("    %d ", i);
		else printf("   %d", i);


	}
	printf("\n");
	printf("  ");
	for (i = 0; i < size; i++) {

		printf("+----");
	}
	printf("+\n");

	for (i = 0; i < size; i++)
	{
		printf("%d", i);
		if (i < 10)printf(" ");
		for (j = 0; j < size; j++)
		{
			printf("|  %c ", fieldUser[i][j], fieldUser[i][j]);

		}
		printf("|\n");
		printf("  ");
		for (k = 0; k < size; k++) {

			printf("+----");

		}


		printf("+\n");
	}
	boardGuess();
}


void boardPrintBlank() { //pritanje igre
	system("cls");
	int i = 0, j = 0, k = 0;
	printf("\n");

	for (i = 0; i < size; i++) {

		if (i < 9)printf("    %d", i);
		else if (i == 9)printf("    %d ", i);
		else printf("   %d", i);


	}
	printf("\n");
	printf("  ");
	for (i = 0; i < size; i++) {

		printf("+----");
	}
	printf("+\n");

	for (i = 0; i < size; i++)
	{
		printf("%d", i);
		if (i < 10)printf(" ");
		for (j = 0; j < size; j++)
		{

			printf("|  - ");
		}
		printf("|\n");
		printf("  ");
		for (k = 0; k < size; k++) {

			printf("+----");

		}


		printf("+\n");
	}
	boardGuess();
}

void endGame() {

	char check[3];
	int temp;
	score += timeInSeconds * 10;
	printf("Za igru vam je trebalo %d", timeInSeconds);
	printf("\nPolje koje ste odabrali sadrzava minu! Igra je zavrsena!");
	writeFile();
	printf("\nZelite li odigrati jos jednu igru?");
	do {
		scanf("%2s", check);
		if (strcmp(check, "da") == 1 && strcmp(check, "ne") == 1) printf("\nUnos nije dobar\n");

	} while (strcmp(check, "da") == 1 && strcmp(check, "ne") == 1);

	if (strcmp(check, "da") == 0) {
		temp = 1;
	}
	else temp = 0;

	switch (temp) {
	case 1:
		boardDifficulty();
		break;
	case 0:

		exit(EXIT_FAILURE);
	}


}


void menuScores() {
	int choice;
	//Printanje podizbornika!
	printf("\n");
	printf("Opcije s rezultatima\n");
	printf("1. Ispisati 10 najboljih rezultata!\n");
	printf("2. Obrisati trazeni rezultat!\n");
	printf("3. Obrisati sve rezultate!\n");
	printf("4. Nazad na glavni izbornik\n");
	printf("\n");

	//provjera unosa
	do {
		printf("Odaberite opciju:");
		scanf("%d", &choice);
		if (choice < 1 || choice>5) printf("Unos nije ispravan!");
	} while (choice < 1 || choice>5);

	// izbor!
	switch (choice) {
	case 1:
		sort();
		outputFile();
		break;

	case 2:
		deleteSpecificScore();
		break;

	case 3:
		deleteScores();
		break;

	case 4:

		system("cls");
		menu();
		break;
	}


}




void fileOpening() {
	FILE* file = fopen("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin", "ab+");
	fwrite(&id, sizeof(int), 1, file);
	if (file == NULL) {
		perror("Kreiranje datoteke scores.bin");
		exit(EXIT_FAILURE);
	}
	fclose(file);
}

void loadFile() {
	FILE* file = fopen("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin", "rb");
	if (file == NULL) {
		perror("Ucitavanje rezultata");
		return NULL;
	}
	fread(&id, sizeof(int), 1, file);
	printf("Broj Clanova: %d\n", id);
	userField = (PLAYER*)calloc(id, sizeof(PLAYER));
	if (userField == NULL) {
		perror("Zauzimanje memorije za rezultate");
		return NULL;
	}
}


void writeFile() {
	char tempUsername[30];
	fileOpening();
	FILE* file = fopen("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin", "rb+");
	if (file == NULL) {
		perror("Kreiranje datoteke scores.bin");
		exit(EXIT_FAILURE);
	}

	PLAYER* temp={ 0 };
	temp=(PLAYER*)calloc(1, sizeof(PLAYER));
	fread(&id, sizeof(int), 1, file);
	temp->id = id;
	printf("\nNapisite svoj username!");
	scanf("%29s", temp->username);
	temp->score = score * scoreMultiplier;
	temp->time = timeInSeconds;
	fseek(file, sizeof(PLAYER) * id, SEEK_CUR);
	fwrite(&temp, sizeof(PLAYER), 1, file);
	rewind(file);
	id++;
	fwrite(&id, sizeof(int), 1, file);
	fclose(file);

}

void outputFile() {
	int i;
	FILE* file = fopen("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin", "rb+");
	if (file == NULL) {
		perror("Kreiranje datoteke scores.bin");
		exit(EXIT_FAILURE);
	}
	fread(userField, sizeof(PLAYER), id, file);
	if (id < 10) {
		for (i = 0; i < id; i++) {
			printf("ID:%d ,Username:%s, Score:%d, Vrijeme:%d\n", (userField + i)->id, (userField + i)->username, (userField + i)->score, (userField + i)->time);
		}
	}
	else {
		for (i = 0; i < 10; i++) {
			printf("ID:%d ,Username:%s, Score:%d, Vrijeme:%d\n", (userField + i)->id, (userField + i)->username, (userField + i)->score, (userField + i)->time);
		}
	}
	fclose(file);
}

void deleteSpecificScore() {
	FILE* file = fopen("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin", "wb");
	FILE* temp = fopen("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\temp.bin", "wb");
	int i;
	int n;
	int found;
	do {
		printf("Zadaj id kojeg zelis obrisati!");
		scanf("%d", &n);
		if (n > id)printf("NEma toliko unesenih rezultata");
	} while (n > id);
	for (i = 0; i < id; i++) {
		if ((userField + i)->id != n) {
			fwrite(&userField + i, sizeof(PLAYER), 1, temp);
		}
		else found = 1;
	}
	if (!found) {
		printf("Nema tog id-a!");
	}

	fclose(file);
	fclose(temp);
	remove("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin");
	rename("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\temp.bin", "C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin");
}


void deleteScores() {
	FILE* file = fopen("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin", "rb");
	FILE* temp = fopen("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\temp.bin", "wb");
	
	fclose(file);
	fclose(temp);
	remove("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin");
	rename("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\temp.bin", "C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin");
}

void change(int* const veci, int* const manji) {
	int temp = 0;
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}
void sort() {
	FILE* temp = fopen("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\temp.bin", "wb");
	int min = -1;
	int i, j;
	for (i = 0; i < id - 1; i++)
	{
		min = i;
		for (j = i + 1; j < id; j++)
		{
			if ((userField+j)->score < (userField+min)->score) {
				min = j;
			}
		}
		change(&(userField+j)->score, &(userField+min)->score);
	}


	for (i = 0; i < id; i++) {
		fwrite(&userField + i, sizeof(PLAYER), 1, temp);
	}
	fclose("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\temp.bin");
	remove("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin");
	rename("C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\temp.bin", "C:\\Users\\Mihael\\Downloads\\Projekt-main\\Projekt-main\\scores.bin");
}
