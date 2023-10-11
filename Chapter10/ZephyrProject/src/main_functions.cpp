/*
 * Copyright 2020 The TensorFlow Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "main_functions.h"

#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/system_setup.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include "input.h"
#include "model.h"

/* Globals, used for compatibility with Arduino-style sketches. */
namespace {
  tflite::ErrorReporter *error_reporter = nullptr;
  const tflite::Model *model = nullptr;
  tflite::MicroInterpreter *interpreter = nullptr;
  TfLiteTensor *input = nullptr;
  TfLiteTensor *output = nullptr;

  constexpr int kTensorArenaSize = 44000;
  uint8_t tensor_arena[kTensorArenaSize];

  float o_scale = 0.0f;
  int32_t o_zero_point = 0;
}  /* namespace */

/* The name of this function is important for Arduino compatibility. */
void setup(void)
{
  /* Set up logging. Google style is to avoid globals or statics because of
    * lifetime uncertainty, but since this has a trivial destructor it's okay.
    * NOLINTNEXTLINE(runtime-global-variables)
    */
  static tflite::MicroErrorReporter micro_error_reporter;

  error_reporter = &micro_error_reporter;

  /* Map the model into a usable data structure. This doesn't involve any
    * copying or parsing, it's a very lightweight operation.
    */
  model = tflite::GetModel(cifar10_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
            "Model provided is schema version %d not equal "
            "to supported version %d.",
            model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  /* This pulls in all the operation implementations we need.
    * NOLINTNEXTLINE(runtime-global-variables)
    */
  static tflite::MicroMutableOpResolver<6> resolver;
  resolver.AddConv2D();
  resolver.AddRelu();
  resolver.AddDepthwiseConv2D();
  resolver.AddMaxPool2D();
  resolver.AddReshape();
  resolver.AddFullyConnected();

  /* Build an interpreter to run the model with. */
  static tflite::MicroInterpreter static_interpreter(
    model, resolver, tensor_arena, kTensorArenaSize, error_reporter);

  interpreter = &static_interpreter;

  /* Allocate memory from the tensor_arena for the model's tensors. */
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  /* Obtain pointers to the model's input and output tensors. */
  input = interpreter->input(0);
  output = interpreter->output(0);

  const auto* o_quantization = reinterpret_cast<TfLiteAffineQuantization*>(output->quantization.params);
  o_scale = o_quantization->scale->data[0];
  o_zero_point = o_quantization->zero_point->data[0];
}

/* The name of this function is important for Arduino compatibility. */
void loop(void)
{
  for(int i = 0; i < g_test_len; ++i) {
    input->data.int8[i] = g_test[i];
  }

  interpreter->Invoke();

  int32_t ix_max = 0;
  float pb_max = 0;

  for(size_t ix = 0; ix < 10; ++ix) {
    int8_t out_val = output->data.int8[ix];
    float  pb      = ((float)out_val - o_zero_point);
           pb *= o_scale;
    if(pb > pb_max) {
      ix_max = ix;
      pb_max = pb;
    }
  }

  if(ix_max == g_test_ilabel) {
    TF_LITE_REPORT_ERROR(error_reporter, "TEST passed\n");
  }
  else {
    TF_LITE_REPORT_ERROR(error_reporter, "TEST failed\n");
  }
  while(1);
}
