#ifndef DRIVERS_H
#define DRIVERS_H

#include "moduels.hpp"

class Driver{
private:
  Lcd* mlcd = new Lcd();
  Gyro* gyro = new Gyro();
  DcMotor* lgm = new DcMotor(0, ldm_rin_port, ldm_fin_port, ldm_dac_port);
  DcMotor* rgm = new DcMotor(1, rdm_rin_port, rdm_fin_port, rdm_dac_port);
  Ultrasonic* us = new Ultrasonic(us_rin_port, us_fin_port);
public:
	Driver(void);
	~Driver(void);
	bool execute(void);
};

#endif
