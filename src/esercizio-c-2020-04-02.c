//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char maxChar(char *array) {
	char result = array[0];
	for (int i = 1; i < sizeof(array); i++) {
		if (result < array[i])
			result = array[i];
	}
	return result;
}

char minChar(char *array) {
	char result = array[0];
	for (int i = 1; i < sizeof(array); i++) {
		if (result > array[i])
			result = array[i];
	}
	return result;
}

int main(int argc, char *argv[]) {

#define NUM_CHARS 80

	//mettere array statico
	char char_array[NUM_CHARS];
	char inputChar;
	int index = 0;
	int numberOfArray = 0;

	while ((inputChar = getchar()) != EOF){

		char_array[index] = inputChar;
		index++;

		if (index == NUM_CHARS+1) {
			numberOfArray++;
			switch (fork()) {
			case 0:
				printf("sono il processo figlio\n");
				char minchar = minChar(char_array);
				printf("il carattere minimo è: %c\n", minchar);
				char maxchar = maxChar(char_array);
				printf("il carattere massimo è: %c\n", maxchar);

				exit(0);
				break;
			case -1:
				printf("fork() ha fallito! niente processo figlio!\n");

				exit(1);
				break;
			default:

				printf("sono il processo padre\n");

				if (wait(NULL) == -1) {
					perror("wait error");
				} else {
					printf(
							"[parent]il processo figlio ha terminato! ora termino anche io.\n");
				}
				index = 0;
				memset(char_array, 0, NUM_CHARS * sizeof(char));
				printf("array %d con contenuto al posto i di = %d\n",
						numberOfArray, char_array[3]);

				//	exit(0);
				// quando il processo padre termina, il processo figlio diventa
				// "orfano" e viene "adottato" dal processo init,
				// che automaticamente invoca wait() per rimuovere gli zombie.
			}
			/*index = 0;
			memset(char_array, 0, NUM_CHARS * sizeof(char));*/
		}
	}

	printf("%d\n", numberOfArray);
}
