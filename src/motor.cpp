#include "motor.hpp"

/**
 * @brief Constructor
 * @details Setup for pins
 * @param rin_port IN1 for TA7291P
 * @param fin_port IN2 for TA7291P
 * @param dac_port Vref for TA7291P
 */
Motor::Motor(int rin_port, int fin_port, int dac_port)
:rin_port(rin_port), fin_port(fin_port), dac_port(dac_port), power(0) {
  pinMode(rin_port, OUTPUT);
  pinMode(fin_port, OUTPUT);
  pinMode(dac_port, OUTPUT);
  digitalWrite(rin_port, LOW);
  digitalWrite(fin_port, LOW);
}

/**
 * @brief Destructor
 */
Motor::~Motor(void) { }

/**
 * @brief Set PWM for the motor
 * @details Set turning force for the motor (Not turn)
 * @param power PWM value
 */
void Motor::setPWM(int power) {
  dacWrite(dac_port, abs(power));
  this->power = power;
}

/**
 * @brief Turn the motor
 * @details Turn the motor according to the PWM value
 */
void Motor::rotate() {
  if (this->power >= 0) {
    digitalWrite(rin_port, HIGH);
    digitalWrite(fin_port, LOW);
  }else {
    digitalWrite(rin_port, LOW);
    digitalWrite(fin_port, HIGH);
  }
}

/**
 * @brief Stop motor rotation
 */
void Motor::stop() {
   digitalWrite(rin_port, LOW);
   digitalWrite(fin_port, LOW);
}
