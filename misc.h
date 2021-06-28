/**********
 * Misc. functions for manipulating arrays of hex characters, bytes, and 
 * State arrays
 */

#include <stdint.h>
#include "aes.h"

/* Convert a byte to a hex character
 * pre: byte < 16
 */
char byteToHex(uint8_t byte);

/* Converts a hex string to a byte */
uint8_t hexToByte(char c1);

/* Converts an array of bytes to a hex string
 * pre
 * 		bytes = array of bytes
 * 		bytesLen = len(bytes)
 * 		hex = array of char, len >= 2*bytesLen + 1
 */
void bytesToHex(uint8_t* bytes, int bytesLen,  char* hex);

/* Converts a string of hex to an array of bytes
 * pre
 * 		hex = array of hex chars
 * 		hexLen = len(hex)
 * 		bytes = array of len >= hexLen / 2
 */
void hexToBytes(char* hex, int hexLen, uint8_t* bytes);


/* Prints out state object in human readable form */
void printState(State s);



/* Writes a buffer into a proper State array */
void writeState(State s, uint8_t* bytes);


/* Reads a proper State into an array of byte */
void readState(State s, uint8_t* bytes);

/* Converts all characters in a string to upper case */
void toUpperCase(char* c);
