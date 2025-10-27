// FILE: ChipNorm_SHT21.h
// VERSION: 1.0.0
//
// ChipNorm invests time and resources providing this open code,
// please support ChipNorm by purchasing products from ChipNorm.
//
// Written by Enrique Fernandez for ChipNorm by FMH.
//
// Copyright   Copyright (c) 2025 Enrique Fernandez - ChipNorm by FMH
// See the LICENSE file for details.

#include "ChipNorm_SHT21.h"

bool ChipNorm_SHT21::writeCommand(uint8_t command) {
  Wire.beginTransmission(SHT21_I2CADDR);
  Wire.write(command);
  if (Wire.endTransmission(true) != 0) {
    return false;
  }
  return true;
}

bool ChipNorm_SHT21::readData(uint8_t command, uint8_t *buffer, uint8_t len, uint16_t delay_ms) {
  if (!writeCommand(command)) {
    return false;
  }

  delay(delay_ms);

  uint8_t read_count = Wire.requestFrom((uint8_t)SHT21_I2CADDR, len);
  if (read_count != len) {
    return false;
  }

  for (uint8_t i = 0; i < len; i++) {
    buffer[i] = Wire.read();
  }
  
  return true;
}


ChipNorm_SHT21::ChipNorm_SHT21(int8_t scl_pin, int8_t sda_pin) {
  _last_humidity = 0.0f;
  _last_temp = 0.0f;
  _scl = scl_pin;
  _sda = sda_pin;
}

bool ChipNorm_SHT21::begin() {
  Wire.begin(_sda, _scl); 
  
  Wire.setClock(400000); 

  reset();

  if (!writeCommand(SHT21_READREG)) {
    return false;
  }
  
  uint8_t read_count = Wire.requestFrom((uint8_t)SHT21_I2CADDR, (uint8_t)1);
  if (read_count != 1) {
      return false;
  }
  
  uint8_t reg_val = Wire.read();
  
  return (reg_val & 0xFF) == 0x02;
}

void ChipNorm_SHT21::reset(void) {
  writeCommand(SHT21_RESET);
  delay(15);
}

float ChipNorm_SHT21::readTemperature(void) {
  uint8_t buf[3];
  
  if (!readData(SHT21_READTEMP, buf, 3, 50)) {
    return NAN;
  }

  uint16_t t = buf[0];
  t <<= 8;
  t |= buf[1] & 0b11111100;

  float temp = t;
  temp *= 175.72f;
  temp /= 65536.0f;
  temp -= 46.85f;

  _last_temp = temp;
  return temp;
}

float ChipNorm_SHT21::readHumidity(void) {
  uint8_t buf[3];
  
  if (!readData(SHT21_READHUM, buf, 3, 50)) {
    return NAN;
  }

  uint16_t h = buf[0];
  h <<= 8;
  h |= buf[1] & 0b11111100;

  float hum = h;
  hum *= 125.0f;
  hum /= 65536.0f;
  hum -= 6.0f;

  _last_humidity = hum;
  return hum;
}