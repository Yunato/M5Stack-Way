#include "dcmotor.hpp"

DcMotor::DcMotor(int num, int rin_port, int fin_port)
:num(num * 2 + 1),rin_port(rin_port),fin_port(fin_port) {
  pinMode(rin_port, OUTPUT);
  pinMode(fin_port, OUTPUT);

  ledcSetup(this->num, 30000, 10);    // channel this->num, 30kHz, 10bit
  ledcAttachPin(rin_port, this->num); // GPIO rin_port assigned to channel this->num
  ledcSetup(this->num + 1, 30000, 10);    // channel this-num + 1, 30kHz, 10bit
  ledcAttachPin(fin_port, this->num + 1); // GPIO fin_port assigned to channel this->num
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

void DcMotor::changeSpeed(int pc) {
  float p = pc / 100.0f;
  if(p > 0){
    ledcWrite(this->num, 0);
    ledcWrite(this->num + 1, (int)(p * 1023.0));
  }else{
    ledcWrite(this->num, (int)(p * -1 * 1023.0));
    ledcWrite(this->num + 1, 0);
  }
}
