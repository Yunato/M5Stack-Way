#ifndef MOTOR_H_
#define MOTOR_H_

#include <M5Stack.h>
#include "esp32-hal-ledc.h"

class Motor {
private:
  int rin_port;
  int fin_port;
  int dac_port;
  int power;

public:
  explicit Motor(int rin_port, int fin_port, int dac_port);
  ~Motor(void);
  void setPWM(int power);
  void rotate();
  void stop();
};

#endif
