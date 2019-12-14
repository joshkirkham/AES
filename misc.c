#include "misc.h"

#include <stdint.h>
#include <stdio.h>
#include "aes.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



/*
 * Pre:
 * 	bytes: bytes to be converted
 * 	hex: where to write hex to
 * 	bytesLen: lenght of byte array
 */
void bytesToHex(uint8_t* bytes, int bytesLen,  char* hex) {
	for (int i = 0; i < bytesLen; ++i) {
		//printf("%d ", bytes[i]);
		hex[2*i+1] =  byteToHex(bytes[i] & 0x0F);
		hex[2*i] = byteToHex((bytes[i] >> 4) & 0x0F);
	}

}

char byteToHex(uint8_t byte) {
	//printf("%d\n", byte);
	if (byte < 10) {
		return '0' + byte;
	}
	return 'A' + byte - 10;
}



void hexToBytes(char* hex, int hexLen, uint8_t* bytes) {
	for (int i = 0; i < hexLen; i+=2) {
		bytes[i/2] = hexToByte(hex[i+1]);
		//printf("%d\n", hexToByte(hex[i+1]));
		bytes[i/2] |= hexToByte(hex[i]) << 4;
	}
}



uint8_t hexToByte(char c1) {
	if (c1 == 0) {
		return 0;
	}

	if (c1 <= '9' && c1 >= '0')  {
		return c1 - '0';
	}
	return c1 - 'A' + 10;
}


void toUpperCase(char* s) {
	for (int i = 0; i < strlen(s); ++i) {
		s[i] = toupper(s[i]);
	}
}



/**REIMPLEMENT THIS TO BUFFER BETTER FOR LONGER STIRNGS*/
void printState(State s) {
	char* hexbuff = calloc(33, sizeof(char));
	uint8_t* debugBuffer = calloc(16, sizeof(uint8_t));
	readState(s, debugBuffer);
	bytesToHex(debugBuffer, 16, hexbuff);

	printf("%s\n", hexbuff);
	free(hexbuff);
	free(debugBuffer);
}


void zeroState(State s) {
	for (int c = 0; c < 4; ++c) {
		for (int r = 0; r < 4; ++r) {
			s[r][c] = 0; 
		}
	}
}


void writeState(State s, uint8_t* bytes) {
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			s[row][col] = bytes[row + 4*col];
		}
	}
}

void readState(State s, uint8_t* bytes) {
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			bytes[row + 4*col] = s[row][col];
		}
	}
}



