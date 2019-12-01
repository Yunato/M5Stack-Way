#ifndef GYRO_H_
#define GYRO_H_
#define M5STACK_MPU6886

#include <M5Stack.h>

class Gyro {

private:
  static constexpr float DEFAULT_OFFSET = 0.0f;
  float mOffset;
  float gyroX;
  float gyroY;
  float gyroZ;

public:
  Gyro(void);
  ~Gyro(void);

  float getAngle(void);
  void setValue(int);
  float getValue(void);
  void reset(void);
  void setupOffset(void);
  float getOffset(void);
};

#endif
