#include "storage.h"
#include "config.h"
#include "iap.h"

void store_pin(const char* const pin, uint8_t length){
  iap_erease_sector(PIN_ADDRESS);
  for(uint8_t i = 0; i<length; i++){
    iap_write_byte(PIN_ADDRESS + i, pin[i]);
  }
}

void restore_pin(char* const pin, uint8_t length){
  for(uint8_t i = 0; i<length; i++){
    pin[i] = iap_read_byte(PIN_ADDRESS + i);
  }
}

void store_relay_state(void){
  char data = RELAY_1 | (RELAY_2<<1);
  iap_erease_sector(RELAY_STATE_ADDRESS);
  iap_write_byte(RELAY_STATE_ADDRESS, data);
}

void restore_relay_state(void){
  char data = iap_read_byte(RELAY_STATE_ADDRESS);
  RELAY_1 = data & 0x1;
  RELAY_2 = data & 0x2;
}
