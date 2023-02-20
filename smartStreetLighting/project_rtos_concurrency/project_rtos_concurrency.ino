#include <FreeRTOS.h>
#include <task.h>
#include <map>
#include <EEPROM.h>
#include <semphr.h>


std::map<eTaskState, const char *> eTaskStateName { {eReady, "Ready"}, { eRunning, "Running" }, {eBlocked, "Blocked"}, {eSuspended, "Suspended"}, {eDeleted, "Deleted"} };

void ps() {
  int tasks = uxTaskGetNumberOfTasks();
  TaskStatus_t *pxTaskStatusArray = new TaskStatus_t[tasks];
  unsigned long runtime;
  tasks = uxTaskGetSystemState( pxTaskStatusArray, tasks, &runtime );
  delete[] pxTaskStatusArray;
}

void blink(void *param) {
  (void) param;
  Serial.printf("Running blink \n");

  pinMode(LED_BUILTIN, OUTPUT);
  while (true) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(750);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
  }
}

const int led = 13;
const int led2 = 11;
const int led3 = 10;
const int buttonPin = 12; // the pin our push button is on
int c = 0;

int buttonState = 0;
int pirState = 0;
int oldButtonState = LOW;
int ledState = LOW;

bool isLedTaskRunning = false;

SemaphoreHandle_t xMutex;

void ledTask(void *param) {
  (void) param;

  // Wait for the mutex to become available
  xSemaphoreTake(xMutex, portMAX_DELAY);

  digitalWrite(led, HIGH);
  delay(500);
  Serial.println(" LED 1 ON");

  digitalWrite(led2, HIGH);
  delay(500);
  Serial.println(" LED 2 ON");

  digitalWrite(led3, HIGH);
  delay(500);
  Serial.println(" LED 3 ON");

  delay(500);

  digitalWrite(led, LOW);
  Serial.println(" LED 1 OFF");
  delay(500);

  digitalWrite(led2, LOW);
  Serial.println(" LED 2 OFF");
  delay(500);

  digitalWrite(led3, LOW);
  Serial.println(" LED 3 OFF");
  delay(500);

  // Release the mutex
  xSemaphoreGive(xMutex);

  vTaskDelete(nullptr);
  Serial.println(isLedTaskRunning);

  isLedTaskRunning = false;
  Serial.println(isLedTaskRunning);
}


void setup() {
  Serial.begin(9600);
  Serial.print("test - start");

  Serial.begin(115200);
  pinMode(buttonPin, INPUT);

  xMutex = xSemaphoreCreateMutex();

  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  delay(500);
}

int i = 0;
volatile int val= 0;
void loop() {
  int pirState;

  pirState = digitalRead(buttonPin);
  Serial.println(isLedTaskRunning);
  if (pirState == HIGH) {
    if (xSemaphoreTake(xMutex, 0) == pdTRUE) {
      xSemaphoreGive(xMutex);
      isLedTaskRunning = true;
      xTaskCreate(ledTask, "LED" + i, 128, nullptr, 1, nullptr);
      i = i + 1;
      Serial.println(i);
    } else {
      Serial.println("LED task already running");
    }
  }

  Serial.println(" - No motion");
  delay(500);
}