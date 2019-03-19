#include "iap.h"
#include <stc12.h>


#if (FOSC > 24000000)
  #define IAP_ENABLE 0x80
#elif (FOSC > 20000000)
  #define IAP_ENABLE 0x81
#elif (FOSC > 12000000)
  #define IAP_ENABLE 0x82
#elif (FOSC > 6000000)
  #define IAP_ENABLE 0x83
#elif (FOSC > 3000000)
  #define IAP_ENABLE 0x84
#elif (FOSC > 2000000)
  #define IAP_ENABLE 0x85
#elif (FOSC > 1000000)
  #define IAP_ENABLE 0x86
#else
  #define IAP_ENABLE 0x87
#endif


#define IAP_CMD_IDLE 0
#define IAP_CMD_READ 1
#define IAP_CMD_PROGRAM 2
#define IAP_CMD_ERASE 3

void iap_idle(void);

void iap_idle(void){
  IAP_CONTR = 0;
  IAP_CMD = 0;
  IAP_TRIG = 0;
  IAP_ADDRH = 0x80;
  IAP_ADDRL = 0;
}

char iap_read_byte(uint16_t addr){
  IAP_CONTR = IAP_ENABLE;
  IAP_CMD = IAP_CMD_READ;
  IAP_ADDRL = addr;
  IAP_ADDRH = addr >> 8;
  IAP_TRIG = 0x5a;
  IAP_TRIG = 0xa5;
  NOP();

  uint8_t data = IAP_DATA;
  iap_idle();

  return data;
}

void iap_write_byte(uint16_t addr, char data){
  IAP_CONTR = IAP_ENABLE;
  IAP_CMD = IAP_CMD_PROGRAM;
  IAP_ADDRL = addr;
  IAP_ADDRH = addr >> 8;
  IAP_DATA = data;
  IAP_TRIG = 0x5a;
  IAP_TRIG = 0xa5;
  NOP();

  iap_idle();
}

void iap_erease_sector(uint16_t addr){
  IAP_CONTR = IAP_ENABLE;
  IAP_CMD = IAP_CMD_ERASE;
  IAP_ADDRL = addr;
  IAP_ADDRH = addr >> 8;
  IAP_TRIG = 0x5a;
  IAP_TRIG = 0xa5;
  NOP();

  iap_idle();
}
