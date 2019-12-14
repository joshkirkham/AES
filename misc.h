#include <stdint.h>
#include "aes.h"

char byteToHex(uint8_t byte);
uint8_t hexToByte(char c1);

void bytesToHex(uint8_t* bytes, int bytesLen,  char* hex);
void hexToBytes(char* hex, int hexLen, uint8_t* bytes);


void printState(State s);



void writeState(State s, uint8_t* bytes);
void readState(State s, uint8_t* bytes);


void toUpperCase(char* c);
