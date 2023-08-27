#include "mbed.h"

static const PinName gpio_pin_out = D13;
static const PinName gpio_pin_in  = D11;

static mbed::DigitalIn button(gpio_pin_in);
static mbed::DigitalOut led(gpio_pin_out);

void setup() {
  button.mode(PullUp);
}

void loop() {
  led = !button;
}
