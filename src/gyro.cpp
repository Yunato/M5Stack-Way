#include "gyro.hpp"

Gyro::Gyro(void): mOffset(DEFAULT_OFFSET) {}

Gyro::~Gyro(void) {}

float Gyro::getAngle(void) {
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  return this->gyroX;
}

// void Gyro::checkPort(void) {
// 	getAngle();
// }

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
     	delay(3000);
    }while((int)getAngle() != (int)std_value);
}
