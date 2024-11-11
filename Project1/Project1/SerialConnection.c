#include "SerialConnection.h"

HANDLE SerialPortConnect() {
	// ��� ����
	HANDLE hSerial;

	wchar_t PortNo[20] = { 0 }; //contain friendly name
	swprintf_s(PortNo, 20, PORT);

	hSerial = CreateFile(PortNo, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DCB dcbSerialParams = { 0 };	// ��� ������ ����ü
	COMMTIMEOUTS timeouts = { 0 };	// ��� Timeout

	if (hSerial == INVALID_HANDLE_VALUE) {
		printf("Error : Serial port can't be opened\n");
		return NULL;
	}

	// ���� ����ü
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(hSerial, &dcbSerialParams)) {
		// Error getting COM port state
		printf("Error : Getting COM port state\n");
		CloseHandle(hSerial);
		return NULL;
	}

	dcbSerialParams.BaudRate = CBR_115200;	// ���巹��Ʈ ����
	dcbSerialParams.ByteSize = 8;			// ������ ������ ����
	dcbSerialParams.StopBits = ONESTOPBIT;	// ��ž��Ʈ ����
	dcbSerialParams.Parity = NOPARITY;		// �и�Ƽ ����

	if (!SetCommState(hSerial, &dcbSerialParams)) {     // ���� ����
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