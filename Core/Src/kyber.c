#include "kyber.h"

void SetSecretKey(UART_HandleTypeDef *huart, uint8_t* SecretKey) {
    HAL_UART_Receive_IT(&huart, &SecretKey, SECRETKEYBYTES);
}

void Decryption(uint8_t* PlainText, const uint8_t* CipherText, const uint8_t* SecretKey) {
    indcpa_dec(PlainText, CipherText, SecretKey);
}

void GetCipherText(UART_HandleTypeDef *huart, uint8_t* CipherText) {
    HAL_UART_Receive_IT(&huart, &CipherText, CIPHERTEXTBYTES);
}

void PrintPlainText(UART_HandleTypeDef *huart, const uint8_t* PlainText) {
    HAL_UART_Transmit(&huart, PlainText, strlen((char *)PlainText), TIMEOUT);
}

// Debug
void PrintSecretKey(UART_HandleTypeDef *huart, const uint8_t* SecretKey) {
    HAL_UART_Transmit(&huart, SecretKey, strlen((char *)SecretKey), TIMEOUT);
}

void PrintCipherText(UART_HandleTypeDef *huart, const uint8_t* CipherText) {
    HAL_UART_Transmit(&huart, CipherText, strlen((char *)CipherText), TIMEOUT);
}