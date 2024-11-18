#include <stdio.h>
#include <string.h>

#include "Params.h"
#include "Encryption.h"
#include "kem.h"
#include "LogFileWrite.h"
#include "KeyReference.h"
#include "SerialConnection.h"

//enum Input {
//	Decryption = 1,
//	PrintCurrentSetting,
//	ChangeOriginText,
//};

// CRYSTALS-KYBER
// Current Setting
unsigned char pk[PUBLIC_KEY_SIZE] = PUBLIC_KEY_REF;    // Public Key
unsigned char sk[SECRET_KEY_SIZE] = SECRET_KEY_REF;    // Secret Key

unsigned char ss[SAMPLE_COUNT][KYBER_SYMBYTES] = { 0, }; // Shared Secret
unsigned char ot[SAMPLE_COUNT][ORIGIN_TEXT_SIZE] = { 0, };  // Origin Text
unsigned char ct[SAMPLE_COUNT][CIPHER_TEXT_SIZE] = { 0, }; // Cipher Text

// Differential Power Analysis
unsigned char ts[KYBER_SYMBYTES];
unsigned char tk[SECRET_KEY_SIZE] = TEMP_KEY_REF;  // Temporary Key
unsigned char pt[ORIGIN_TEXT_SIZE] = ORIGIN_TEXT_REF;  // Plain Text

// Function
int Init();
int Verify();

int main() {

	
	//for (int i = 0; i < PLAIN_TEXT_SIZE; i++) {
		//printf("%02x", pt[i]);
	// }

	/*Init();

	int input = 1;

	while (input != 0) {
		printf(INPUT_MESSAGE);

		scanf_s("%d", &input);

		switch (input) {
		case Decryption:

			break;

		case PrintCurrentSetting:

			break;

		case ChangeOriginText:

			break;

		default:

		}
	}*/

	// 새로운 메시지, 암호문 만들기
	/*for (int round = 1; round <= 1; round++) {
		printf("\n\nRound : %d\n", round);


		Encryption(ct, ot, pk);


		int result = Decryption(ct, pt);

		if (result) {
			printf("Error code %d : Decryption Failed..\n", result);
		}


		FileWrite(round, ot, Verify());
	}*/

	//SaveSetting(pk, sk, ct, ot, tk);
	//FileClose();
}

int Init() {
	int state;

	// Load Setting
	if (state = LoadSetting(pk, sk, tk)) {
		printf("Error code %d : Load Setting Failed..\n", state);
		// return 1;
	}
	else {
		printf("Log : Load Setting Successful!\n");
	}

	// Load Setting
	if (state = LoadMessage(ot, ct, ss)) {
		printf("Error code %d : Load Message Failed..\n", state);
		// return 1;
	}
	else {
		printf("Log : Load Message Successful!\n");
	}

	// Connect Serial Port 
	if (state = SerialPortConnect()) {
		printf("Error code %d : Connect Serial Port Failed..\n", state);
		// return 1;
	}
	else {
		printf("Log : Connect Serial Port Successful!\n");
	}

	// Open Log File
	if (state = FileOpen()) {
		printf("Error code %d : Open File Failed..\n", state);
		// return 1;
	}
	else {
		WriteLog(pk, sk);
		printf("Log : Open File Successful!\n");
	}

	// Send Key To Board
	if (state = SendKey(sk)) {
		printf("Error code %d : Send Key Failed..\n", state);
		// return 1;
	}
	else {
		printf("Log : Send Key Successful!\n");
	}

	printf("Log : Initialize Complete!\n\n");

	return 0;
}

int Verify() {
	if (!strncmp(pt, ot, ORIGIN_TEXT_SIZE)) {
		return 0;
	}
	else {
		return 1;
	}
}