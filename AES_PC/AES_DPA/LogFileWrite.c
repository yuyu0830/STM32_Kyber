#include <time.h>

#include "LogFileWrite.h"

int FileOpen() {
	fopen_s(&fp, "./Log/PlainText.txt", "w");

	if (fp == NULL)
		return 24;

	return 0;
}

int SavePlainText(const char pt[KEYLEN])
{
	for (int i = 0; i < KEYLEN; i++) {
		CharToHexAndWrite((unsigned char)pt[i], fp);
	}
	
	fputc('\n', fp);

	return 0;
}

void FileClose() {
	fclose(fp);
}

void CharToHexAndWrite(unsigned char c, FILE* f) {
	fputs("0x", f);
	fputc((c >> 4) + ((c >> 4) < 10 ? 48 : 55), f);
	fputc((c & 0b1111) + ((c & 0b1111) < 10 ? 48 : 55), f);
	fputs(", ", f);
}