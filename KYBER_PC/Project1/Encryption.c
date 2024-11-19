#include <string.h>

#include "Encryption.h"
#include "kem.h"

void GetNewOriginText(uint8_t *ct, 
					  uint8_t *ot, 
					  uint8_t *ss,
					  const uint8_t pk[SECRET_KEY_SIZE])
{
	for (int i = 0; i < SAMPLE_COUNT; i++) {
		uint8_t tmp_ct[CIPHER_TEXT_SIZE];
		uint8_t tmp_ot[ORIGIN_TEXT_SIZE];
		uint8_t tmp_ss[KYBER_SYMBYTES];
		
		crypto_kem_enc(tmp_ct, tmp_ot, tmp_ss, pk);

		memcpy(ct + (CIPHER_TEXT_SIZE * i), tmp_ct, CIPHER_TEXT_SIZE);
		memcpy(ot + (ORIGIN_TEXT_SIZE * i), tmp_ot, ORIGIN_TEXT_SIZE);
		memcpy(ss + (KYBER_SYMBYTES * i), tmp_ss, KYBER_SYMBYTES);
	}
	
	//printf("originText : ");
	//for (int i = 0; i < PLAIN_TEXT_SIZE; i++) {
	//	printf("%02x", ot[i]);
	//}
	//printf("\n");
}
