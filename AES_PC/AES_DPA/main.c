#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <Windows.h>

#include "STMBoard.h"
#include "LogFileWrite.h"
#include "RandomBytes.h"
#include "Params.h"
#include "aes.h"

#define PORT L"\\\\.\\COM7"
#define MAX_ROUND 200

#define KEY_TRANSMIT (uint8_t) 1
#define ENCRYPTION_START (uint8_t) 2
#define ENCRYPTION_END (uint8_t) 255

#define DONGGEUN_SEED 10000

uint8_t const key[KEYLEN] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

uint8_t in[KEYLEN];
uint8_t ref[KEYLEN];
uint8_t out[KEYLEN];

DWORD dwBytesWrite;
DWORD dwBytesRead;

int main(void)
{
	srand(DONGGEUN_SEED);

	if (SerialPortConnect()) {
		printf("Serial Port Connect Error\n");
		return -1;
	}

	if (FileOpen()) {
		printf("File Open Error\n");
		return - 1;
	}

	char sendSignal[2], receiveSignal[2];

	sendSignal[0] = KEY_TRANSMIT;
	sendSignal[1] = 1;

	SendSignalToBoard(sendSignal);

	for (int i = 0; i < 3; i++) {
		uint8_t buffer[16];
		GetDataFromBoard(buffer, KEYLEN);
		SendSignalToBoard(sendSignal);

		for (int j = 0; j < KEYLEN; j++) {
			printf("%02x ", buffer[j]);
		}
		printf("\n");
	}

	return 0;

	for (int i = 0; i < 5000; i++) {
		uint8_t buffer[16];

		GetDataFromBoard(buffer, KEYLEN);
		SavePlainText(buffer);
		SendSignalToBoard(sendSignal);

		for (int j = 0; j < KEYLEN; j++) {
			printf("%02x ", buffer[j]);
		}
		printf("\n");

		AES128_ECB_encrypt(buffer, key, out);

		GetDataFromBoard(buffer, KEYLEN);
		SendSignalToBoard(sendSignal);

		for (int j = 0; j < KEYLEN; j++) {
			printf("%02x ", buffer[j]);
		}
		printf("\n");

		for (int j = 0; j < KEYLEN; j++) {
			printf("%02x ", out[j]);
		}
		printf("\n");

		if (strncmp(out, buffer, KEYLEN)) {
			
			break;
		}
		printf("%d Success\n", i + 1);

	}

	return 0;


	uint8_t buffer[16];
	

	sendSignal[0] = KEY_TRANSMIT;
	sendSignal[1] = 1;

	SendSignalToBoard(sendSignal);
	GetSignalFromBoard(receiveSignal);
	
	SendDataToBoard(key, KEYLEN);
	GetDataFromBoard(buffer, KEYLEN);

	if (strncmp(key, buffer, KEYLEN)) {
		printf("Key Transmit Error\n");
		return -1;
	}

	for (int i = 0; i < MAX_ROUND; i++) {
		// Random PlainText Generation
		GetRandomByte(in, KEYLEN);
		SavePlainText(in);

		// Send Start Signal
		sendSignal[0] = ENCRYPTION_START;

		SendSignalToBoard(sendSignal);
		GetSignalFromBoard(&receiveSignal);

		// Send Random PlainText
		SendDataToBoard(in, KEYLEN);
		GetDataFromBoard(buffer, KEYLEN);

		if (strncmp(in, buffer, KEYLEN)) {
			printf("Data Transmit Error\n");
			break;
		}

		SendSignalToBoard(sendSignal);
		GetDataFromBoard(out, KEYLEN);

		AES128_ECB_encrypt(in, key, ref);

		for (int j = 0; j < KEYLEN; j++) {
			printf("%02x ", out[j]);
		}
		printf("\n");
		for (int j = 0; j < KEYLEN; j++) {
			printf("%02x ", ref[j]);
		}
		printf("\n");

		if (strncmp(out, ref, KEYLEN)) {
			printf("Encryption Error\n");
			break;
		}

		printf("%02d Success!\n", i + 1);
		Sleep(1000);
	}

	FileClose();

	//uint8_t rs[16];

	//if (!WriteFile(hSerial, rs, 2, &dwBytesWrite, NULL)) {
	//	printf("!\n");
	//};

	//if (!ReadFile(hSerial, rs, 2, &dwBytesRead, NULL)) {
	//	printf("Data Receive Fail\n");
	//}
	//printf("%02x, %02x\n", rs[0], rs[1]);

	//if (!WriteFile(hSerial, in, KEYLEN, &dwBytesWrite, NULL)) {
	//	printf("Data Send Fail\n");
	//}

	//if (!ReadFile(hSerial, rs, KEYLEN, &dwBytesRead, NULL)) {
	//	printf("Data Receive Fail\n");
	//}
	//for (int i = 0; i < KEYLEN; i++) {
	//	printf("%02x ", rs[i]);
	//}
	//printf("\n");

	//if (!WriteFile(hSerial, key, KEYLEN, &dwBytesWrite, NULL)) {
	//	printf("Data Send Fail\n");
	//}
	//for (int i = 0; i < KEYLEN; i++) {
	//	printf("%02x ", out[i]);
	//}
	//printf("\n");

	//if (!ReadFile(hSerial, out, KEYLEN, &dwBytesRead, NULL)) {
	//	printf("Data Receive Fail\n");
	//}


	//if (!GetSignalFromBoard(&receiveSignal)) {
	//	printf("Data Send Fail\n");
	//	return -1;
	//}

	//GetDataFromBoard(out, KEYLEN);

	//for (int i = 0; i < KEYLEN; i++) {
	//	printf("%02x ", out[i]);
	//}

	//printf("%d\n", strncmp(ref, out, KEYLEN));

	return 0;
}
