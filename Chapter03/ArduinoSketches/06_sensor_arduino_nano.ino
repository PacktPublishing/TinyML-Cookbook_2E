// Set to 1 if you are using the Arduino Nano 33 BLE Sense Rev2
#define ARDUINO_ARDUINO_NANO33BLE_REV2 0

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

void loop() {
}
