#pragma once

#include <Windows.h>
#include <stdio.h>

#include "Params.h"

#define PORT L"\\\\.\\COM5"

HANDLE hSerial;

DWORD dwBytesWrite;
DWORD dwBytesRead;

unsigned char buff[1200];

int SerialPortConnect();
int SendKey(char* secretKey);
int Decryption(char* cipherText, char* plainText);