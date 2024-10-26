#pragma once

#include "main.h"

#define SECRETKEYBYTES 1152
#define CIPHERTEXTBYTES 1088
#define PLAINTEXTBYTES 32

#define TIMEOUT 100

typedef unsigned char uint8_t;

void SetSecretKey(UART_HandleTypeDef *huart, uint8_t* SecretKey);
void Decryption(uint8_t* PlainText, const uint8_t* CipherText, const uint8_t* SecretKey);
void GetCipherText(UART_HandleTypeDef *huart, uint8_t* CipherText);
void PrintPlainText(UART_HandleTypeDef *huart, const uint8_t* PlainText);

// Debug
void PrintSecretKey(UART_HandleTypeDef *huart, const uint8_t* SecretKey);
void PrintCipherText(UART_HandleTypeDef *huart, const uint8_t* CipherText);