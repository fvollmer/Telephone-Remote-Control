#ifndef CONFIG_H
#define CONFIG_H

#include <stc12.h>

SFR(P5, 0xC8);
  SBIT(P5_0, 0xC8, 0);
  SBIT(P5_1, 0xC8, 1);
  SBIT(P5_2, 0xC8, 2);
  SBIT(P5_3, 0xC8, 3);
  SBIT(P5_4, 0xC8, 4);
  SBIT(P5_5, 0xC8, 5);

SFR(T2L, 0xD7);
SFR(T2H, 0xD6);

#define T1kHz (0xffff-FOSC/1000)

#define PICKUP_PHONE P5_4
#define RELAY_1 P3_6
#define RELAY_2 P3_7

#define NSET P3_1
#define NCALL_DETECT P3_3
#define DV P3_2
#define AUDIO_OUT P5_5

#define RELAY_STATE_ADDRESS 0x0100
#define PIN_ADDRESS 0x0200

#define PIN_LENGTH 6

#endif // CONFIG_H
