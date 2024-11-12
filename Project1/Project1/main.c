#include <stdio.h>
#include <string.h>

#include "Params.h"
#include "Encryption.h"
#include "LogFileWrite.h"
#include "KeyReference.h"
#include "SerialConnection.h"

// CRYSTALS-KYBER
unsigned char publicKey[PUBLIC_KEY_SIZE] = PUBLIC_KEY_REF;
unsigned char secretKey[SECRET_KEY_SIZE] = SECRET_KEY_REF;

unsigned char cipherText[CIPHER_TEXT_SIZE];
unsigned char plainText[PLAIN_TEXT_SIZE];
unsigned char originText[PLAIN_TEXT_SIZE];

int Verify();

int main() {
	int state;

	if (state = SerialPortConnect()) {
		printf("Error code %d : Connect Serial Port Failed..\n", state);
		//return 1;
	}
	else {
		printf("Log : Connect Serial Port Successful!\n");
	}

	if (state = FileOpen()) {
		printf("Error code %d : Open File Failed..\n", state);
		//return 1;
	}
	else {
		WriteLog(publicKey, secretKey);
		printf("Log : Open File Successful!\n");
	}

	if (state = SendKey(secretKey)) {
		printf("Error code %d : Send Key Failed..\n", state);
		//return 1;
	}
	else {
		printf("Log :Send Key Successful!\n");
	}

	// 새로운 메시지, 암호문 만들기
	for (int round = 1; round <= MAX_ROUND; round++) {
		printf("\n\nRound : %d\n", round);


		Encryption(cipherText, originText, publicKey);


		int result = Decryption(cipherText, plainText);

		if (result) {
			printf("Error code %d : Decryption Failed..\n", result);
		}


		FileWrite(round, originText, Verify());
	}

	FileClose();
}

int Verify() {
	if (!strncmp(plainText, originText, PLAIN_TEXT_SIZE)) {
		return 0;
	}
	else {
		return 1;
	}
}