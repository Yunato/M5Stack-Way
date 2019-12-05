#ifndef MOTOR_H_
#define MOTOR_H_

#include <M5Stack.h>
#include "esp32-hal-ledc.h"

class Motor {
private:
  int num;
  int rin_port;
  int fin_port;
  int dac_port;
  void rotate(bool is_positive_rotate);

public:
  explicit Motor(int num, int rin_port, int fin_port, int dac_port);
  ~Motor(void);
  void stop();
  void setPWM(int pc);
};

#endif
