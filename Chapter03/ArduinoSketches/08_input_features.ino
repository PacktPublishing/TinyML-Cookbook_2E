// Set to 1 if you are using the Arduino Nano 33 BLE Sense Rev2
#define ARDUINO_ARDUINO_NANO33BLE_REV2 0

constexpr int num_hours = 3;
int8_t t_vals [num_hours] = {0};
int8_t h_vals [num_hours] = {0};
int cur_idx = 0;

float tflu_i_scale = 1.0f;
int32_t tflu_i_zero_point = 0;

#if defined(ARDUINO_ARDUINO_NANO33BLE)

#if ARDUINO_ARDUINO_NANO33BLE_REV2 == 0
#include <Arduino_HTS221.h>
#define SENSOR HTS
#else
#include <Arduino_HS300x.h>
#define SENSOR HS300x
#endif

void setup() {
  Serial.begin(9600);

  while (!Serial);

  if (!SENSOR.begin()) {
    Serial.println("Failed sensor initialization!");
    while (1);
  }

  Serial.print("Test Temperature = ");
  Serial.print(SENSOR.readTemperature(), 2);
  Serial.println(" °C");
  Serial.print("Test Humidity = ");
  Serial.print(SENSOR.readHumidity(), 2);
  Serial.println(" %");
}
#endif

#if defined(ARDUINO_RASPBERRY_PI_PICO)
#include <DHT.h>

// Arduino pin number
const int gpio_pin_dht_pin = 10;
DHT dht(gpio_pin_dht_pin, DHT22);

#define SENSOR dht

void setup() {
  Serial.begin(9600);
  while(!Serial);
  SENSOR.begin();
  delay(2000);

  Serial.print("Test Temperature = ");
  Serial.print(SENSOR.readTemperature(), 2);
  Serial.println(" °C");
  Serial.print("Test Humidity = ");
  Serial.print(SENSOR.readHumidity(), 2);
  Serial.println(" %");
}
#endif

constexpr int num_reads = 3;
void loop() {
  float t = 0.0f;
  float h = 0.0f;
  for(int i = 0; i < num_reads; ++i) {
    t += SENSOR.readTemperature();
    h += SENSOR.readHumidity();
    delay(3000);
  }
  t /= (float)num_reads;
  h /= (float)num_reads;

  // Use the mean and standard deviation
  // extracted from your dataset
  constexpr float t_mean = 2.08993f;
  constexpr float h_mean = 87.22773f;
  constexpr float t_std  = 6.82158f;
  constexpr float h_std  = 14.21543f;
  t = (t - t_mean) / t_std;
  h = (h - h_mean) / h_std;

  t = (t / tflu_i_scale);
  t += (float)tflu_i_zero_point;
  h = (h / tflu_i_scale);
  h += (float)tflu_i_zero_point;

  t_vals[cur_idx] = t;
  h_vals[cur_idx] = h;

  cur_idx = (cur_idx + 1) % num_hours;

  delay(2000);
}
