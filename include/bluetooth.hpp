#ifndef BLE_H_
#define BLE_H_

#include <M5Stack.h>
#include <vector>
#include "BluetoothSerial.h"

class Bluetooth {
private:
  BluetoothSerial bts;
  int count = 0;

public:
	Bluetooth();
	~Bluetooth();

	void active();
	void stop();
	int receive();
	void send(const char*);

	template <typename tFunction>
	void exec(tFunction func);
};

#endif
