#include "ble.hpp"

const std::string Ble::SERVICE_UUID        = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
const std::string Ble::CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";

/**
 * @brief Constructor
 * @details Setup
 */
Ble::Ble():pServer(NULL), pCharacteristic(NULL) {
  // Create the BLE Device
  BLEDevice::init("m5-stack");

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  // Create the BLE Service
  pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  // Set the callback handlers
  pCharacteristic->setCallbacks(new CharacteristicCallbacks());
}

/**
 * @brief Destructor
 */
Ble::~Ble() {}

/**
 * @brief Activate BLE
 */
void Ble::active(){
  // Start the service
  pService->start();

  // Start advertising
  pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

/**
 * @brief Stop BLE
 */
void Ble::stop(){
  // Stop the service
  pService->start();

  // Stop advertising
  pAdvertising->stop();
}

/**
 * @brief Receive via BLE
 */
// void Ble::receive(){
//   while(!received) { delay(1); }
// }

/**
 * @brief Send via BLE
 */
// void Ble::send(){
// }

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

