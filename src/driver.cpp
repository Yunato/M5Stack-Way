#include "driver.hpp"

Driver::Driver(void) {
  gyro->reset();
	gyro->setupOffset();
}

Driver::~Driver(void) {}

bool Driver::execute(void){
	char buf[128];
	while(true){
		for (int power = 255; power > -255; power -= 51) {
			lgm->setPWM(power);
			rgm->setPWM(power);
			sprintf(buf, "power : %d\ndist: %6.2f\npitch: %6.2f\n", power, us->getDistance(), gyro->getAngle());
			// sprintf(buf, "dist: %6.2f\tpitch: %6.2f\n", power, us->getDistance(), gyro->getAngle());
			// sprintf(buf, "power : %d\npitch: %6.2f\n", power, gyro->getAngle());
			mlcd->draw(buf);
			// Serial.println(buf);
			delay(10);
		}
		lgm->setPWM(0);
		rgm->setPWM(0);
		sprintf(buf, "stop");
		mlcd->draw(buf);
		delay(100);

		// gyro->setupOffset();
		// sprintf(buf, "offset : %6.2f\n", gyro->getOffset());
		// mlcd->draw(buf);
		// delay(3000);

			// Todo: Stop?
	}
	return false;
}
