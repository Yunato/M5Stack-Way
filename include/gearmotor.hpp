#ifndef GEARMOTOR_H_
#define GEARMOTOR_H_

#include <M5Stack.h>
#include "esp32-hal-ledc.h"

class GearMotor {
private:
  int rin_port;
  int fin_port;

public:
  explicit GearMotor(int rin_port, int fin_port);
  ~GearMotor(void);
  void rotate();
  void stop();
  void changeSpeed(int pc);
};

#endif
