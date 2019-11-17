#include "gearmotor.hpp"

GearMotor::GearMotor(int rin_port, int fin_port)
:rin_port(rin_port),fin_port(fin_port) {
  pinMode(rin_port, OUTPUT);
  pinMode(fin_port, OUTPUT);

  ledcSetup(1, 20000, 16);    // channel 1, 20kHz, 16bit
  ledcAttachPin(rin_port, 1); // GPIO 16 assigned to channel 1
  ledcSetup(2, 20000, 16);    // channel 2, 20kHz, 16bit
  ledcAttachPin(fin_port, 2); // GPIO 17 assigned to channel 2
}

GearMotor::~GearMotor(void) {
}

void GearMotor::rotate() {
   digitalWrite(rin_port, HIGH);
   digitalWrite(fin_port, LOW);
}

void GearMotor::stop() {
   digitalWrite(rin_port, LOW);
   digitalWrite(fin_port, LOW);
}

void GearMotor::changeSpeed(int pc) {
  float p = pc / 100.0f;
  if(p > 0){
    ledcWrite(1, 0);
    ledcWrite(2, (int)(p * 65535.0));
  }else{
    ledcWrite(1, (int)(p * -1 * 65535.0));
    ledcWrite(2, 0);
  }
}
