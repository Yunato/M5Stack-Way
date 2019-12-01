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

float Gyro::getValue(void) {
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

void Gyro::setupOffset(void) {
  this->mOffset = this->DEFAULT_OFFSET;
  for (int cnt = 0; cnt < 255; ++cnt) {
    this->mOffset += getAngle();
  }
  this->mOffset /= 255.0f;
  M5.Speaker.tone(250);
  delay(100);
  M5.Speaker.end();
  delay(2900);
}

float Gyro::getOffset(void) {
  return this->mOffset;
}
