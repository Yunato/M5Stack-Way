#include <M5Stack.h>
#include "lcd.hpp"
#include "bluetooth.hpp"

// LCD
# define LCD_HEIGHT 240
# define LCD_WIDTH  320

// time
# define SEC_FROM_MICRO   1000000
# define SEC_FROM_MILLI   1000
# define MILLI_FROM_MICRO 1000

TaskHandle_t task1;
// TaskHandle_t task2;

volatile long t_count = -1;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void task1_fun(void *params) {
  int count = 0;
  Bluetooth* bt = new Bluetooth();
  bt->active();
  Lcd* mLcd = new Lcd();
  while (1) {
    delay(1);
    ++count;

    if (t_count > 2) {
      // Print 'count' per 4ms
      timerAlarmDisable(timer);

      char buf[128];
      sprintf(buf, "count  : %d\nt_count: %ld\nreceived: %c", count, t_count, bt->receive());
      mLcd->draw(buf);

      count = 0;
      t_count = -1;

      delay(1000);
      bt->send("From M5Stack\n");
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

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  M5.begin();

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
