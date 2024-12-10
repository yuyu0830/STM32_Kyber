#include <string.h>

#include "Encryption.h"
#include "kem.h"

void GetNewOriginText(uint8_t *ct, 
					  uint8_t *ot, 
					  const uint8_t pk[SECRET_KEY_SIZE])
{
	uint8_t tmp_ct[CIPHER_TEXT_SIZE];
	uint8_t tmp_ot[ORIGIN_TEXT_SIZE];
	uint8_t tmp_ss[KYBER_SYMBYTES];
		
	crypto_kem_enc(tmp_ct, tmp_ot, tmp_ss, pk);

	memcpy(ct, tmp_ct, CIPHER_TEXT_SIZE);
	memcpy(ot, tmp_ot, ORIGIN_TEXT_SIZE);
	//memcpy(ss, tmp_ss, KYBER_SYMBYTES);
	
}
