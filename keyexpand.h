/** Functions for performing key expansions. Most of these are documented
 * in the AES spec, but the pseudo code on the class slides was better
 * so I used them as a model
 */

/** Functions for the key expansion core **/
void SubWord(uint8_t* key);
void RotWord(uint8_t* key);
void RCon(uint8_t* key);
void KeyExpansionCore(uint8_t* key);


/** Functions to expand a key to a certain length
 * pre
 * 		initial_key and expanded_key must be pre initialized
 * 		to the proper sizes
 */
void Expand128(uint8_t* initial_key, uint8_t* expanded_key);
void Expand192(uint8_t* initial_key, uint8_t* expanded_key);
void Expand256(uint8_t* initial_key, uint8_t* expanded_key);


