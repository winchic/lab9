#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ping.h"
#include "timer.h"

// declare variables to store echo pulse times
extern volatile unsigned int risingEdgeTime;
extern volatile unsigned int fallingEdgeTime;

int main(void) {
    // initialize the ping))) sensor and timer 5
    ping_init();          // initialize the ping))) sensor
    timer_init();         // initialize timer 5

    while (1) {
        ping_trigger();   // trigger the ping))) sensor
        ping_measureEcho(); // measure the echo pulse width

        // calculate pulse width, handling overflow
        unsigned int pulseWidth;
        if (fallingEdgeTime >= risingEdgeTime) {
            pulseWidth = fallingEdgeTime - risingEdgeTime;  // normal case
        } else {
            // overflow case: handle timer wrap-around
            pulseWidth = (MICROS_PER_TICK - risingEdgeTime) + fallingEdgeTime;
        }

        // calculate distance in centimeters
        double distance = (pulseWidth * 340.0) / (2 * 1000000);  // distance in meters
        distance *= 100;  // convert to centimeters

        // use the `distance` variable as needed (e.g., display, uart, etc.)

        // delay for 200 milliseconds before the next measurement
        timer_waitMillis(200);
    }
}
