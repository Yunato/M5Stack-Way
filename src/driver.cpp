#include "driver.hpp"

Driver::Driver(void) {
  gyro->reset();
}

Driver::~Driver(void) {}

bool Driver::execute(void){
	int count = 0;
	while(true){
		delay(500);
		++count;

		for(int pwm = -100; pwm <= 100; pwm += 10){
      lgm->changeSpeed(pwm);
      rgm->changeSpeed(-pwm);
			delay(1000);
		}
		lgm->changeSpeed(0);
		rgm->changeSpeed(0);

		if (count >= 1) {
			char buf[128];
			sprintf(buf, "count : %d", count);
			mlcd->draw(buf);

			count = 0;
			delay(10000);
		}

    // gyro
		// if(INVERT_GS_RATE < std::abs(gyroRate)){
		// 	return true;
		// }

    // button or bluetooth
    // break

    // dist

    // up tail
	}
	return false;

}
