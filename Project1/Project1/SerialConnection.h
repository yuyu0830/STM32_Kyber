#pragma once

#include <Windows.h>
#include <stdio.h>

#define PORT L"\\\\.\\COM5"

HANDLE SerialPortConnect();