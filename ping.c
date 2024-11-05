#include "tm4c123gh6pm.h"
#include "ping.h"
#include "timer.h"

// variables to store rising and falling edge times
volatile unsigned int risingEdgeTime = 0;
volatile unsigned int fallingEdgeTime = 0;

// function to initialize pb3 as gpio output for triggering the ping))) sensor
void ping_init(void) {
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;  // enable clock for port b
    GPIO_PORTB_DIR_R |= 0x08;                 // set pb3 as output
    GPIO_PORTB_DEN_R |= 0x08;                 // enable digital function on pb3
}

// function to trigger the ping))) sensor
void ping_trigger(void) {
    GPIO_PORTB_DATA_R &= ~0x08;  // set pb3 low
    timer_waitMicros(2);         // wait 2 microseconds
    GPIO_PORTB_DATA_R |= 0x08;   // set pb3 high
    timer_waitMicros(5);         // wait 5 microseconds
    GPIO_PORTB_DATA_R &= ~0x08;  // set pb3 low
}

// function to measure the echo pulse width using timer 5
void ping_measureEcho(void) {
    // reconfigure pb3 as input
    GPIO_PORTB_DIR_R &= ~0x08;           // set pb3 as input
    GPIO_PORTB_AFSEL_R |= 0x08;          // enable alternate function on pb3
    GPIO_PORTB_PCTL_R &= ~0x0000F000;    // clear pctl for pb3
    GPIO_PORTB_PCTL_R |= 0x00007000;     // configure pb3 for t5ccp1 (timer 5 capture)
    GPIO_PORTB_DEN_R |= 0x08;            // enable digital functionality on pb3

    // use timer functions to capture rising and falling edges
    risingEdgeTime = timer_getMicros();  // capture time of rising edge
    // wait for falling edge and capture time
    fallingEdgeTime = timer_getMicros();
}
