#include <M5Stack.h>
#include <BLEDevice.h>
#include "lcd.hpp"

// LCD
# define LCD_HEIGHT 240
# define LCD_WIDTH  320

// time
# define SEC_FROM_MICRO   1000000
# define SEC_FROM_MILLI   1000
# define MILLI_FROM_MICRO 1000

// BLE
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;

TaskHandle_t task1;
// TaskHandle_t task2;

volatile long t_count = -1;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void task1_fun(void *params) {
  int count = 0;
  Lcd* mLcd = new Lcd();
  while (1) {
    delay(1);
    ++count;

    if (t_count > 2) {
      // Print 'count' per 4ms
      timerAlarmDisable(timer);

      char buf[128];
      sprintf(buf, "count  : %d\nt_count: %ld\n", count, t_count);
      mLcd->Draw(buf);

      count = 0;
      t_count = -1;

      delay(1000);
      timerAlarmEnable(timer);
    }
  }
}

// void task2_fun(void *params) {
//   int count = 0;
//   while (1) {
//     ++count = 0;
//     vTaskDelay(4);
//   }
// }

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  ++t_count;
  portEXIT_CRITICAL_ISR(&timerMux);
}

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      M5.Lcd.println("connect");
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      M5.Lcd.println("disconnect");
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
  void onRead(BLECharacteristic *pCharacteristic) {
    pCharacteristic->setValue("Message from M5Stack");
  }

  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    M5.Lcd.println(value.c_str());
  }
};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  M5.begin();

  // Create the BLE Device
  BLEDevice::init("m5-stack");

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 0 * SEC_FROM_MICRO + 4 * MILLI_FROM_MICRO + 0, true);
  timerAlarmEnable(timer);

  // task function, task name, stack size, parameter, priority, task handle, task affinity
  xTaskCreatePinnedToCore(task1_fun, "task1", 4096, NULL, 2, &task1, 0);
  // xTaskCreatePinnedToCore(task2_fun, "task2", 4096, NULL, 1, &task2, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
}
