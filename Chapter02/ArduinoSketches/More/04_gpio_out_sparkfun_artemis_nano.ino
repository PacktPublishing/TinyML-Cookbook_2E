#include "mbed.h"

static const PinName gpio_pin_out = D13;

static mbed::DigitalOut led(gpio_pin_out);

void setup() {
}

void loop() {
  led = 1;
}