#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "isr.h"
#include "util.h"
#include "phone.h"
#include "time.h"
#include "storage.h"

static enum state {INIT,
                   WAITING,
                   CALL_DETECTED,
                   PICKUP,
                   AUTHENTICATION_START,
                   AUTHENTICATION,
                   CONTROL,
                   CONFIGURATION_START,
                   CONFIGURATION}
                   state = INIT;

static char pin[PIN_LENGTH];

/**
 * @brief do_control interprets user dtmf tones to switch relays:
 * 1 -> switch relay 1 on
 * 2 -> switch relay 1 off
 * 4 -> switch relay 2 on
 * 5 -> switch relay 2 off
 * * -> hang up
 * Any received digit will reset the timeout. This function is blocking until dtmf tone stopped.
 * @return true if * was received and line should be hung up
 */
bool do_control(void){
  enum digit digit = get_digit();

  switch (digit) {
  case DIGIT_1:
    RELAY_1 = 1;
    store_relay_state();
    beep(1, 100);
    break;
  case DIGIT_2:
    RELAY_1 = 0;
    store_relay_state();
    beep(2, 100);
    break;
  case DIGIT_4:
    RELAY_2 = 1;
    store_relay_state();
    beep(4, 100);
    break;
  case DIGIT_5:
    RELAY_2 = 0;
    store_relay_state();
    beep(5, 100);
    break;
  case DIGIT_STAR:
    return true;
    break;
  default:
    //skip
    break;
  }

  return false;
}


void init(void){
  // initialize I/O Ports
  AUDIO_OUT = 0;
  RELAY_1 = 0;
  RELAY_2 = 0;
  PICKUP_PHONE = 0;
  NCALL_DETECT = 1;
  NSET = 1;

  // set P3.6, P3.7 as output (relays)
  P3M0 = (1U<<6)|(1U<<7);
  // set P5.4, P5.5 as output (phone pickup, audio out)
  P5M0 = (1U<<4)|(1U<<5);
  // set P3.2 as input (DV)
  P3M1 = (1U<<2);

  // setup timer 2
  T2L = T1kHz & 0xff;
  T2H = T1kHz >> 8;
  AUXR |= 0x14; // start timer 2, SYSclk/1
  IE2 |= 0x04; // enable timer 2 interrupt

  // Setup INT0 Interrupt
  IT0 = 0; // falling and rising
  EX0 = 1; // ennable INT0 Interrupt

  // Setup INT1 Interrupt
  IT1 = 0; // falling and rising
  EX1 = 1; // ennable INT1 Interrupt

  // Enable Interrupts
  EA = 1;
}

int main(){
  init();

  restore_relay_state();
  restore_pin(pin, PIN_LENGTH);

  uint8_t idx = 0;
  char buffer[PIN_LENGTH];

  while(1){
    switch (state) {
    case INIT:
      // hang up
      PICKUP_PHONE = 0;
      idx = 0;
      delay_ms(1000); // wait (just in case C16 is charged)
      state = WAITING;
      break;
    case WAITING:
      if(ringing_detected){
        timeout_reset();
        state = CALL_DETECTED;
      }else if(!NSET){
        state = CONFIGURATION_START;
      }
      break;
    case CALL_DETECTED:
      if(timeout(5000)){
        state = INIT;
      }else if(ringing_detected){
        idx++;
        ringing_detected = false;
        timeout_reset();
      }else if(!NSET){
        state = CONFIGURATION_START;
      }else if(idx > 4){
        state = PICKUP;
      }
      break;
    case PICKUP:
      PICKUP_PHONE = 1;
      // greet with long beep
      delay_ms(500);
      beep(1, 500);
      state = AUTHENTICATION_START;
      break;
    case AUTHENTICATION_START:
      idx = 0;
      timeout_reset();
      state = AUTHENTICATION;
      break;
    case AUTHENTICATION:
      if(timeout(10000)){
        state = INIT;
      } else if(idx < PIN_LENGTH){
        // get next digit
        enum digit digit = get_digit();
        if((digit <= DIGIT_0) && (digit >= DIGIT_1)){
          // put next numeric digit into buffer
          buffer[idx] = (char) digit;
          idx++;
        }else if(digit == DIGIT_STAR){
          // reset on star input
          state = INIT;
        }
      } else if(cmp_const_time(buffer, pin, sizeof(pin)) == 0) {
        // if the pin is valid, play confirmationation tone
        beep(1, 500);
        state = CONTROL;
      } else {
        // if the pin is invalid, go back
        state = INIT;
      }
      break;
    case CONTROL:
      if(timeout(10000) || do_control()){
        state = INIT;
      }
      break;
    case CONFIGURATION_START:
      while(!NSET){} // ensure button was released
      idx = 0;
      PICKUP_PHONE = 1;
      delay_ms(500);
      beep(2, 200);
      timeout_reset();
      state = CONFIGURATION;
    case CONFIGURATION:
      if(!NSET || timeout(10000)){
        // exit config on button press, or timeout
        state = INIT;
      }else if(idx < PIN_LENGTH){
        // get next digit
        enum digit digit = get_digit();
        if((digit <= DIGIT_0) && (digit >= DIGIT_1)){
          // set next digit in pin
          buffer[idx] = (char) digit;
          idx++;
        }
      }else {
        // set and store new pin
        for(uint8_t i = 0; i<PIN_LENGTH; i++){
          pin[i] = buffer[i];
        }
        store_pin(pin, PIN_LENGTH);
        beep(2, 200);
        state = INIT;
      }
      break;
    default:
      // impossible state
      break;
    }
  }

}
