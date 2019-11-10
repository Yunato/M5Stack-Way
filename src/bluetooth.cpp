#include "bluetooth.hpp"

/**
 * @brief Constructor
 * @details Setup
 */
Bluetooth::Bluetooth() {
}

/**
 * @brief Destructor
 */
Bluetooth::~Bluetooth() {}

/**
 * @brief Activate BLE
 */
void Bluetooth::active() {
  bts.begin("M5Stack");
}

/**
 * @brief Stop BLE
 */
void Bluetooth::stop() {
  bts.end();
}

/**
 * @brief Receive via BLE
 */
int Bluetooth::receive() {
  return bts.read();
}

/**
 * @brief Send via Bluetooth
 */
void Bluetooth::send(const char* str) {
	uint8_t u[sizeof(str) / sizeof(char)];
	int size = sizeof(u) / sizeof(uint8_t);
	for (int cnt = 0; cnt < size; ++cnt) {
		u[cnt] = (uint8_t)str[cnt];
	}
  bts.write(u, size);
}

/// <summary>
/// Wait for data via Bluetooth
/// </summary>
template <typename tFunction>
void Bluetooth::exec(tFunction func) {
	active();
	int rtn = -1;
	do{
		func();
		delay(10);
  	rtn = receive();
	}while(rtn == -1);
	stop();
}

