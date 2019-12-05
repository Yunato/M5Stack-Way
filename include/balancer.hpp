#ifndef BALANCER_H
#define BALANCER_H

#include "moduels.hpp"

class Balancer{
private:
  float angle = 0.0f;
  float velocity = 0.0f;
  float distance = 0.0f;
  static constexpr float F1 = 10.0f;
  static constexpr float F2 = 2.0f;
  static constexpr float F3 = 0.0001f;
  static constexpr float F4 = 0.0001f;

  Gyro* gyro = new Gyro();
  Motor* lgm = new Motor(0, ldm_rin_port, ldm_fin_port, ldm_dac_port);
  Motor* rgm = new Motor(1, rdm_rin_port, rdm_fin_port, rdm_dac_port);
  Ultrasonic* us = new Ultrasonic(us_rin_port, us_fin_port);
public:
	Balancer(void);
	~Balancer(void);
	void execute(void);
};

#endif

