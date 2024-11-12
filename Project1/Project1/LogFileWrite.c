#include <time.h>

#include "LogFileWrite.h"

int FileOpen() {
	// Get Current Time
	time_t seconds = time(NULL);
	struct tm* now = localtime(&seconds);

	char buff[30];
	sprintf_s(buff, 30, "./Log/%2d%02d%02d_%02d%02d%02d.txt", now->tm_year - 100, now->tm_mon, now->tm_wday, now->tm_hour, now->tm_min, now->tm_sec);
	
	// File open
	fopen_s(&fp, buff, "w");

	if (fp == NULL) {
		return 21;
	}

	return 0;
}

void WriteLog(char* publicKey, char* secretKey)
{
	char buff[30];

	sprintf_s(buff, 30, "MAX Round : %d\n", MAX_ROUND);
	fputs(buff, fp);


	fputs("Public Key : ", fp);
	for (int i = 0; i < PUBLIC_KEY_SIZE; i++) {
		WriteHexToCharacter((unsigned char)publicKey[i]);
	}
	fputc('\n', fp);


	fputs("Secret Key : ", fp);
	for (int i = 0; i < SECRET_KEY_SIZE; i++) {
		WriteHexToCharacter((unsigned char)secretKey[i]);
	}
	fputc('\n', fp);
	fputc('\n', fp);
}


void FileWrite(int cnt, char* originText, int result) {
	char buff[4];

	sprintf_s(buff, 4, "%d  ", cnt);
	fputs(buff, fp);

	for (int i = 0; i < PLAIN_TEXT_SIZE; i++) {
		WriteHexToCharacter((unsigned char) originText[i]);
	}

	sprintf_s(buff, 4, " %d\n", result);
	fputs(buff, fp);
}

void FileClose()
{
	fclose(fp);
}

void WriteHexToCharacter(unsigned char c) {
	fputc((c >> 4) + ((c >> 4) < 10 ? 48 : 55), fp);
	fputc((c & 0b1111) + ((c & 0b1111) < 10 ? 48 : 55), fp);
}