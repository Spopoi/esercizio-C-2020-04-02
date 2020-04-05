#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define NUM_CHARS 4

unsigned char minChar(unsigned char *array) {
	char result = array[0];
	for (int i = 1; i < sizeof(array); i++) {
		if (result > array[i])
			result = array[i];
	}
	return result;
}

unsigned char maxChar(unsigned char *array) {
	char result = array[0];
	for (int i = 1; i < sizeof(array); i++) {
		if (result < array[i])
			result = array[i];
	}
	return result;
}

int main(int argc, char *argv[]) {

	unsigned char char_array[NUM_CHARS];
	unsigned char inputChar;
	int index = 0;
	int numberOfArray = 0;
	printf("ciao, inserisci i caratteri: \n");

	while ((inputChar = getchar()) != EOF) {

		char_array[index] = inputChar;
		index++;

		if (index == NUM_CHARS) {
			numberOfArray++;
			switch (fork()) {
			case 0:
				printf("sono il processo figlio\n");
				unsigned char minchar = minChar(char_array);
				printf("il carattere minimo è: %d\n", minchar);
				unsigned char maxchar = maxChar(char_array);
				printf("il carattere massimo è: %c\n", maxchar);

				exit(0);
				break;
			case -1:
				printf("fork() ha fallito! niente processo figlio!\n");

				exit(1);
				break;
			default:

				if (wait(NULL) == -1) {
					perror("wait error");
				}
				index = 0;
				memset(char_array, 0, NUM_CHARS * sizeof(char));
			}
		}
	}

	printf("ho creato %d figli\n", numberOfArray);
	return 0;
}
