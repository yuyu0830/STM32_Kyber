#pragma once

#include <stdio.h>

#include "Params.h"

// Log File
FILE* fp;

int FileOpen();
void WriteLog(char* publicKey, char* secretKey);
void FileWrite(int cnt, char* originText, int result);
void FileClose();

void WriteHexToCharacter(unsigned char c);