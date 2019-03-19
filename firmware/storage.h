#ifndef STORAGE_H
#define STORAGE_H
#include <stdint.h>

void store_pin(const char* const pin, uint8_t length);

void restore_pin(char* const pin, uint8_t length);

void store_relay_state(void);

void restore_relay_state(void);

#endif // STORAGE_H
