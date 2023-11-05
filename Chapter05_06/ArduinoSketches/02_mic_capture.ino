#include "mbed.h"
#include "hardware/adc.h"

#define ON          1
#define OFF         0
#define PRESSED     0
#define LED_BUILTIN p25
#define BUTTON      p10
#define BIAS_MIC    1552 // (1.25V * 4095) / 3.3
#define SAMPLE_RATE 22050
#define AUDIO_LENGTH_SEC  4
#define AUDIO_LENGTH_SAMPLES (SAMPLE_RATE * AUDIO_LENGTH_SEC)

mbed::Ticker     timer;
mbed::DigitalOut led_builtin(LED_BUILTIN);
mbed::DigitalIn  button(BUTTON);

struct Buffer
{
  int32_t cur_idx{0};
  bool    is_ready{false};
  int16_t data[AUDIO_LENGTH_SAMPLES];
};

volatile Buffer buffer;

void adc_setup() {
  adc_init();
  adc_gpio_init(26);
  adc_select_input(0);
}

void print_raw_audio() {
  Serial.println(SAMPLE_RATE);
  Serial.println(AUDIO_LENGTH_SAMPLES);
  for(int i = 0; i < AUDIO_LENGTH_SAMPLES; ++i) {
    Serial.println((int32_t)buffer.data[i]);
  }
}

void timer_ISR() {
  if(buffer.cur_idx < AUDIO_LENGTH_SAMPLES) {
    int16_t v = (int16_t)((adc_read() - BIAS_MIC));
    // Get current buffer index
    int32_t ix_buffer = buffer.cur_idx;
    // Store the sample in the audio buffer
    buffer.data[ix_buffer] = (int16_t)v;
    // Increment buffer index
    buffer.cur_idx++;
  }
  else {
    buffer.is_ready = true;
  }
}

/**
 * @brief      Arduino setup function
 */
void setup()
{
  Serial.begin(115200);

  while(!Serial);

  button.mode(PullUp);

  adc_setup();
}

/**
 * @brief      Arduino main function
 */
void loop()
{
  if(button == PRESSED)
  {
    delay(800);

    // Reset audio buffer
    buffer.cur_idx  = 0;
    buffer.is_ready = false;
    led_builtin = ON;

    constexpr uint32_t sr_us = 1000000 / SAMPLE_RATE;
    timer.attach_us(&timer_ISR, sr_us);

    while(!buffer.is_ready);

    timer.detach();

    led_builtin = OFF;

    print_raw_audio();
  }
}
