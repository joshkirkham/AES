#include "aes.h"
#include "misc.h"
#include "sbox.h"
#include "invsbox.h"
#include <stdlib.h>
#include <stdio.h>
#include "galois.h"




void Cipher(State s, uint8_t* key, uint8_t keylen) {
	uint8_t nRounds;

	switch(keylen / 8) {
		case 4: nRounds = 10; break;
		case 6: nRounds = 12; break;
		case 8: nRounds = 14; break;
	}

	char* debugBuffer = calloc(33, sizeof(char));

	//printState(s);
	AddRoundKey(s, key);
	//printState(s);

	int round;
	for (round = 1; round < nRounds; ++round) {
		SubBytes(s);
		//printState(s);
		ShiftRows(s);
		//printState(s);

		//printf("mixcolumns ");
		MixColumns(s);
		//printState(s);


		/*
		char* hex = calloc(33, sizeof(char));
		bytesToHex(key + (round * BLOCK_SZ), 16, hex);
		printf("Round Key %d: %s\n", round, hex);
		free(hex);
		*/


		AddRoundKey(s, key + (round * BLOCK_SZ));
	//	printState(s);
	}

	SubBytes(s);
	//printState(s);
	ShiftRows(s);
	//printState(s);
	AddRoundKey(s, key + (round * BLOCK_SZ));
	//printState(s);

	free(debugBuffer);
}

void InvCipher(State s, uint8_t* key, uint8_t keylen) {
	uint8_t nRounds;

	switch(keylen / 8) {
		case 4: nRounds = 10; break;
		case 6: nRounds = 12; break;
		case 8: nRounds = 14; break;
	}

	char* debugBuffer = calloc(33, sizeof(char));

	//printState(s);
	AddRoundKey(s, key + BLOCK_SZ * (nRounds));
	//printState(s);

	int round;
	for (round = nRounds - 1; round > 0; --round) {
		InvShiftRows(s);
		//printf("InvShiftRows ");printState(s);

		InvSubBytes(s);
		//printf("InvSubBytes ");printState(s);


		
		char* hex = calloc(33, sizeof(char));
		bytesToHex(key + (round * BLOCK_SZ), 16, hex);
		//printf("Round Key %d: %s\n", round, hex);
		free(hex);
		


		//printf("InvAddRoundKey ");
		AddRoundKey(s, key + (round * BLOCK_SZ));
		//printState(s);


		//printf("InvMixColumns ");
		InvMixColumns(s);
		//printState(s);

		
	}
	InvShiftRows(s);
	//printState(s);


	InvSubBytes(s);
	//printState(s);

	InvAddRoundKey(s, key);
	//printf("=========");
	//printState(s);

	free(debugBuffer);
}


void SubBytes(State s) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			//printf("%d -> %d\n", s[i][j], sbox[s[i][j]]);
			s[i][j] = sbox[s[i][j]];
		}
	}
}

void InvSubBytes(State s) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			//printf("%x -> %x\n", s[i][j], sbox[s[i][j]]);
			s[i][j] = invsbox[s[i][j]];
		}
	}
}




void ShiftRows(State s) {
	uint8_t tmp[4];
	for (int row = 1; row < 4; ++row) {
		for (int j = 0; j < 4; ++j) 
			tmp[j] = s[row][j];

		for (int j = 0; j < 4; ++j) 
			s[row][j] = tmp[(row+j) % 4];
	}
}


void InvShiftRows(State s) {
	uint8_t tmp[4];
	for (int row = 1; row < 4; ++row) {
		for (int j = 0; j < 4; ++j) 
			tmp[j] = s[row][j];

		for (int j = 0; j < 4; ++j) 
			s[row][j] = tmp[(j+4-row) % 4];
	}
}





void MixColumns(State s){
	uint8_t newColumn [4];
	for (int col = 0; col < 4; ++col)  {
		newColumn[0] = mul2(s[0][col]) ^ 	mul3(s[1][col]) ^	   s[2][col]    ^    s[3][col];
		newColumn[1] =    s[0][col]  ^ 	mul2(s[1][col]) ^ mul3(s[2][col]) 	^    s[3][col];
		newColumn[2] =    s[0][col]  ^ 	   s[1][col]  ^ mul2(s[2][col]) 	^ mul3(s[3][col]);
		newColumn[3] = mul3(s[0][col]) ^ 	   s[1][col]  ^    s[2][col] 	^ mul2(s[3][col]);


		for (int i = 0; i < 4; ++i) {
			s[i][col] = newColumn[i];
		}
	}
}

void InvMixColumns(State s){
	uint8_t newColumn [4];
	for (int col = 0; col < 4; ++col)  {
		newColumn[0] =	mulE(s[0][col]) ^ mulB(s[1][col]) ^ mulD(s[2][col]) ^ mul9(s[3][col]);
		newColumn[1] =	mul9(s[0][col]) ^ mulE(s[1][col]) ^ mulB(s[2][col]) ^ mulD(s[3][col]);
		newColumn[2] =	mulD(s[0][col]) ^ mul9(s[1][col]) ^ mulE(s[2][col]) ^ mulB(s[3][col]);
		newColumn[3] =	mulB(s[0][col]) ^ mulD(s[1][col]) ^ mul9(s[2][col]) ^ mulE(s[3][col]);

		for (int i = 0; i < 4; ++i) {
			s[i][col] = newColumn[i];
		}
	}
}




void AddRoundKey(State s, uint8_t* rk) {
/*	char* hex = calloc(33, sizeof(char));
	bytesToHex(rk, 16, hex);
	printf("Round Key: %s\n", hex);
	free(hex);*/
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			s[row][col] ^= rk[row + 4*col];
		}
	}
}




void InvAddRoundKey(State s, uint8_t* rk) {
	AddRoundKey(s, rk);
}




