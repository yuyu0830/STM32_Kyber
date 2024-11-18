#pragma once

#include <stdio.h>

#include "Params.h"

// Log File
FILE* fp;

int LoadSetting(char* pk, char* sk, char* tk);
int SaveSetting(const char* pk, const char* sk, const char* tk);
int LoadMessage(char ot[SAMPLE_COUNT][ORIGIN_TEXT_SIZE],
				char ct[SAMPLE_COUNT][CIPHER_TEXT_SIZE],
				char ss[SAMPLE_COUNT][KYBER_SYMBYTES]);
int SaveMessage(const char ot[SAMPLE_COUNT][ORIGIN_TEXT_SIZE],
				const char ct[SAMPLE_COUNT][CIPHER_TEXT_SIZE],
				const char ss[SAMPLE_COUNT][KYBER_SYMBYTES]);

int FileOpen();
void WriteLog(char* publicKey, char* secretKey);
void FileWrite(int cnt, char* originText, int result);
void FileClose();

void CharToHexAndWrite(unsigned char c, FILE* f);
unsigned char HexToChar(char a, char b);