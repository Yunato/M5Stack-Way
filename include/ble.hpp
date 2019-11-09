#ifndef BLE_H_
#define BLE_H_

#include <M5Stack.h>
#include "BluetoothSerial.h"

class Ble {
private:
  BluetoothSerial bts;
  int count = 0;

public:
	Ble();
	~Ble();

	void active();
	void stop();
	int receive();
	// void send(const char*);
	void send();

	template <typename tFunction>
	void exec(tFunction func);
};

#endif
