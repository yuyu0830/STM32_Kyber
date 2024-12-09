#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <Windows.h>
#include <time.h>

// Enable both ECB and CBC mode. Note this can be done before including aes.h or at compile-time.
// E.g. with GCC by using the -D flag: gcc -c aes.c -DCBC=0 -DECB=1
#define PORT L"\\\\.\\COM7"
#define MAX_ROUND 2
#define SECRET_KEY_REF 0x80

HANDLE hSerial;

DWORD dwBytesWrite;
DWORD dwBytesRead;

uint8_t buff[2];

int SerialPortConnect();

int main(void) {
	// 통신 설정
	HANDLE hSerial;

	wchar_t PortNo[20] = { 0 }; //contain friendly name
	swprintf_s(PortNo, 20, PORT);

	hSerial = CreateFile(PortNo, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DCB dcbSerialParams = { 0 };	// 통신 설정용 구조체
	COMMTIMEOUTS timeouts = { 0 };	// 통신 Timeout

	if (hSerial == INVALID_HANDLE_VALUE) {
		return 0;
	}

	// 세팅 구조체
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(hSerial, &dcbSerialParams)) {
		// Error getting COM port state
		CloseHandle(hSerial);
		return 0;
	}

	dcbSerialParams.BaudRate = CBR_115200;	// 보드레이트 설정
	dcbSerialParams.ByteSize = 8;			// 데이터 사이즈 설정
	dcbSerialParams.StopBits = ONESTOPBIT;	// 스탑비트 설정
	dcbSerialParams.Parity = NOPARITY;		// 패리티 설정

	if (!SetCommState(hSerial, &dcbSerialParams)) {     // 설정 적용
		// Error setting COM port state
		CloseHandle(hSerial);
		return 0;
	}

	timeouts.ReadIntervalTimeout = 100;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.ReadTotalTimeoutMultiplier = 10;

	timeouts.WriteTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(hSerial, &timeouts)) {
		// Error set timeouts
		CloseHandle(hSerial);
		return 0;
	}

	printf("Serial Connect\n");

	

	for (int i = 0; i < 256; i++) {
		uint8_t plainText[2];
		
		//plainText[0] = rand() % 256;

		for (int j = 0; j < 20; j++) {
			plainText[0] = i;
			plainText[1] = SECRET_KEY_REF;

			printf("plain text : %02x\n", plainText[0]);
			if (!WriteFile(hSerial, plainText, 2, &dwBytesWrite, NULL)) {
				printf("Error : Send Data Failed..\n");
			}
			else {
				printf("Log : %d Data Send Successful!\n", i + 1);
			}

			if (!ReadFile(hSerial, buff, 1, &dwBytesRead, NULL)) {
				printf("Error : Receive Data Failed..\n");
			}
			else {
				printf("%02x Data Receive Success!\n", buff[0]);
			}
			Sleep(1000);
		}
		
			/*for (int tk = 0; tk < 256; tk++) {
				plainText[1] = tk;
				Sleep(10);
				if (!WriteFile(hSerial, plainText, 2, &dwBytesWrite, NULL)) {
					printf("Error : Send Data Failed..\n");
				}
				else {
					printf("Log : %d, %d Data Send Successful!\n", i + 1, tk + 1);
				}

				if (!ReadFile(hSerial, buff, 1, &dwBytesRead, NULL)) {
					printf("Error : Receive Data Failed..\n");
				}
				else {
					printf("%02x Data Receive Success!\n", buff[0]);
				}
				Sleep(5000);
			
			}*/
		
		printf("\n");
	}


	return 0;
}

int SerialPortConnect() {
	
}