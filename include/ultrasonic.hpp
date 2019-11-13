#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <M5Stack.h>

class Ultrasonic {

private:
  double value;
  int echo_port;
  int trig_port;
  const double speed_of_sound = 340.0 * 100.0 / 1000000.0;

public:
  explicit Ultrasonic(int echo_port, int trig_port);
  ~Ultrasonic(void);
  double getDistance(void);
  void setValue(double);
  double getValue(void);
};

#endif
