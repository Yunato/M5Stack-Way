#ifndef DRIVERS_H
#define DRIVERS_H

#include "moduels.hpp"

class Driver{
private:
  // Gyro* gyro = new Gyro();
  DcMotor* gm = new DcMotor(dm_rin_port, dm_fin_port);
  Ultrasonic* us = new Ultrasonic(us_rin_port, us_fin_port);
public:
	Driver(void);
	~Driver(void);
	bool execute(void);
};

#endif
