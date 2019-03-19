#ifndef DTMF_H
#define DTMF_H

#include <stdbool.h>
#include <stdint.h>

enum digit {
  DIGIT_1=1,
  DIGIT_2=2,
  DIGIT_3=3,
  DIGIT_4=4,
  DIGIT_5=5,
  DIGIT_6=6,
  DIGIT_7=7,
  DIGIT_8=8,
  DIGIT_9=9,
  DIGIT_0=10,
  DIGIT_STAR=11,
  DIGIT_POUND=12,
  DIGIT_A=13,
  DIGIT_B=14,
  DIGIT_C=15,
  DIGIT_D=0,
  DIGIT_NONE=0xff
};

extern volatile bool ringing_detected;

void beep_interrupt_fun(void);

void dv_edge_interrupt_fun(void);

void ringing_edge_interrupt_fun(void);

/**
 * @brief get_digit reads the next digit. This function is blocking until dtmf tone stops
 * @return received digit or DIGIT_NONE if there was no digit
 */
enum digit get_digit(void);

void beep(uint8_t number, uint16_t length);

#endif // DTMF_H
