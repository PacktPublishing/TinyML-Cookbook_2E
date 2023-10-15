%%writefile ethosu_prj/src/demo_bare_metal.c
#include <stdio.h>
#include <tvm_runtime.h>
#include <tvmgen_default.h>

#include "ethosu_mod.h"
#include "uart.h"

#include "input.h"

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

int abs(int v) { return v * ((v > 0) - (v < 0)); }

int8_t out_q8[10] __attribute__((section("ethosu_scratch"), aligned(16)));
float out_f32[10] __attribute__((section("ethosu_scratch"), aligned(16)));

int main(int argc, char** argv) {
  uart_init();

  printf("Starting Demo\n");
  EthosuInit();

  printf("Running inference\n");
  struct tvmgen_default_outputs outputs = {
    .StatefulPartitionedCall_0 = out_q8,
  };

  struct tvmgen_default_inputs inputs = {
    .serving_default_input_1_0 = g_test,
  };
  struct ethosu_driver* driver = ethosu_reserve_driver();
  struct tvmgen_default_devices devices = {
    .ethos_u = driver,
  };
  tvmgen_default_run(&inputs, &outputs, &devices);
  ethosu_release_driver(driver);

  dequantize(out_q8, out_f32, 10);

  int32_t max_idx = argmax(out_f32, 10);

  if(max_idx == g_test_ilabel) {
    printf("The image has been correctly classified\n");
  }
  else {
    printf("Classification FAILED\n");
  }

  // The FVP will shut down when it receives "EXITTHESIM" on the UART
  printf("EXITTHESIM\n");
  while (1 == 1)
    ;
  return 0;
}