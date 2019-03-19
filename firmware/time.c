#include "time.h"



static volatile uint16_t time = 0; // current time in ms, increased by timer
static uint16_t last_input_time = 0;

void time_increase_1ms(void){
  time++;
}

void timeout_reset(void){
  last_input_time = time;
}

bool timeout(uint16_t ms){
  uint16_t stop = last_input_time + ms;
  if(stop > last_input_time){
    return (time > stop);
  } else {
    return (time > stop) && (time < last_input_time);
  }
}

void delay_ms(uint16_t ms)
{
  uint16_t start = time;
  uint16_t stop = start + ms;
  if(stop > start){
    while(stop > time){}
  } else if (stop < start){
    while(stop < time){}
  }
}
