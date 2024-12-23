#ifndef STM_BOARD_H
#define STM_BOARD_H

#include <Windows.h>
#include <stdint.h>
#include <stdio.h>

#include "Params.h"

#define PORT L"\\\\.\\COM7"

HANDLE hSerial;

DWORD dwBytesWrite;
DWORD dwBytesRead;

int SerialPortConnect();

int SendSignalToBoard(char* const signal);
int GetSignalFromBoard(uint8_t* signal);

int SendDataToBoard(char* const data, int length);
int GetDataFromBoard(char* destination, int length);

#endif