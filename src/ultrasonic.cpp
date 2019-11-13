#include "ultrasonic.hpp"

Ultrasonic::Ultrasonic(int echo_port, int trig_port)
: value(0), echo_port(echo_port), trig_port(trig_port) {
  pinMode(echo_port, INPUT);
  pinMode(trig_port, OUTPUT);
}

Ultrasonic::~Ultrasonic(void) {}

double Ultrasonic::getDistance(void) {
  digitalWrite(trig_port, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_port, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_port, LOW);
  double duration = pulseIn(echo_port, HIGH);
  this->value = duration > 0 ? (duration / 2.0) * speed_of_sound : 0.0;
  return this->value;
}

void Ultrasonic::setValue(double value) {
	this->value = value;
}

double Ultrasonic::getValue() {
	return this->value;
}
