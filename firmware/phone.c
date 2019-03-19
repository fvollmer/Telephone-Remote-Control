#include "config.h"
#include "phone.h"
#include "time.h"

volatile static bool make_beep_sound = false;
volatile static bool dv_rising = false;
volatile bool ringing_detected = false;

void beep_interrupt_fun(void){
  if(make_beep_sound == true){
    AUDIO_OUT ^= 1;
  }
}

void dv_edge_interrupt_fun(void){
  dv_rising |= INT0; // set dv_rising if there was a rising edge
}

void ringing_edge_interrupt_fun(void){
  ringing_detected |= INT1; // set dv_rising if there was a rising edge
}

void beep(uint8_t number, uint16_t length){
  for(uint8_t i = 0; i<number;i++){
    if(i>0){
      delay_ms(length);
    }
    make_beep_sound = true;
    delay_ms(length);
    make_beep_sound = false;
    AUDIO_OUT = 0; // ensure that output is low
  }
}

enum digit get_digit(void){
  if(dv_rising) {
    // there was a new valid digit
    enum digit ret = P1 & 0xF;
    dv_rising = false;
        while(INT0){
          // block until user releases key
        }
        timeout_reset();
        return ret;
  } else {
    return DIGIT_NONE;
  }
}
