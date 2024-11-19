#include "SerialConnection.h"

int SerialPortConnect() {
	// ��� ����
	HANDLE hSerial;

	wchar_t PortNo[20] = { 0 }; //contain friendly name
	swprintf_s(PortNo, 20, PORT);

	hSerial = CreateFile(PortNo, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DCB dcbSerialParams = { 0 };	// ��� ������ ����ü
	COMMTIMEOUTS timeouts = { 0 };	// ��� Timeout

	if (hSerial == INVALID_HANDLE_VALUE) {
		return 11;
	}

	// ���� ����ü
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(hSerial, &dcbSerialParams)) {
		// Error getting COM port state
		CloseHandle(hSerial);
		return 12;
	}

	dcbSerialParams.BaudRate = CBR_115200;	// ���巹��Ʈ ����
	dcbSerialParams.ByteSize = 8;			// ������ ������ ����
	dcbSerialParams.StopBits = ONESTOPBIT;	// ��ž��Ʈ ����
	dcbSerialParams.Parity = NOPARITY;		// �и�Ƽ ����

	if (!SetCommState(hSerial, &dcbSerialParams)) {     // ���� ����
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

int SendKey(char* secretKey) {
	if (!WriteFile(hSerial, KEY_SEND_START_SIGNAL, SIGNAL_SIZE, &dwBytesWrite, NULL)) {
		return 31;
	}

	if (!ReadFile(hSerial, buff, SIGNAL_SIZE, &dwBytesRead, NULL)) {
		return 32;
	}
	
	if (!WriteFile(hSerial, secretKey, SECRET_KEY_SIZE, &dwBytesWrite, NULL)) {
		return 33;
	}

	if (!ReadFile(hSerial, buff, SIGNAL_SIZE, &dwBytesRead, NULL)) {
		return 34;
	}

	return 0;
}

int Decryption(char* cipherText, char* plainText)
{
	if (!WriteFile(hSerial, DECRYPTION_START_SIGNAL, SIGNAL_SIZE, &dwBytesWrite, NULL)) {
		return 41;
	}

	if (!ReadFile(hSerial, buff, SIGNAL_SIZE, &dwBytesRead, NULL)) {
		return 42;
	}

	if (!WriteFile(hSerial, cipherText, CIPHER_TEXT_SIZE, &dwBytesWrite, NULL)) {
		return 43;
	}

	if (!ReadFile(hSerial, buff, SIGNAL_SIZE, &dwBytesRead, NULL)) {
		return 44;
	}

	if (ReadFile(hSerial, plainText, ORIGIN_TEXT_SIZE, &dwBytesRead, NULL)) {
		printf("plaintext  : ");
		for (int i = 0; i < ORIGIN_TEXT_SIZE; i++) {
			printf("%02x", plainText[i]);
		}
	}
	else {
		return 45;
	}

	return 0;
}

