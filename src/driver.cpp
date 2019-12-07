#include "driver.hpp"

/**
 * @brief Constructor
 * @param gyro object for gyro sensor
 * @param lgm object for left gear motor
 * @param rgm object for right gear motor
 */
Driver::Driver(Lcd* mlcd, Gyro* gyro, Motor* lgm, Motor* rgm):
mlcd(mlcd), gyro(gyro), lgm(lgm), rgm(rgm) { }

/**
 * @brief Destructor
 */
Driver::~Driver(void) {}

/**
 * @brief Update
 * @details Start motors, get values from gyro sensor
 */
bool Driver::execute(void){
	// char buf[128];
	while(true){
		// for (int power = 255; power > -255; power -= 51) {
		// 	lgm->setPWM(power);
		// 	rgm->setPWM(power);
		// 	sprintf(buf, "power : %d\ndist: %6.2f\npitch: %6.2f\n", power, us->getDistance(), gyro->getAngle());
		// 	mlcd->draw(buf);
		// 	delay(10);
		// }
		// lgm->setPWM(0);
		// rgm->setPWM(0);
		// sprintf(buf, "stop");
		// mlcd->draw(buf);
		// delay(100);

		lgm->rotate();
		rgm->rotate();
		gyro->read();
		// delayMicroseconds(100);
	}
	return false;
}
