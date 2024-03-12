#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

float dt = 0;
float roll = 0, pitch = 0, gyroRoll = 0, gyroPitch = 0;
float gX = 0, gY = 0, gZ = 0;
float wheelSpeed_1 = 0;
float wheelSpeed_2 = 0;
static double filteredSpeed_1 = 0;
static double filteredSpeed_2 = 0;
int deadBand = 40;
unsigned long previousTime = 0;
unsigned long prevCurrentTime = 0;
bool vertical = false;

void setup(void) {
  Serial.begin(115200);
  setupMPU();
  setupEncoder();
  setupMotor();
  prevCurrentTime = micros();
}

void loop() {

  // Update sensors
  deltaTime_calc();
  imuCalc();
  encoderCalc();
  updateCurrent();
  verticalCheck();

  // LQR and motor Update
  lqrControl();
  motorControl_1();  
  motorControl_2();

  // Debug Print
//  printStuff();
}
