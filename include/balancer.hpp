#ifndef BALANCER_H
#define BALANCER_H

#include "moduels.hpp"

class Balancer{
private:
  float angle = 0.0f;
  float velocity = 0.0f;
  float distance = 0.0f;

  static constexpr float F1 = 1.0f;
  static constexpr float F2 = 0.04f;
  static constexpr float F3 = 0.06f;
  static constexpr float F4 = 0.0f;

  static constexpr float P = 1.00f;
  static constexpr float I = 0.005f;
  static constexpr float D = 52.0f;
  float i = 0.0f;

  Gyro* gyro;
  Motor* lgm;
  Motor* rgm;
  // Ultrasonic* us = new Ultrasonic(us_rin_port, us_fin_port);

public:
	Balancer(Gyro*, Motor*, Motor*);
	~Balancer(void);
	void execute(float base_angle);
  void pid(void);
  void reset(void);
};

#endif

