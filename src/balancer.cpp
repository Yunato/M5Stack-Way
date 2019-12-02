#include "balancer.hpp"

Balancer::Balancer(void) {
  gyro->reset();
  gyro->setupOffset();
}

Balancer::~Balancer(void) {}

void Balancer::execute(void){
  float angular_velocity = gyro->getAngularVelocity() - gyro->getOffset();
  this->angle += (angular_velocity / 160.0f);
  // this->angle = gyro->getAngle();

  float term1 = this->F1 * angle;
  float term2 = this->F2 * angular_velocity;
  float term3 = this->F3 * velocity / 1000;
  float term4 = this->F4 * distance / 1000;

  float pwr = term1 + term2 + term3 + term4;
  // float max_pwr = 110.0f; // F1 only
  float max_pwr = 1000.0f; // F1 only
  float min_pwr = 1.0f;

  float pwm_max = 200.0f;
  float pwm_min = 60.0f;

  int pwm = 0;
  if (pwr >= max_pwr) {
    pwm = -pwm_max;
  } else if(pwr <= -max_pwr) {
    pwm = pwm_max;
  } else if(abs(pwr) >= min_pwr) {
    pwm = (int)(pwm_min + (pwm_max - pwm_min) * abs(pwr)/ max_pwr);
    if (pwr > 0) {
      pwm *= -1;
    }
  } else {
    pwm = min_pwr;
    if (pwr > 0) {
      pwm *= -1;
    }
  }
  char buf[124];
  sprintf(buf, "pwr: %6.2f, pwm: %d", pwr, pwm);
  Serial.println(buf);

  lgm->setPWM(pwm);
  rgm->setPWM(pwm);
  velocity += (float)pwm;
  distance += (float)velocity;
}

