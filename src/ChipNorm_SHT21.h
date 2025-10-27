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

#ifndef _CHIPNORM_SHT21_H
#define _CHIPNORM_SHT21_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h> 

#define SHT21_I2CADDR (0x40)
#define SHT21_READTEMP (0xE3)
#define SHT21_READHUM (0xE5)
#define SHT21_READREG (0xE7)
#define SHT21_RESET (0xFE)

class ChipNorm_SHT21 {
public:
  ChipNorm_SHT21(int8_t scl_pin, int8_t sda_pin);

  bool begin();
 
  float readTemperature(void);
  float readHumidity(void);
  void reset(void);

private:
  int8_t _scl, _sda; 
  float _last_humidity, _last_temp;
  bool readData(uint8_t command, uint8_t *buffer, uint8_t len, uint16_t delay_ms);
  bool writeCommand(uint8_t command);
  uint8_t crc8(const uint8_t *data, int len);
};

#endif