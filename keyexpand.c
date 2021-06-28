#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "sbox.h"
#include "keyexpand.h"

static uint16_t round_const = 1;

void Expand128(uint8_t* initial_key, uint8_t* expanded_key) {
	memcpy(expanded_key, initial_key, 16*sizeof(uint8_t));
	int i = 16;
	while (i < 176) {

		for (int j = 0; j < 4; ++j) {
			//last 4 bytes
			uint8_t temp1[4];
			for (int q = 0; q < 4; ++q) {
				temp1[q] = expanded_key[i-4+q];
			}

			if (j == 0) { KeyExpansionCore(temp1); }

			// first 4 bytes of last 16
			uint8_t* temp2 = expanded_key + i - 16;

			for (int k = 0; k < 4; ++k) {
				expanded_key[i+k] = temp1[k] ^ temp2[k];
			}
			i += 4;

		}
	}
}

void Expand192(uint8_t* initial_key, uint8_t* expanded_key) {
	memcpy(expanded_key, initial_key, 24*sizeof(uint8_t));
	int i = 24;
	while (i < 208) {

		for (int j = 0; j < 6; ++j) {
			//last 4 bytes
			uint8_t temp1[4];
			for (int q = 0; q < 4; ++q) {
				temp1[q] = expanded_key[i-4+q];
			}

			if (j == 0) { KeyExpansionCore(temp1); }

			// first 4 bytes of last 24
			uint8_t* temp2 = expanded_key + i - 24;

			for (int k = 0; k < 4; ++k) {
				expanded_key[i+k] = temp1[k] ^ temp2[k];
			}
			i += 4;

		}
	}
}

void Expand256(uint8_t* initial_key, uint8_t* expanded_key) {
	memcpy(expanded_key, initial_key, 32*sizeof(uint8_t));
	int i = 32;
	while (i < 240) {

		for (int j = 0; j < 8; ++j) {
			//last 4 bytes
			uint8_t temp1[4];
			for (int q = 0; q < 4; ++q) {
				temp1[q] = expanded_key[i-4+q];
			}

			if (j == 0) { KeyExpansionCore(temp1); }
			if (j == 4) {
				for (int q = 0; q < 4; ++q) {
					temp1[q] = sbox[temp1[q]];
				}
			}


			//first 4 bytes of last 32
			uint8_t* temp2 = expanded_key + i - 32;

			for (int k = 0; k < 4; ++k) {
				expanded_key[i+k] = temp1[k] ^ temp2[k];
			}
			i += 4;

		}
	}
}








void KeyExpansionCore(uint8_t* key) {
	RotWord(key);
	SubWord(key);
	RCon(key);
}

void SubWord(uint8_t* key) {
	for (int i = 0; i < 4; ++i) {
		key[i] = sbox[key[i]];
	}
}

void RotWord(uint8_t* key) {
	uint8_t tmp = key[0];
	key[0] = key[1];
	key[1] = key[2];
	key[2] = key[3];
	key[3] = tmp;
}





void RCon(uint8_t* key) {

	key[0] ^= round_const;

	//tricky bitwise way of saying
	//multiply the polynomial by x
	//and then mod it by the aes polynomial (0x11b if its first bit was 
	//1 before shifting
	round_const = (round_const << 1) ^ (0x11b & -(round_const >> 7));


}


