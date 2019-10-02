#include <stdio.h>

void print(char **argv) {
	if (*argv != NULL) {
		printf("%s ", *argv);
		print(argv+1);
	} else {
		printf("\n");
	}
}


int main(int argc, char** argv) {
	print(argv);
}
