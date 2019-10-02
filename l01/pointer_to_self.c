#include <stdio.h>

int main(int argc, char** argv) {
	void* ptr = NULL;
	ptr = &ptr;

	printf("%p original, %p content", &ptr, ptr);
}
