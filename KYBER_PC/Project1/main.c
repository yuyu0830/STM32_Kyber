#include <stdio.h>
#include <string.h>

#include "indcpa.h"
#include "Params.h"
#include "Encryption.h"
#include "LogFileWrite.h"
#include "KeyReference.h"
#include "SerialConnection.h"

// CRYSTALS-KYBER
unsigned char publicKey[PUBLIC_KEY_SIZE] = PUBLIC_KEY_REF;
unsigned char secretKey[SECRET_KEY_SIZE] = SECRET_KEY_REF;

unsigned char cipherText[CIPHER_TEXT_SIZE];
unsigned char plainText[ORIGIN_TEXT_SIZE];
unsigned char originText[ORIGIN_TEXT_SIZE];

int main() {
	if (SerialPortConnect()) {
		printf("Connect Serial Port Failed..\n");
		//return 1;
	}

	if (FileOpen()) {
		printf("Open File Failed..\n");
		//return 1;
	}

	if (SendKey(secretKey)) {
		printf("Send Key Failed..\n");
		//return 1;
	}

	// 새로운 메시지, 암호문 만들기
	for (int round = 1; round <= MAX_ROUND; round++) {
		printf("\nRound : %d\n", round);

		GetNewOriginText(cipherText, originText, publicKey);
		//Decryption(cipherText, plainText);
		indcpa_dec(plainText, cipherText, secretKey);

		printf("plaintext  : ");
		for (int i = 0; i < ORIGIN_TEXT_SIZE; i++) 
			printf("%02x", plainText[i]);
		
		printf("\norigintext : ");
		for (int i = 0; i < ORIGIN_TEXT_SIZE; i++) 
			printf("%02x", originText[i]);
		
		printf("\n");

		if (strncmp(plainText, originText, ORIGIN_TEXT_SIZE)) {
			printf("Decryption Fail..\n");
			break;
		}

		printf("Success!\n");
		SaveMessage(cipherText);
	}

	FileClose();
}