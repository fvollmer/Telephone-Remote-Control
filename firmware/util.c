#include "util.h"
#include <stdbool.h>

char cmp_const_time(void *a, void *b, uint8_t size){
  char *ca = (char*) a;
  char *cb = (char*) b;
  bool result = 0;
  for(uint8_t i=0; i<size; i++){
    result |= ca[i] ^ cb[i];
  }
  return result;
}
