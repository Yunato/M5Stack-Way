#include "balancer.hpp"

/**
 * @brief Constructor
 * @details Setup for gyro sensor and motors
 * @param gyro object for gyro sensor
 * @param lgm object for left gear motor
 * @param rgm object for right gear motor
 */
Balancer::Balancer(Gyro* gyro, Motor* lgm, Motor* rgm):
gyro(gyro), lgm(lgm), rgm(rgm) {
  gyro->setup();
}

/**
 * @brief Destructor
 */
Balancer::~Balancer(void) { }

/**
 * @brief Control based on equation of motion　(Not work)
 */
void Balancer::execute(float base_angle) {
  float angular_velocity = gyro->getAngularVelocity() - gyro->getOffset();
  this->angle += (angular_velocity / 160.0f);
  // this->angle = gyro->getAngle();

  float term1 = this->F1 * angle;
  float term2 = this->F2 * angular_velocity;
  float term3 = this->F3 * velocity / 1000;
  float term4 = this->F4 * distance / 1000;

  float pwr = term1 + term2 + term3 + term4;
  float max_pwr = 60.0f;
  float min_pwr = 1.0f;

  float pwm_max = 250.0f;
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

/**
 * @brief PID Control
 */
void Balancer::pid() {
  // gyro->kalmanFilter();
  // float angular_velocity = gyro->getFilterd() - gyro->getFilterdOffset();
  // float p = angular_velocity;
  // i = p * 4.0f;
  // float d = (p - last_p) / 4.0f;
  // float pwr = P * p + I * i + D * d;
  // last_p = p;

  float angular_velocity = gyro->getAngularVelocity() - gyro->getOffset();
  this->angle += angular_velocity;
  float p = this->angle;
  i += p * 4.0f;
  float d = angular_velocity / 4.0f;
  float pwr = P * p + I * i + D * d;
  float max_pwr = 5000.0f;
  float min_pwr = 1.0f;

  float pwm_max = 250.0f;
  float pwm_min = 30.0f;

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
    pwm = pwm_min;
    if (pwr > 0) {
      pwm *= -1;
    }
  }
  char buf[124];
  sprintf(buf, "pwr: %6.2f, pwm: %d, velocity: %6.2f", pwr, pwm, velocity);
  Serial.println(buf);
  lgm->setPWM(pwm);
  rgm->setPWM(pwm);
}

/**
 * @brief Reset
 */
void Balancer::reset(void) {
  angle = 0.0f;
  velocity = 0.0f;
  distance = 0.0f;
}
