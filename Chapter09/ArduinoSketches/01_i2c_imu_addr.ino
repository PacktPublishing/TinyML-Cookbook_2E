#include "mbed.h"

static constexpr PinName I2C_SDA_PIN = p6;
static constexpr PinName I2C_SCL_PIN = p7;

static constexpr int32_t MPU6050_ADDR_7BIT = 0x68;
static constexpr int32_t MPU6050_ADDR_8BIT = 0xD1; // (0x68 << 1)
static constexpr int32_t MPU6050_WHO_AM_I  = 0x75;

mbed::I2C i2c(I2C_SDA_PIN, I2C_SCL_PIN);

void read_reg(int32_t addr_i2c, int32_t addr_reg, char *buf, int32_t length) {
  char data = addr_reg;
  i2c.write(addr_i2c, &data, 1);
  i2c.read(addr_i2c, buf, length);
  return;
}

void setup() {
  i2c.frequency(400000);

  Serial.begin(115200);
  while (!Serial);

  char id;
  read_reg(MPU6050_ADDR_8BIT, MPU6050_WHO_AM_I, &id, 1);

  if(id == MPU6050_ADDR_7BIT) {
    Serial.println("MPU6050 found");
  } else {
    Serial.println("MPU6050 not found");
    while(1);
  }
}

void loop() {
}
