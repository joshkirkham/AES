
#include "galois.h"

uint8_t mul2(uint8_t a) {
	return (a << 1) ^ (0x1b & -(a>>7));
}

/** 2 * a + a*/
uint8_t mul3(uint8_t a) {
	return mul2(a) ^ a;
}



uint8_t mul9(uint8_t a) {
	return mul2(mul2(mul2(a))) ^ a;
}

uint8_t mulB(uint8_t a) {
	return a ^ mul2( a ^ mul2( mul2(a)));
}

uint8_t mulD(uint8_t a) {
	return a^ mul2( mul2( a ^ mul2(a)));
}

uint8_t mulE(uint8_t a) {
	return mul2( a ^ mul2 ( a ^ mul2(a)));
}

