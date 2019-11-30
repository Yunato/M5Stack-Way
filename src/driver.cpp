#include "driver.hpp"

Driver::Driver(void) {
  gyro->reset();
}

Driver::~Driver(void) {}

bool Driver::execute(void){
	char buf[128];
	while(true){
		for (int power = 0; power <= 255; power += 51) {
			lgm->setPWM(power);
			rgm->setPWM(power);
			sprintf(buf, "power : %d", power);
			mlcd->draw(buf);
			delay(3000);
		}
		lgm->setPWM(0);
		rgm->setPWM(0);
		sprintf(buf, "stop");
		mlcd->draw(buf);
		delay(3000);
	}
	return false;
}
