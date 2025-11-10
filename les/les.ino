// Locate the initial position of legs
// Converted for ESP32 + PCA9685 (12-channel servo control)
// RegisHsu (original), Modified 2025

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // default I2C address

// Servo config
#define SERVO_MIN  150   // Min pulse length (0°)
#define SERVO_MAX  600   // Max pulse length (180°)

// 4 legs × 3 servos = 12 total servos on PCA9685 channels 0–11
const int servo_channel[4][3] = { 
  {0, 1, 2},     // Leg 1: Coxa, Femur, Tibia
  {3, 4, 5},     // Leg 2
  {6, 7, 8},     // Leg 3
  {9, 10, 11}    // Leg 4
};

// Convert angle (0–180°) to PCA9685 PWM pulse
int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

void setup() {
  Wire.begin();                  // ESP32 I2C (default SDA=21, SCL=22)
  pwm.begin();
  pwm.setPWMFreq(50);            // Standard servo frequency 50 Hz
  delay(10);
}

void loop() {
  // Set all servos to 90°
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      int channel = servo_channel[i][j];
      int pulse = angleToPulse(90);

      pwm.setPWM(channel, 0, pulse);
      delay(20);
    }
  }

  while (true) {}  // Hold positions forever
}
 
