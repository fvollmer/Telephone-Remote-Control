#ifndef TIME_H
#define TIME_H

#include <stdint.h>
#include <stdbool.h>



void time_increase_1ms(void);

void timeout_reset(void);

bool timeout(uint16_t ms);

void delay_ms(uint16_t ms);

#endif // TIME_H
