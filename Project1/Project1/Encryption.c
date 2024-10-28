#include "Encryption.h"
#include "kem.h"

void Encryption(uint8_t ciphertext[CIPHER_TEXT_SIZE], uint8_t originText[PLAIN_TEXT_SIZE], uint8_t publicKey[SECRET_KEY_SIZE])
{
	crypto_kem_enc(ciphertext, originText, publicKey);

	printf("originText : ");
	for (int i = 0; i < PLAIN_TEXT_SIZE; i++) {
		printf("%02x", originText[i]);
	}

	printf("\n");
}
