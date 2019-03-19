#ifndef IAP_H
#define IAP_H
#include <stdint.h>

char iap_read_byte(uint16_t addr);

void iap_write_byte(uint16_t addr, char data);

void iap_erease_sector(uint16_t addr);


#endif // IAP_H
