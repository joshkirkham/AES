/* Functions for multiplying inside the AES galois field. I got a bit lazy, and just 
 * implemented every multiplication I needed as its own function in terms of 
 * multiplication by 2 and addition of 1.
 */

#include <stdint.h>

uint8_t mul2(uint8_t a);

uint8_t mul3(uint8_t a);



uint8_t mul9(uint8_t a);

uint8_t mulB(uint8_t a);

uint8_t mulD(uint8_t a);

uint8_t mulE(uint8_t a);

