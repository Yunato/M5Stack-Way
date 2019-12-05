#include <M5Stack.h>
#include "bluetooth.hpp"
#include "moduels.hpp"
#include "driver.hpp"
#include "balancer.hpp"

# define SEC_FROM_MICRO   1000000
# define SEC_FROM_MILLI   1000
# define MILLI_FROM_MICRO 1000
# define BT_ON 0
# define BT_OFF 1

TaskHandle_t drive_task;
TaskHandle_t bt_task;
TaskHandle_t select_task;

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
uint32_t cp0_regs[18];

Balancer* balancer;
Driver* driver;
Lcd* mlcd;
Gyro* gyro;
Motor* lgm;
Motor* rgm;
bool canExecute = false;
int state = BT_ON;

void task_bt(void *params) {
  char str[128];
  Bluetooth* bt = new Bluetooth();
  int cnt = 0;

  bt->active();
  while(true) {
    if (bt->receive() != -1) {
      canExecute = true;
      bt->stop();
    }
    gyro->read();
    if (++cnt > 1000 / 5) {
      sprintf(str, "%6.2f\n", gyro->getAngle());
      bt->send(str);
      cnt = 0;
    }
    delay(5);
  }
}

void task_drive(void *params) {
  vTaskDelete(select_task);
  mlcd->draw("Initializing...");

  balancer = new Balancer(gyro, lgm, rgm);
  driver = new Driver(mlcd, gyro, lgm, rgm);
  mlcd->draw("Ready");
  if (state == BT_ON) {
    xTaskCreatePinnedToCore(task_bt, "bt_task", 4096, NULL, 1, &bt_task, 0);
    while(!canExecute) {
      delay(10);
    }
    vTaskDelete(bt_task);
  } else {
    char str[128];
    unsigned long start = millis();
    while(millis() - start < 10000) {
      gyro->read();
      sprintf(str, "ready\nangle: %6.2f\n", gyro->getAngle());
      mlcd->draw(str);
    }
  }
  mlcd->draw("Drive");

  timerAlarmEnable(timer);
  driver->execute();
}

void task_select(void *params) {
  while(true) {
    if (M5.BtnA.wasPressed()) {
      state = BT_ON;
      xTaskCreatePinnedToCore(task_drive, "drive_task", 4096, NULL, 3, &drive_task, 0);
    }
    if (M5.BtnB.wasPressed()) {
      state = BT_OFF;
      xTaskCreatePinnedToCore(task_drive, "drive_task", 4096, NULL, 3, &drive_task, 0);
    }
    M5.update();
    delay(10);
  }
}

// 4ms
// - Bluetooth
// - Inverted pendulum
void IRAM_ATTR onTimer() {
  // get FPU state
  uint32_t cp_state = xthal_get_cpenable();

  if(cp_state) {
    // Save FPU registers
    xthal_save_cp0(cp0_regs);
  } else {
    // enable FPU
    xthal_set_cpenable(1);
  }

  portENTER_CRITICAL_ISR(&timerMux);
  balancer->pid();

  portEXIT_CRITICAL_ISR(&timerMux);

  if(cp_state) {
    // Restore FPU registers
    xthal_restore_cp0(cp0_regs);
  } else {
    // turn it back off
    xthal_set_cpenable(0);
  }
}

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Power.begin();
  M5.Speaker.begin();

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 0 * SEC_FROM_MICRO + 4 * MILLI_FROM_MICRO + 0, true);

  xTaskCreatePinnedToCore(task_select, "select_task", 4096, NULL, 2, &select_task, 0);
  mlcd = new Lcd();
  mlcd->draw("Turn on \nthe battery box.\nPlease press\nA button.");

  gyro = new Gyro();
  lgm = new Motor(ldm_rin_port, ldm_fin_port, ldm_dac_port);
  rgm = new Motor(rdm_rin_port, rdm_fin_port, rdm_dac_port);
}

void loop() { vTaskDelay(portMAX_DELAY); }
