#pragma once

#include <stdio.h>

#include "Params.h"

// Log File
FILE* fp;

int SaveMessage(const char ct[CIPHER_TEXT_SIZE]);

int FileOpen();
void FileClose();

void CharToHexAndWrite(unsigned char c, FILE* f);