#include "model.h"

#include "mbed.h"
#include <Arduino_OV767X.h>

#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_log.h>
#include <tensorflow/lite/micro/system_setup.h>
#include <tensorflow/lite/schema/schema_generated.h>

static const char *label[] = {"book", "mug", "unknown"};
static int32_t bytes_per_frame;
static int32_t bytes_per_pixel;
static bool debug_application = false;

static uint8_t data[160 * 120 * 2]; // QQVGA: 160x120 X 2 bytes per pixel (YUV422)

// Resolutions of the cropped image
static int32_t height_i = 0; // Initialized in the setup() function
static int32_t width_i  = 0; // Initialized in the setup() function

// Resolution of TensorFlow Lite input model
static int32_t height_o = 48;
static int32_t width_o  = 48;

// Scaling factors required by the resize operator
static float scale_x = 0.0f;  // Initialized in the setup() function
static float scale_y = 0.0f;  // Initialized in the setup() function

// Strides of the cropped image
static int32_t stride_x = 0; // Initialized in the setup() function
static int32_t stride_y = 0; // Initialized in the setup() function

template <typename T>
inline T clamp_0_255(T x) {
  return std::max(std::min(x, static_cast<T>(255)), static_cast<T>(0));
}

inline void ycbcr422_rgb888(int32_t Y, int32_t Cb, int32_t Cr, uint8_t* out) {
  Cr = Cr - 128;
  Cb = Cb - 128;

  out[0] = clamp_0_255((int32_t)(Y + Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5)));
  out[1] = clamp_0_255((int32_t)(Y - ((Cb >> 2) + (Cb >> 4) + (Cb >> 5)) - ((Cr >> 1) + (Cr >> 3) + (Cr >> 4)) + (Cr >> 5)));
  out[2] = clamp_0_255((int32_t)(Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6)));
}

inline uint8_t bilinear(uint8_t v00, uint8_t v01, uint8_t v10, uint8_t v11, float xi_f, float yi_f) {
  const float xi = (int32_t)std::floor(xi_f);
  const float yi = (int32_t)std::floor(yi_f);
  const float wx1 = (xi_f - xi);
  const float wx0 = (1.0f - wx1);
  const float wy1 = (yi_f - yi);
  const float wy0 = (1.0f - wy1);

  float res = 0;
  res += (v00 * wx0 * wy0);
  res += (v01 * wx1 * wy0);
  res += (v10 * wx0 * wy1);
  res += (v11 * wx1 * wy1);

  return clamp_0_255(res);
}

inline float rescale(float x, float scale, float offset) {
  return (x * scale) - offset;
}

inline int8_t quantize(float x, float scale, float zero_point) {
  return (x / scale) + zero_point;
}

// TensorFlow Lite for Microcontroller global variables
static const tflite::Model* tflu_model            = nullptr;
static tflite::MicroInterpreter* tflu_interpreter = nullptr;
static TfLiteTensor* tflu_i_tensor                = nullptr;
static TfLiteTensor* tflu_o_tensor                = nullptr;

static constexpr int tensor_arena_size = 128000;
static uint8_t *tensor_arena = nullptr;

static float   tflu_scale     = 0.0f;
static int32_t tflu_zeropoint = 0;

void tflu_initialization() {
  Serial.println("TFLu initialization - start");

  tensor_arena = new uint8_t[tensor_arena_size];

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
        tensor_arena_size);
    tflu_interpreter = &static_interpreter;

  // Allocate TFLu internal memory
  tflu_interpreter->AllocateTensors();

  // Get the pointers for the input and output tensors
  tflu_i_tensor = tflu_interpreter->input(0);
  tflu_o_tensor = tflu_interpreter->output(0);

  const auto* i_quant = reinterpret_cast<TfLiteAffineQuantization*>(tflu_i_tensor->quantization.params);

  // Get the quantization parameters (per-tensor quantization)
  tflu_scale     = i_quant->scale->data[0];
  tflu_zeropoint = i_quant->zero_point->data[0];

  Serial.println("TFLu initialization - completed");
}

