#include "phone.h"
#include "time.h"

void timer2_isr (void) __interrupt (12) __using (1){
  time_increase_1ms();
  beep_interrupt_fun();
}


void int0_isr (void) __interrupt (0) __using (2){
  dv_edge_interrupt_fun();
}

void int1_isr (void) __interrupt (2) __using (3){
  ringing_edge_interrupt_fun();
}

