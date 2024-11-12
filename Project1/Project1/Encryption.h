#pragma once

#include <stdio.h>

#include "RandomBytes.h"
#include "Params.h"

void Encryption(uint8_t ciphertext[CIPHER_TEXT_SIZE], uint8_t originText[PLAIN_TEXT_SIZE], uint8_t publicKey[SECRET_KEY_SIZE]);