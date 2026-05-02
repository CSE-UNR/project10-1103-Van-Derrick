//Author: Derrick Van
//Purpose: Using 2D arrays and strings of arrays to replicate wordle
//Date:
#include <stdio.h>
#include <stdbool.h>

int getLength(char arr[]);
bool checkValid(char arr[]);
void makeLower(char arr[]);
bool loadFile(char secret[]);
void showExact(char entry[], char secret[]);
void showPartial(char entry[], char secret[]);
void printWin(int total);
void readEntry(char entry[]);

int main() {
	char secret[6];
	char history[6][6];
	int turn = 0;
	bool isVictory = false;

	if (!loadFile(secret)) {
		printf("Sorry, could not get today's word. Try again tomorrow.\n");
		return 1;
	}

	while (turn < 6 && !isVictory) {
		printf("GUESS %d! Enter your guess: ", turn + 1);
		readEntry(history[turn]);
		makeLower(history[turn]);
		printf("================================\n");

		bool match = true;
		for (int i = 0; i < 5; i++) {
			if (history[turn][i] != secret[i]) {
				match = false;
			}
		}

		if (match) {
			isVictory = true;
			for(int s = 0; s < 12; s++) printf(" ");
			for(int i = 0; i < 5; i++) printf("%c", history[turn][i] - 32);
			printf("\n");
			printWin(turn + 1);
		} else {
			for (int i = 0; i <= turn; i++) {
				showExact(history[i], secret);
				showPartial(history[i], secret);
			}
			turn++;
		}
	}

	if (!isVictory) {
		printf("FINAL GUESS : %s\n", secret);
		printf("================================\n");
		for (int i = 0; i < 6; i++) {
			showExact(history[i], secret);
			showPartial(history[i], secret);
		}
		printf("You lost, better luck next time!\n");
	}

	return 0;
}

int getLength(char arr[]) {
	int size = 0;
	while (arr[size] != '\0') {
		size++;
	}
	return size;
}

bool checkValid(char arr[]) {
	for (int i = 0; arr[i] != '\0'; i++) {
		if (!((arr[i] >= 'a' && arr[i] <= 'z') || (arr[i] >= 'A' && arr[i] <= 'Z'))) {
			return true;
		}
	}
	return false;
}

void makeLower(char arr[]) {
	for (int i = 0; arr[i] != '\0'; i++) {
		if (arr[i] >= 'A' && arr[i] <= 'Z') {
			arr[i] += 32;
		}
	}
}

bool loadFile(char secret[]) {
	FILE *ptr = fopen("mystery.txt", "r");
	if (!ptr) {
		return false;
	}
	fscanf(ptr, "%s", secret);
	makeLower(secret);
	fclose(ptr);
	return true;
}

void showExact(char entry[], char secret[]) {
	for (int i = 0; i < 5; i++) {
		if (entry[i] == secret[i]) {
			printf("%c", entry[i] - 32);
		} else {
			printf("%c", entry[i]);
		}
	}
	printf("\n");
}

void showPartial(char entry[], char secret[]) {
	bool taken[5] = {false, false, false, false, false};
	for (int i = 0; i < 5; i++) {
		if (entry[i] == secret[i]) {
			taken[i] = true;
		}
	}
	for (int i = 0; i < 5; i++) {
		bool flag = false;
		if (entry[i] != secret[i]) {
			for (int j = 0; j < 5; j++) {
				if (!taken[j] && entry[i] == secret[j]) {
					flag = true;
					taken[j] = true;
					break;
				}
			}
		}
		if (flag) {
			printf("^");
		} else {
			printf(" ");
		}
	}
	printf("\n");
}

void printWin(int total) {
	if (total == 1) {
		printf("      You won in 1 guess!\n            GOATED!\n");
	} else {
		printf("      You won in %d guesses!\n", total);
		if (total == 2) {
			printf("            Amazing!\n");
		} else {
			printf("            Nice!\n");
		}
	}
}

void readEntry(char entry[]) {
	char buffer[100];
	scanf("%s", buffer);
	while (getLength(buffer) != 5 || checkValid(buffer)) {
		if (getLength(buffer) != 5) {
			printf("Your guess must be 5 letters long.\n");
		} else {
			printf("Your guess must contain only letters.\n");
		}
		printf("Please try again: ");
		scanf("%s", buffer);
	}
	for (int i = 0; i < 5; i++) {
		entry[i] = buffer[i];
	}
	entry[5] = '\0';
}
