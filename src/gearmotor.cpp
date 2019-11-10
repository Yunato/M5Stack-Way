#include "gearmotor.hpp"

GearMotor::GearMotor(int rin_port, int fin_port)
:rin_port(rin_port),fin_port(fin_port) {
  pinMode(rin_port, OUTPUT);
  pinMode(fin_port, OUTPUT);
}

GearMotor::~GearMotor(void){
}

void GearMotor::rotate(){
   digitalWrite(rin_port, HIGH);
   digitalWrite(fin_port, LOW);
}

void GearMotor::stop(){
   digitalWrite(rin_port, LOW);
   digitalWrite(fin_port, LOW);
}
