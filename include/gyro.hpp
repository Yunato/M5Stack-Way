#ifndef GYRO_H_
#define GYRO_H_
#define M5STACK_MPU6886

#include <M5Stack.h>

class Gyro {

private:
  static const uint8_t DEFAULT_OFFSET = 0;
  uint8_t mOffset;
  float gyroX;
  float gyroY;
  float gyroZ;

public:
  Gyro(void);
  ~Gyro(void);

  float getAngle(void);
  // void checkPort(void);
  void setValue(int);
  float getValue(void);
  void reset(void);
  /*
  void setOffset(int16_t offset);

  int16_t getAnglerVelocity(void) const;
  */
};

#endif
