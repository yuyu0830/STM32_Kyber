#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "STMBoard.h"
#include "aes.h"
#include "test.h"

#define ENCRYPTION_START (uint8_t) 1
#define ENCRYPTION_END (uint8_t) 255

uint8_t key[KEYLEN] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
uint8_t in[KEYLEN] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
uint8_t ref[KEYLEN] = { 0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97 };
uint8_t out[KEYLEN] = { 0, };

int main(void)
{
	//Init();

	int state;
	uint8_t receiveSignal;

	SendSignalToBoard(ENCRYPTION_START);

	SendDataToBoard(key, KEYLEN);

	if (state = GetSignalFromBoard(&receiveSignal)) {
		printf("Data Send Fail : Code %d\n", state);
		return -1;
	}

	SendDataToBoard(in, KEYLEN);

	if (state = GetSignalFromBoard(&receiveSignal)) {
		printf("Data Send Fail : Code %d\n", state);
		return -1;
	}

	GetDataFromBoard(out, KEYLEN);

	for (int i = 0; i < KEYLEN; i++) {
		printf("%02x ", out[i]);
	}

	printf("%d\n", strncmp(ref, out, KEYLEN));

	return 0;
}


int Init() {
	int state;

	// Connect Serial Port 
	if (state = SerialPortConnect()) {
		printf("Error code %d : Connect Serial Port Failed..\n", state);
		return 1;
	}

	// Open Log File
	//if (state = FileOpen()) {
	//	printf("Error code %d : Open File Failed..\n", state);
	//	return 1;
	//}

	printf("Log : Initialize Complete!\n\n");

	return 0;
}

