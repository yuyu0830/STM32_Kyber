#include "RandomBytes.h"

int GetRandomByte(char* destination, int length) {
	for (int i = 0; i < length; i++) {
		destination[i] = rand() % 256;
	}
}