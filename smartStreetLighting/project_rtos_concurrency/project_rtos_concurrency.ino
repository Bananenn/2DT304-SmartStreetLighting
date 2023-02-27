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
int timetoBeON = 0;


void setup() {
  Serial.begin(9600);
  Serial.print("test - start");

  Serial.begin(115200);
  pinMode(buttonPin, INPUT);

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
  if (pirState == HIGH) {
    Serial.println(" ** Motion detected");
    timetoBeON = millis() + 1000;
  }

  if (timetoBeON > millis()) {
    digitalWrite(led, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  } else {
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }

  Serial.println(" - No motion");
  delay(300);
}