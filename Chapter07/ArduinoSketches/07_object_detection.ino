#include <object_detection_inferencing.h>

#define FRAME_SIZE (76 * 76)
uint8_t frame[FRAME_SIZE];

int get_data_from_camera(size_t offset, size_t length, float *out_ptr) {
  for(size_t i = 0; i < length; ++i) {
    uint8_t gray = frame[i + offset];
    uint8_t r = gray;
    uint8_t g = gray;
    uint8_t b = gray;

    // Pack the RGB into a floating-point variable
    float pixel_f = (r << 16) + (g << 8) + b;
    out_ptr[i] = pixel_f;
  }

  return 0;
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);
}

void loop()
{
  Serial.println("<cam-read>");

  Serial.readBytes(frame, FRAME_SIZE);

  ei::signal_t signal;
  signal.total_length = FRAME_SIZE;
  signal.get_data = &get_data_from_camera;

  // Run the classifier
  ei_impulse_result_t result = { 0 };

  EI_IMPULSE_ERROR err = run_classifier(&signal, &result, false);

  if (err != EI_IMPULSE_OK) {
    ei_printf("ERR: Failed to run classifier (%d)\n", err);
    return;
  }

  uint32_t xy[EI_CLASSIFIER_OBJECT_DETECTION_COUNT][2];

  uint32_t num_objs = 0;
  const uint32_t max_ix = result.bounding_boxes_count;
  for (size_t ix = 0; ix < max_ix; ix++) {
    auto bb = result.bounding_boxes[ix];
    if (bb.value == 0) {
      continue;
    }

    xy[num_objs][0] = bb.x + bb.width / 2;
    xy[num_objs][1] = bb.y + bb.height / 2;
    num_objs++;
  }

  Serial.println(num_objs);
  for(uint32_t i = 0; i < num_objs; ++i) {
    Serial.print(xy[i][0]);
    Serial.print(",");
    Serial.println(xy[i][1]);
  }
}
