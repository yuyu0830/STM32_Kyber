#pragma once

#include <stdio.h>

#include "Params.h"

// Log File
FILE* fp;

int SavePlainText(const char pt[KEYLEN]);

int FileOpen();
void FileClose();

void CharToHexAndWrite(unsigned char c, FILE* f);