void setup() {
  Serial.begin(115600);
  while (!Serial);

  if (!Camera.begin(QQVGA, YUV422, 1)) {
    Serial.println("Failed to initialize camera!");
    while (1);
  }

  bytes_per_pixel = Camera.bytesPerPixel();
  bytes_per_frame = Camera.width() * Camera.height() * bytes_per_pixel;

  // Initialize TFLu
  tflu_initialization();

  // Initialize resolution
  // Resolutions of the cropped image
  height_i = Camera.height();
  width_i  = Camera.height();

  if(debug_application) {
    height_o = Camera.height();
    width_o  = Camera.height();
    Camera.testPattern();
  }

  // Strides of the cropped image
  stride_x = bytes_per_pixel;
  stride_y = Camera.width() * bytes_per_pixel;

  // Initialize the scaling factors required by the resize operator
  scale_x = (float)width_i / (float)width_o;
  scale_y = (float)height_i / (float)height_o;
}

void loop() {
  Camera.readFrame(data);
  uint8_t rgb888[3];
  if(debug_application) {
    Serial.println("<image>");
    Serial.println(width_o);
    Serial.println(height_o);
  }

  int32_t idx = 0;
  for (int32_t yo = 0; yo < height_o; yo++) {
    const float yi_f = (yo * scale_y);
    const int32_t yi = (int32_t)std::floor(yi_f);

    for(int32_t xo = 0; xo < width_o; xo++) {
      const float xi_f = (xo * scale_x);
      const int32_t xi = (int32_t)std::floor(xi_f);

      const int32_t x0 = xi;
      const int32_t y0 = yi;
      const int32_t x1 = std::min(xi + 1, width_i - 1);
      const int32_t y1 = std::min(yi + 1, height_i - 1);

      // Calculate the offset to access the Y component
      const int32_t off_Y00 = x0 * stride_x + y0 * stride_y;
      const int32_t off_Y01 = x1 * stride_x + y0 * stride_y;
      const int32_t off_Y10 = x0 * stride_x + y1 * stride_y;
      const int32_t off_Y11 = x1 * stride_x + y1 * stride_y;

      const int32_t Y00 = data[off_Y00];
      const int32_t Y01 = data[off_Y01];
      const int32_t Y10 = data[off_Y10];
      const int32_t Y11 = data[off_Y11];

      // Calculate the offset to access the Cr component
      const int32_t adj_cr00 = xi % 2 == 0? 1 : -1;
      const int32_t adj_cr01 = (xi + 1) % 2 == 0? 1 : -1;

      const int32_t Cr00 = data[off_Y00 + adj_cr00];
      const int32_t Cr01 = data[off_Y01 + adj_cr01];
      const int32_t Cr10 = data[off_Y10 + adj_cr00];
      const int32_t Cr11 = data[off_Y11 + adj_cr01];

      // Calculate the offset to access the Cb component
      const int32_t adj_cb00 = xi % 2 == 0? 3 : 1;
      const int32_t adj_cb01 = (xi + 1) % 2 == 0? 3 : 1;

      const int32_t Cb00 = data[off_Y00 + adj_cb00];
      const int32_t Cb01 = data[off_Y01 + adj_cb01];
      const int32_t Cb10 = data[off_Y10 + adj_cb00];
      const int32_t Cb11 = data[off_Y11 + adj_cb01];

      uint8_t rgb00[3];
      uint8_t rgb01[3];
      uint8_t rgb10[3];
      uint8_t rgb11[3];

      // Convert YCbCr422 to RGB888
      ycbcr422_rgb888(Y00, Cb00, Cr00, rgb00);
      ycbcr422_rgb888(Y01, Cb01, Cr01, rgb01);
      ycbcr422_rgb888(Y10, Cb10, Cr10, rgb10);
      ycbcr422_rgb888(Y11, Cb11, Cr11, rgb11);

      // Iterate over the RGB channels
      uint8_t c_i;
      float c_f;
      int8_t c_q;
      for(int32_t i = 0; i < 3; i++) {
        c_i = bilinear(rgb00[i], rgb01[i], rgb10[i], rgb11[i], xi_f, yi_f);
        c_f = rescale((float)c_i, 1.f/255.f, -1.f);
        c_q = quantize(c_f, tflu_scale, tflu_zeropoint);

        if(debug_application) {
          Serial.println(rgb00[i]);
        }
        else {
          tflu_i_tensor->data.int8[idx++] = c_q;
        }
      }
    }
  }
  if(debug_application) {
    Serial.println("</image>");
    while(1);
  }

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

