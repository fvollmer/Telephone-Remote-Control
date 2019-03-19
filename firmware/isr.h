#ifndef ISR_H
#define ISR_H
void timer2_isr (void) __interrupt (12) __using (1);

void int0_isr (void) __interrupt (0) __using (2);

void int1_isr (void) __interrupt (2) __using (3);
#endif // ISR_H
