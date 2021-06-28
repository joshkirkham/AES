/** The thing which actually implements the program. Documentation can be 
 * found in README.txt */

#include "aes.h"
#include "keyexpand.h"
#include "misc.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>





/**
 * RETURN:
 * 		0: Success
 * 		1: Invalid invocation
 */
int main(int argc, char** argv) {

	// Parse the arg vector into a set of variables
	bool DECRYPT = false;
	bool CBC = false;
	char* hexkey = NULL;
	char* text = NULL;
	char* hexIV = NULL;

	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-d"))
			DECRYPT = true;

		else if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--cbc")) {
			CBC = true;
			hexIV = argv[++i];

		}

		else if (!strcmp(argv[i], "-k"))
			hexkey = argv[++i];
			
		else if (!strcmp(argv[i], "-t"))
			text = argv[++i];

	}

	if (text == NULL || hexkey == NULL) {
		printf("Enter a key and plain/ciphertext\n");
		exit(1);
	}

	toUpperCase(hexkey);
	toUpperCase(text);



	// Determine the number of rounds needed
	int keylen = strlen(hexkey);

	int nRounds;
	switch(keylen) {
		case 32: nRounds = 10; break;
		case 48: nRounds = 12; break;
		case 64: nRounds = 14; break;
		default:
			printf("Invalid key size\n");
			exit(1);
	}

	// Convert the key to bytes
	uint8_t* key = calloc(keylen / 2, sizeof(uint8_t));
	hexToBytes(hexkey, keylen, key);


	// Convert IV to bytes
	uint8_t* IV; //Holds the chain of IV ^ text ^ text ^ ...
	uint8_t* chain;    //Holds a separate copy of IV for use in encryption
	if (CBC) {
		chain = calloc(16, sizeof(int8_t));
		IV = calloc(16, sizeof(int8_t));
		hexToBytes(hexIV, 32, chain);
		memcpy(IV, chain, 16);
	}

	// Expand the key
	uint8_t* expanded = calloc((nRounds + 2) * BLOCK_SZ, sizeof(uint8_t));

	switch(keylen) {
		case 32: Expand128(key, expanded); break;
		case 48: Expand192(key, expanded); break;
		case 64: Expand256(key, expanded); break;
	}


	int inputlen = strlen(text);
	State s;
	int i = 0;

	// Temporary arrays for doing hex/byte conversions
	char* hex = calloc(33, sizeof(char));
	uint8_t* bytes = calloc(16, sizeof(int8_t));


	//Perform the cipher for each block of input
	while (i < inputlen) {
		strncpy(hex, text + i, 32);
		i  += 32;
		hexToBytes(hex, 32, bytes);
		writeState(s, bytes);


		switch (DECRYPT) {
			case true: 
				if (CBC) { 
					memcpy(IV, chain, 16);
					readState(s, chain);
				}
				InvCipher(s, expanded, keylen); 
				if (CBC) { AddRoundKey(s, IV); }
				break;

			case false: 
				if (CBC) { AddRoundKey(s, IV); }
				Cipher(s, expanded, keylen); 
				if (CBC) { readState(s, IV); }
				break;
		}
		readState(s, bytes);
		bytesToHex(bytes, 16, hex);
		printf("%s\n", hex);
	}

	
	// cleanup
	if (CBC) { free(chain); free(IV); }
	free(hex);
	free(bytes);
	free(key);
	free(expanded);

}


	
	







