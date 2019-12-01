#include "gyro.hpp"

Gyro::Gyro(void): mOffset(DEFAULT_OFFSET), gyroX(0), gyroY(0), gyroZ(0) {}

Gyro::~Gyro(void) {}

float Gyro::getAngle(void) {
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  return this->gyroX;
}

void Gyro::setValue(int value) {
	this->gyroX = value;
}

float Gyro::getValue() {
	return this->gyroX;
}

void Gyro::reset(void) {
  float std_value;
  do{
    M5.IMU.Init();
    std_value = getAngle();
   	delay(500);
  }while((int)getAngle() != (int)std_value);
}
