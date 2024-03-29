#include "gyro.hpp"

/**
 * @brief Constructor
 * @details Initialize each variable
 */
Gyro::Gyro(void):
mOffset(DEFAULT_OFFSET),
accX(0.0f), accY(0.0f), accZ(0.0f),
gyroX(0.0f), gyroY(0.0f), gyroZ(0.0f),
pitch(0.0f), roll(0.0f), yaw(0.0f){}

/**
 * @brief Destructor
 */
Gyro::~Gyro(void) { }

/**
 * @brief Get value from sensor
 * @details Get angular velocity, acceleration, angle from sensor
 */
void Gyro::read(void) {
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);
}

/**
 * @brief Return the latest angular velocity
 * @return angular velocity
 */
float Gyro::getAngularVelocity(void) {
  return this->gyroX;
}

/**
 * @brief Return the latest angle (roll)
 * @return angle (roll)
 */
float Gyro::getAngle(void) {
  return this->roll;
}

/**
 * @brief Calibration
 * @details Calibration is performed by letting it stand for 3 seconds
 */
void Gyro::reset(void) {
  float std_value;
  unsigned long start_time = millis();
  bool reset_flag = true;
  while(millis() - start_time < 3000 || reset_flag) {
    if (reset_flag) {
      M5.IMU.Init();
      read();
      std_value = getAngularVelocity();
      start_time = millis();
      reset_flag = false;
    }
    read();
    if ((int)std_value != (int)getAngularVelocity()) {
      reset_flag = true;
    }
  }
}

/**
 * @brief Setup Gyro sensor
 */
void Gyro::setup(void) {
  reset();
  this->mOffset = this->DEFAULT_OFFSET;
  for (int cnt = 0; cnt < 500; ++cnt) {
    read();
    this->mOffset += getAngularVelocity();
  }
  this->mOffset /= 500.0f;
  for (int i = 0; i < 1000; ++i) {
    kalmanFilter();
    filterdOffset = filterd;
  }
  // filterd = 0.0f;
  // kalmanFilter();
}

/**
 * @brief Return the offset for angular velocity
 * @return offset
 */
float Gyro::getOffset(void) {
  return this->mOffset;
}

void Gyro::kalmanFilter(void) {
  read();
  float angle = (atan2(accY, accZ) * 180 / M_PI);
  filterd = kalman->update(angle, gyroX / 20.0);
}

void Gyro::filter(void) {
  read();
  float angle = (atan2(accY, accZ) * 180 / M_PI);
  float omega = gyroX / 20.0;
  unsigned long now = millis();
  float dt = (now - pre_time) / 1000.0f;
  pre_time = now;
  float K = 0.8;
  float A = K / (K + dt);
  filterd = A * (filterd + omega * dt) + (1 - A) * angle;
}

float Gyro::getFilterd(void) {
  return filterd;
}

float Gyro::getFilterdOffset(void) {
  return filterdOffset;
}
