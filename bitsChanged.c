/** Code for comparing two strings of bits for my analysis 
 * It is not part of the aes program, but requires some headers to run
 */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "aes.h"
#include "misc.h"




int diffBits(uint8_t a, uint8_t b) {
	int count = 0;
	uint8_t mask = 1;
	for (int i = 0; i < 7; ++i) {
		if ((a & mask) != (b & mask)) {
			++count;
		}
		mask <<= 1;
	}

	return count;
}




int main(int argc, char** argv) {

	int s1len = strlen(argv[1]);
	int s2len = strlen(argv[2]);
	uint8_t* b1 = calloc(s1len / 2, sizeof(uint8_t));
	uint8_t* b2 = calloc(s2len / 2, sizeof(*b2));

	hexToBytes(argv[1], s1len, b1);
	hexToBytes(argv[2], s2len, b2);

	int notsame = 0;
	int sum = 0;
	for (int i = 0; i < s1len/2 && i < s2len/2; ++i) {
		int k = diffBits(b1[i], b2[i]);
		sum += k;
		notsame += 8 - k;

		printf("%d ", k);
		for (int q = 0; q < k; ++q) {
			putchar('=');
		}

		putchar('\n');

	}
	printf(" [%d]\n", sum);
	printf("same  [%d]\n", notsame);

	return 0;
				


}





