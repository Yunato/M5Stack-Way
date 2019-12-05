#ifndef GYRO_H_
#define GYRO_H_
#define M5STACK_MPU6886

#include <M5Stack.h>
#include "filter.hpp"

class Gyro {

private:
  static constexpr float DEFAULT_OFFSET = 0.0f;
  float mOffset;
  float accX;
  float accY;
  float accZ;
  float gyroX;
  float gyroY;
  float gyroZ;
  float pitch;
  float roll;
  float yaw;

  Filter* kalman = new Filter(0.001, 0.003, 0.03);
  float filterd;
  float filterdOffset;
  unsigned long pre_time = 0;

public:
  Gyro(void);
  ~Gyro(void);

  void read(void);
  float getAngularVelocity(void);
  float getAngle(void);
  void reset(void);
  void setup(void);
  float getOffset(void);

  void kalmanFilter(void);
  void filter(void);
  float getFilterd(void);
  float getFilterdOffset(void);
};

#endif
