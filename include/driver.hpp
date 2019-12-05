#ifndef DRIVERS_H
#define DRIVERS_H

#include "moduels.hpp"

class Driver {
private:
  Lcd* mlcd;
  Gyro* gyro;
  Motor* lgm;
  Motor* rgm;
  // Ultrasonic* us = new Ultrasonic(us_rin_port, us_fin_port);

public:
	Driver(Lcd*, Gyro*, Motor*, Motor*);
	~Driver(void);
	bool execute(void);
  void stop(void);
};

#endif
