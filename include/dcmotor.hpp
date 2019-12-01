#ifndef GEARMOTOR_H_
#define GEARMOTOR_H_

#include <M5Stack.h>
#include "esp32-hal-ledc.h"

class DcMotor {
private:
  int num;
  int rin_port;
  int fin_port;
  int dac_port;
  void rotate(bool is_positive_rotate);

public:
  explicit DcMotor(int num, int rin_port, int fin_port, int dac_port);
  ~DcMotor(void);
  void stop();
  void setPWM(int pc);
};

#endif
