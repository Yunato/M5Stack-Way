#ifndef BLE_H_
#define BLE_H_

#include <M5Stack.h>
#include <BLEDevice.h>

class Ble {
private:
	static const std::string SERVICE_UUID;
	static const std::string CHARACTERISTIC_UUID;
  BLEServer* pServer;
  BLEService* pService;
  BLECharacteristic* pCharacteristic;
  BLEAdvertising* pAdvertising;

public:
	Ble();
	~Ble();

	void active();
	void stop();
	void receive();
	// void send(const char*);

	template <typename tFunction>
	void exec(tFunction func);

  class ServerCallbacks: public BLEServerCallbacks {
    private:
     bool deviceConnected = false;

    public:
      bool isConnected() {
        return deviceConnected;
     }

      void onConnect(BLEServer* pServer) {
        M5.Lcd.println("connect");
        deviceConnected = true;
      };

      void onDisconnect(BLEServer* pServer) {
        M5.Lcd.println("disconnect");
        deviceConnected = false;
     }
    };

  class CharacteristicCallbacks: public BLECharacteristicCallbacks {
    private:
     bool received = false;

    public:
      bool hasReceived() {
        return received;
      }

      void onRead(BLECharacteristic *pCharacteristic) {
        pCharacteristic->setValue("Message from M5Stack");
      }

      void onWrite(BLECharacteristic *pCharacteristic) {
        //std::string value = pCharacteristic->getValue();
        //M5.Lcd.println(value.c_str());
        received = true;
        M5.Lcd.println("Received!");
      }
    };
};

#endif
