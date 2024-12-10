#ifndef PARAMS_H
#define PARAMS_H

/*****************************************************************************/
/* Defines:                                                                  */
/*****************************************************************************/
// The number of columns comprising a state in AES. This is a constant in AES. Value=4
#define Nb 4
// The number of 32 bit words in a key.
#define Nk 4
// Key length in bytes [128 bit]
#define KEYLEN 16
// The number of rounds in AES Cipher.
#define Nr 10

#define SIGNAL_SIZE 2
#define SAMPLE_COUNT 50

#define MAX_ROUND 5

/* Don't change parameters below this line */

#define KEY_SEND_START_SIGNAL "0\0"
#define DECRYPTION_START_SIGNAL "1\0"
#define INPUT_MESSAGE "\
===========================\n\n\n\
Home\n\
0 : Exit\n\
1 : DPA\n\
2 : Print Current Setting\n\
3 : Create Origin Text\n\
4 : Create Key\n\
input : \n"

#endif