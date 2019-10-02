#include <stdio.h>

int main() {
	void* ptr = NULL;
	ptr = &ptr;

	printf("%p original, %p content", (void*)&ptr, ptr);
}
