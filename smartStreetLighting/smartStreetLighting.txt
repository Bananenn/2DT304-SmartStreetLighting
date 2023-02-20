
// Released to the public domain
#include <FreeRTOS.h>
#include <task.h>
#include <map>
#include <EEPROM.h>

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
const int buttonPin = 12;// the pin our push button is on
int c = 0;

int buttonState = 0;
int pirState = 0;
int oldButtonState = LOW;
int ledState = LOW;

/*
void pir(void *param) {
  (void) param;
  //Serial.println("Running pir task");
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH)
  {
    ledState = (ledState == LOW ? HIGH : LOW);
    digitalWrite(led, ledState);
    Serial.println("MOTION DETECTED!!!");

  }
  oldButtonState = buttonState;
}
*/

void setup() {
  Serial.begin(115200);
  Serial.print("test - start");
  xTaskCreate(blink, "BLINK", 128, nullptr, 1, nullptr);
  //xTaskCreate(pir, "pir", 128, nullptr, 1, nullptr);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buttonPin, INPUT); // Set the Tilt Switch as an input
  delay(500);
}

volatile int val= 0;
void loop() {
  delay(100);
  //Serial.printf("Running PIR\n");
  ps();
  pirState = digitalRead(buttonPin);
  //Serial.printf("Button state");
  //Serial.println(buttonState);

  if (pirState == HIGH)
  {
    ledState = (ledState == LOW ? HIGH : LOW);
    digitalWrite(led, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    Serial.println(" -*-*- Motion detected!!!");
    delay(500);
  }
  Serial.println(" - No motion");
  digitalWrite(led, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}