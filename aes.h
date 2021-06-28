/**
 * A set of functions implementing the AES standard. All the functions are documented
 * in the AES specification
 */

#ifndef __AES_H__
#define __AES_H__

#include <stdint.h>


#define WORD_SZ 4
#define BLOCK_SZ 16

/* The State array is a 4x4 double array. All functions dealing with converting
 * arrays of bytes and States will follow the convention in the AES spec, namely:
 * bytes are read into the State by column not row
 */
typedef uint8_t State [4][WORD_SZ];


void Cipher(State s, uint8_t* key, uint8_t keylen);
void SubBytes(State);
void ShiftRows(State);
void MixColumns(State);
void AddRoundKey(State, uint8_t* roundkey);

void InvCipher(State s, uint8_t* key, uint8_t keylen);
void InvSubBytes(State);
void InvShiftRows(State);
void InvMixColumns(State);
void InvAddRoundKey(State, uint8_t* roundkey);


#endif
