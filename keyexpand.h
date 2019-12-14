void SubWord(uint8_t* key);
void RotWord(uint8_t* key);
void RCon(uint8_t* key);
void KeyExpansionCore(uint8_t* key);
void Expand128(uint8_t* initial_key, uint8_t* expanded_key);
void Expand192(uint8_t* initial_key, uint8_t* expanded_key);
void Expand256(uint8_t* initial_key, uint8_t* expanded_key);


