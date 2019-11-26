#include "dcmotor.hpp"

DcMotor::DcMotor(int num, int rin_port, int fin_port)
:num(num * 2 + 1),rin_port(rin_port),fin_port(fin_port) {
  pinMode(rin_port, OUTPUT);
  pinMode(fin_port, OUTPUT);

  ledcSetup(this->num, 20000, 16);    // channel 1, 20kHz, 16bit
  ledcAttachPin(rin_port, this->num); // GPIO 16 assigned to channel 1
  ledcSetup(this->num + 1, 20000, 16);    // channel 2, 20kHz, 16bit
  ledcAttachPin(fin_port, this->num + 1); // GPIO 17 assigned to channel 2
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
    ledcWrite(this->num + 1, (int)(p * 65535.0));
  }else{
    ledcWrite(this->num, (int)(p * -1 * 65535.0));
    ledcWrite(this->num + 1, 0);
  }
}
