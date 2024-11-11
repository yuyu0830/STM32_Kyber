#include "SerialConnection.h"

HANDLE SerialPortConnect() {
	// 통신 설정
	HANDLE hSerial;

	wchar_t PortNo[20] = { 0 }; //contain friendly name
	swprintf_s(PortNo, 20, PORT);

	hSerial = CreateFile(PortNo, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DCB dcbSerialParams = { 0 };	// 통신 설정용 구조체
	COMMTIMEOUTS timeouts = { 0 };	// 통신 Timeout

	if (hSerial == INVALID_HANDLE_VALUE) {
		printf("Error : Serial port can't be opened\n");
		return NULL;
	}

	// 세팅 구조체
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(hSerial, &dcbSerialParams)) {
		// Error getting COM port state
		printf("Error : Getting COM port state\n");
		CloseHandle(hSerial);
		return NULL;
	}

	dcbSerialParams.BaudRate = CBR_115200;	// 보드레이트 설정
	dcbSerialParams.ByteSize = 8;			// 데이터 사이즈 설정
	dcbSerialParams.StopBits = ONESTOPBIT;	// 스탑비트 설정
	dcbSerialParams.Parity = NOPARITY;		// 패리티 설정

	if (!SetCommState(hSerial, &dcbSerialParams)) {     // 설정 적용
		// Error setting COM port state
		printf("Error : Setting COM port state\n");
		CloseHandle(hSerial);
		return NULL;
	}

	timeouts.ReadIntervalTimeout = 100;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.ReadTotalTimeoutMultiplier = 10;

	timeouts.WriteTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(hSerial, &timeouts)) {
		// Error set timeouts
		printf("Error : Setting timeouts\n");
		CloseHandle(hSerial);
		return NULL;
	}

	return hSerial;
}