#include "dcmotor.hpp"

DcMotor::DcMotor(int num, int rin_port, int fin_port, int dac_port)
:num(num * 2 + 1),rin_port(rin_port),fin_port(fin_port),dac_port(dac_port) {
  pinMode(rin_port, OUTPUT);
  pinMode(fin_port, OUTPUT);
  pinMode(dac_port, OUTPUT);
  digitalWrite(rin_port, LOW);
  digitalWrite(fin_port, LOW);
}

DcMotor::~DcMotor(void) {
}

void DcMotor::rotate() {
   digitalWrite(rin_port, HIGH);
   digitalWrite(fin_port, LOW);
}

void DcMotor::stop() {
   digitalWrite(rin_port, LOW);
   digitalWrite(fin_port, LOW);
}

void DcMotor::setPWM(int power) {
  dacWrite(dac_port, power);
  rotate();
}
