#include "STMBoard.h"

int SerialPortConnect() {
	// 통신 설정
	HANDLE hSerial;

	wchar_t PortNo[20] = { 0 }; //contain friendly name
	swprintf_s(PortNo, 20, PORT);

	hSerial = CreateFile(PortNo, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DCB dcbSerialParams = { 0 };	// 통신 설정용 구조체
	COMMTIMEOUTS timeouts = { 0 };	// 통신 Timeout

	if (hSerial == INVALID_HANDLE_VALUE) {
		return 11;
	}

	// 세팅 구조체
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(hSerial, &dcbSerialParams)) {
		// Error getting COM port state
		CloseHandle(hSerial);
		return 12;
	}

	dcbSerialParams.BaudRate = CBR_115200;	// 보드레이트 설정
	dcbSerialParams.ByteSize = 8;			// 데이터 사이즈 설정
	dcbSerialParams.StopBits = ONESTOPBIT;	// 스탑비트 설정
	dcbSerialParams.Parity = NOPARITY;		// 패리티 설정

	if (!SetCommState(hSerial, &dcbSerialParams)) {     // 설정 적용
		// Error setting COM port state
		CloseHandle(hSerial);
		return 13;
	}

	timeouts.ReadIntervalTimeout = 100;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.ReadTotalTimeoutMultiplier = 10;

	timeouts.WriteTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(hSerial, &timeouts)) {
		// Error set timeouts
		CloseHandle(hSerial);
		return 14;
	}

	return 0;
}

int SendSignalToBoard(uint8_t signal)
{
	if (!WriteFile(hSerial, signal, 1, &dwBytesWrite, NULL))
		return 31;

	return 0;
}

int GetSignalFromBoard(uint8_t* signal)
{
	if (!ReadFile(hSerial, signal, 1, &dwBytesRead, NULL))
		return 32;

	return 0;
}

int SendDataToBoard(char* const data, int length)
{
	if (!WriteFile(hSerial, (uint8_t) length, 1, &dwBytesWrite, NULL))
		return 30;

	if (!WriteFile(hSerial, data, length, &dwBytesWrite, NULL))
		return 31;

	return 0;
}

int GetDataFromBoard(char* destination, int length)
{
	if (!ReadFile(hSerial, destination, length, &dwBytesRead, NULL))
		return 32;

	return 0;
}
