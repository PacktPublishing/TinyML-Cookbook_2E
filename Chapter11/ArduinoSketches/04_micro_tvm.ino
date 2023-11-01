#include "src/model.h"
#include "src/input.h"

#include "mbed.h"

float out_scale = 0.10305877029895782;
int32_t out_zero_point = 20;

void dequantize(int8_t* src, float* dst, int32_t len) {
  for(int32_t i = 0; i < len; ++i) {
    dst[i] = out_scale  * (src[i] - out_zero_point);
  }
}

int32_t argmax(float* src, int32_t len) {
  int32_t max_idx = 0;
  float max_score = src[0];

  for(int32_t i = 1; i < len; ++i) {
    if(src[i] > max_score) {
      max_score = src[i];
      max_idx   = i;
    }
  }
  return max_idx;
}

mbed::DigitalOut led(LED1);

void setup() {
  TVMInitialize();

  led = 0;
}

void loop() {
  int8_t out_q8[10];
  float out_f32[10];
  TVMExecute(g_test, out_q8);

  dequantize(out_q8, out_f32, 10);

  int32_t max_idx = argmax(out_f32, 10);

  if(max_idx == g_test_ilabel) {
    led = 1;
  }
  while(1);
}