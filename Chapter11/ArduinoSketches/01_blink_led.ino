#include "mbed.h"

mbed::DigitalOut led(LED1);

void setup() {
}

void loop() {
  led = 1;
  delay(1000);
  led = 0;
  delay(1000);
}