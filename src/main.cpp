#include <M5Stack.h>
#include "bluetooth.hpp"
#include "moduels.hpp"
#include "driver.hpp"

# define SEC_FROM_MICRO   1000000
# define SEC_FROM_MILLI   1000
# define MILLI_FROM_MICRO 1000

TaskHandle_t balancer_task;

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void task_fun(void *params) {
  Driver* driver = new Driver();
  driver->execute();
}

// 4ms
// - Bluetooth
// - Inverted pendulum
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  // Bluetooth* bt = new Bluetooth();
  // bt->active();
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Power.begin();
  // dacWrite(25, 0); // Speaker OFF

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 0 * SEC_FROM_MICRO + 4 * MILLI_FROM_MICRO + 0, true);
  timerAlarmEnable(timer);

  // task function, task name, stack size, parameter, priority, task handle, task affinity
  xTaskCreatePinnedToCore(task_fun, "task", 4096, NULL, 2, &balancer_task, 0);
}

void loop() {}
