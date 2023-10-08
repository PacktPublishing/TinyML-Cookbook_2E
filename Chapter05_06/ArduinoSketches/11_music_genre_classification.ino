#include "arm_math.h"
#include "mbed.h"
#include "hardware/adc.h"

// TensorFlow Lite model
#include "model.h"

// MFCCs
#include "mfccs_consts.h"
#include "dct_wei_mtx_q15_T.h"
#include "hann_lut_q15.h"
#include "log_lut_q13_3.h"
#include "mel_wei_mtx_q15_T.h"

// TensorFlow Lite for Microcontrollers
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_log.h>
#include <tensorflow/lite/micro/system_setup.h>
#include <tensorflow/lite/schema/schema_generated.h>

#define BIAS_MIC    1552 // (1.25V * 4095) / 3.3
#define SAMPLE_RATE 22050
#define AUDIO_LENGTH_SEC  1
#define AUDIO_LENGTH_SAMPLES (SAMPLE_RATE * AUDIO_LENGTH_SEC)

static const char *label[] = {"disco", "jazz", "metal"};

// TensorFlow Lite for Microcontroller global variables
static const tflite::Model* tflu_model            = nullptr;
static tflite::MicroInterpreter* tflu_interpreter = nullptr;
static TfLiteTensor* tflu_i_tensor                = nullptr;
static TfLiteTensor* tflu_o_tensor                = nullptr;
static constexpr int t_sz                         = 8192;
static uint8_t tensor_arena[t_sz] __attribute__((aligned(16)));

struct Buffer
{
  int32_t cur_idx{0};
  bool    is_ready{false};
  int16_t data[AUDIO_LENGTH_SAMPLES];
};

static mbed::Ticker    timer;
static volatile Buffer buffer;

void tflu_initialization() {

  // Load the TFLITE model
  tflu_model = tflite::GetModel(model_tflite);
  if (tflu_model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.print(tflu_model->version());
    Serial.println("");
    Serial.print(TFLITE_SCHEMA_VERSION);
    Serial.println("");
    while(1);
  }

  tflite::AllOpsResolver tflu_ops_resolver;

  // Initialize the TFLu interpreter
  static tflite::MicroInterpreter static_interpreter(
        tflu_model,
        tflu_ops_resolver,
        tensor_arena,
        t_sz);

  tflu_interpreter = &static_interpreter;

  // Allocate TFLu internal memory
  tflu_interpreter->AllocateTensors();

  // Get the pointers for the input and output tensors
  tflu_i_tensor = tflu_interpreter->input(0);
  tflu_o_tensor = tflu_interpreter->output(0);

  Serial.println("TFLu initialization - completed");
}

class MFCC_Q15 {
public:
 MFCC_Q15() {
    // RFFT instance
    arm_rfft_init_q15(&_rfft_inst, FFT_LENGTH, 0, 1);

    // Mel-weight matrix instance
    _mel_wei_mtx_inst.numRows = mel_wei_mtx_q15_T_dim1;
    _mel_wei_mtx_inst.numCols = mel_wei_mtx_q15_T_dim0;
    _mel_wei_mtx_inst.pData = (q15_t *)&mel_wei_mtx_q15_T_data[0];

    // DCT-weight matrix instance
    _dct_wei_mtx_inst.numRows = dct_wei_mtx_q15_T_dim1;
    _dct_wei_mtx_inst.numCols = dct_wei_mtx_q15_T_dim0;
    _dct_wei_mtx_inst.pData = (q15_t *)&dct_wei_mtx_q15_T_data[0];
  }

  void run(const q15_t* src, float* dst) {
    for(int i = 0; i < NUM_FRAMES; ++i ) {
      // Apply the Hann window
      arm_mult_q15((q15_t*)&src[i * FRAME_STEP], (q15_t*)hann_lut_q15_data, _bufA, FRAME_LENGTH);

      // Calculate the RFFT
      arm_rfft_q15(&_rfft_inst, _bufA, _bufB);

      // Calculate the magnitude
      _bufA[0]                 = _bufB[0];
      _bufA[NUM_FFT_FREQS - 1] = _bufB[1];
      arm_cmplx_mag_q15(&_bufB[2], &_bufA[1], NUM_FFT_FREQS - 2);

      // Mel-scale conversion
      arm_mat_vec_mult_q15(&_mel_wei_mtx_inst, _bufA, _bufB);

      for(int idx = 0; idx < NUM_MEL_FREQS; ++idx) {
        const int16_t val = (int16_t)_bufB[idx];
        _bufA[idx] = log_lut_q13_3_data[val];
      }

      // Calculate the MFCCs through the DCT
      arm_mat_vec_mult_q15(&_dct_wei_mtx_inst, _bufA, _bufB);

      for(int k = 0; k < NUM_MFCCS; ++k) {
        dst[k + i * NUM_MFCCS] = (float)_bufB[k] / (float)(8);
      }
    }
  }
private:
  arm_rfft_instance_q15   _rfft_inst;
  arm_matrix_instance_q15 _mel_wei_mtx_inst;
  arm_matrix_instance_q15 _dct_wei_mtx_inst;
  q15_t                   _bufA[FRAME_LENGTH];
  q15_t                   _bufB[FRAME_LENGTH * 2];
};

MFCC_Q15 mfccs;

static void print_raw_audio() {
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

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize TensorFlow
  tflu_initialization();

  // Initialize ADC
  adc_init();
  adc_gpio_init(26);
  adc_select_input(0);
}

void loop() {
  // Reset audio buffer
  buffer.cur_idx  = 0;
  buffer.is_ready = false;

  constexpr uint32_t sr_us = 1000000 / SAMPLE_RATE;
  timer.attach_us(&timer_ISR, sr_us);

  while(!buffer.is_ready);

  timer.detach();

  // MFCCs computation
  mfccs.run((const q15_t*)&buffer.data[0],
            (float *)&tflu_i_tensor->data.f[0]);

  // Run inference
  TfLiteStatus invoke_status = tflu_interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    Serial.println("Error invoking the TFLu interpreter");
    return;
  }

  size_t ix_max = 0;
  float  pb_max = 0;
  for (size_t ix = 0; ix < 3; ix++) {
    if(tflu_o_tensor->data.f[ix] > pb_max) {
      ix_max = ix;
      pb_max = tflu_o_tensor->data.f[ix];
    }
  }

  Serial.println(label[ix_max]);
}