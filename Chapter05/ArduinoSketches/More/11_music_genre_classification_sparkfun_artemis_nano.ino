#include "arm_math.h"

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

static void print_raw_audio() {
  Serial.println(SAMPLE_RATE);
  Serial.println(AUDIO_LENGTH_SAMPLES);
  for(int i = 0; i < AUDIO_LENGTH_SAMPLES; ++i) {
    Serial.println((int32_t)buffer.data[i]);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize TensorFlow
  tflu_initialization();

  // [ADD HERE] - Initialize PDM microphone
}

void loop() {

  // [ADD HERE] - Recording audio

  // [ADD HERE] - MFCCs computation

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