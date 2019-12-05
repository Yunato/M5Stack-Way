#include "motor.hpp"

Motor::Motor(int rin_port, int fin_port, int dac_port)
:rin_port(rin_port), fin_port(fin_port), dac_port(dac_port), power(0) {
  pinMode(rin_port, OUTPUT);
  pinMode(fin_port, OUTPUT);
  pinMode(dac_port, OUTPUT);
  digitalWrite(rin_port, LOW);
  digitalWrite(fin_port, LOW);
}

Motor::~Motor(void) { }

void Motor::setPWM(int power) {
  dacWrite(dac_port, abs(power));
  this->power = power;
}

void Motor::rotate() {
  if (this->power >= 0) {
    digitalWrite(rin_port, HIGH);
    digitalWrite(fin_port, LOW);
  }else {
    digitalWrite(rin_port, LOW);
    digitalWrite(fin_port, HIGH);
  }
}

void Motor::stop() {
   digitalWrite(rin_port, LOW);
   digitalWrite(fin_port, LOW);
}
