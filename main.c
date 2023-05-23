#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
	int status = 1;

	do {
		program(&status);
	} while (status != 0);

	return 0;
}