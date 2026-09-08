#include <Arduino.h>
#include <Wire.h>
#include <cmath>

#include "vec3.hpp"
#include "mpu6050.hpp"

const int SDA_PIN = 4;
const int SCL_PIN = 5;

const uint8_t MPU_ADDR = 0x68;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Wire.begin(SDA_PIN, SCL_PIN);

    // Wake up MPU6050
    uint8_t error = writeRegister(MPU_ADDR, 0x6B, 0x00);

    Serial.print("Wake error: ");
    Serial.println(error);

    if (error == 0)
    {
        Serial.println("MPU6050 ready.");
    }

    // // Calibrate gyro
    // Serial.println("Gyro calibration begins.");
}

void loop()
{
    Vec3 a = readAccel(MPU_ADDR);

    float axFloat = a.x;
    float ayFloat = a.y;
    float azFloat = a.z;

    Vec3 g = readGyro(MPU_ADDR);

    float aIntegreted = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
    Serial.print("Integreted a: ");
    Serial.println(aIntegreted);

    Serial.print("A: ");
    Serial.print(a.x);
    Serial.print(" ");
    Serial.print(a.y);
    Serial.print(" ");
    Serial.print(a.z);

    Serial.print("    G: ");
    Serial.print(g.x);
    Serial.print(" ");
    Serial.print(g.y);
    Serial.print(" ");
    Serial.println(g.z);

    float xTiltAngle = atan2(ayFloat, azFloat) * 180 / PI;
    Serial.print("x-axis tilt angle: ");
    Serial.print(xTiltAngle);
    Serial.print(" ");
    float yTiltDeg = atan2(-axFloat, sqrt(ayFloat * ayFloat + azFloat * azFloat)) * 180.0 / PI;
    Serial.print("y-axis tilt angle: ");
    Serial.println(yTiltDeg);

    delay(200);
}