#include <M5Stack.h>
#include "bluetooth.hpp"
#include "moduels.hpp"
#include "driver.hpp"

# define SEC_FROM_MICRO   1000000
# define SEC_FROM_MILLI   1000
# define MILLI_FROM_MICRO 1000

TaskHandle_t balancer_task;

volatile long t_count = -1;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void task_fun(void *params) {
  int count = 0;
  Bluetooth* bt = new Bluetooth();
  bt->active();
  Lcd* mLcd = new Lcd();
  // gyro->reset();
  while (1) {
    delay(1);
    ++count;

    if (t_count > 2) {
      // Print 'count' per 4ms
      timerAlarmDisable(timer);

      char buf[128];
      sprintf(buf, "4ms task");
      // sprintf(buf, "count  : %d\nt_count: %ld\nreceived: %c\ndist: %f\n",
      //  count, t_count, bt->receive(), us->getDistance());
      mLcd->draw(buf);

      count = 0;
      t_count = -1;

      // for (int i = 100; i >= -100; i -= 5) {
      //   gm->changeSpeed(i);
      //   delay(1000);
      // }
      // gm->changeSpeed(0);

      delay(1000);
      timerAlarmEnable(timer);
    }
  }
}

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  //++t_count;
  t_count = 0;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Power.begin();

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 0 * SEC_FROM_MICRO + 4 * MILLI_FROM_MICRO + 0, true);
  timerAlarmEnable(timer);

  // task function, task name, stack size, parameter, priority, task handle, task affinity
  xTaskCreatePinnedToCore(task_fun, "task", 4096, NULL, 2, &balancer_task, 0);
  // xTaskCreatePinnedToCore(task2_fun, "task2", 4096, NULL, 1, &task2, 0);

  Driver* driver = new Driver();
  driver->execute();
}

void loop() {}
