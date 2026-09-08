#pragma once

#include <Arduino.h>

uint8_t writeRegister(uint8_t MPU_ADDR, uint8_t reg, uint8_t value) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(reg);
    Wire.write(value);
    return Wire.endTransmission();
}

Vec3 readGyro(uint8_t MPU_ADDR){
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x43);

    Wire.endTransmission(false);

    uint8_t count = Wire.requestFrom(MPU_ADDR, 6);

    if(count != 6){
        return {0.0, 0.0, 0.0};
    }

    int16_t gx = (Wire.read() << 8) | Wire.read();
    int16_t gy = (Wire.read() << 8) | Wire.read();
    int16_t gz = (Wire.read() << 8) | Wire.read();

    return {float(gx) / 131, float(gy) / 131, float(gz) / 131};
}

Vec3 readAccel(uint8_t MPU_ADDR){
    Wire.beginTransmission(MPU_ADDR);

    Wire.write(0x3B);

    Wire.endTransmission(false);

    uint8_t count = Wire.requestFrom(MPU_ADDR, 6);

    if (count != 6){
        return {0.0, 0.0, 0.0};
    }

    int16_t ax = (Wire.read() << 8) | Wire.read();
    int16_t ay = (Wire.read() << 8) | Wire.read();
    int16_t az = (Wire.read() << 8) | Wire.read();

    return {float(ax) / 16384, float(ay) / 16384, float(az) / 16384};
}

// Vec3 calibrateGyro(){
//     int32_t sumX = 0;
//     int32_t sumY = 0;
//     int32_t sumZ = 0;
//     for (uint16_t times = 0; times < 1000; times++){
//     }
// }
