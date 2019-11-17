#ifndef GEARMOTOR_H_
#define GEARMOTOR_H_

#include <M5Stack.h>
#include "esp32-hal-ledc.h"

class DcMotor {
private:
  int rin_port;
  int fin_port;

public:
  explicit DcMotor(int rin_port, int fin_port);
  ~DcMotor(void);
  void rotate();
  void stop();
  void changeSpeed(int pc);
};

#endif
