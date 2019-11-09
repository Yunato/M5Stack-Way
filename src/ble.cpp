#include "ble.hpp"

/**
 * @brief Constructor
 * @details Setup
 */
Ble::Ble() {
  bts.begin("M5Stack");
}

/**
 * @brief Destructor
 */
Ble::~Ble() {}

/**
 * @brief Activate BLE
 */
void Ble::active(){
}

/**
 * @brief Stop BLE
 */
void Ble::stop(){
}

/**
 * @brief Receive via BLE
 */
int Ble::receive(){
  return bts.read();
}

/**
 * @brief Send via BLE
 */
void Ble::send(){
  bts.write('A' + count);
	count++;
	if ('Z' - 'A' < count){
		count = 0;
	}
  //bts.println();
}

/// <summary>
/// Wait for data via BLE
/// </summary>
template <typename tFunction>
void Ble::exec(tFunction func){
	active();
	// do{
	// 	func();
	// 	delay(10);
	// }while();
  receive();
	stop();
}

