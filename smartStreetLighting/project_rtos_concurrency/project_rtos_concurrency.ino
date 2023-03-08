#include <FreeRTOS.h>
#include <task.h>
#include <map>

std::map<eTaskState, const char *> eTaskStateName { {eReady, "Ready"}, { eRunning, "Running" }, {eBlocked, "Blocked"}, {eSuspended, "Suspended"}, {eDeleted, "Deleted"} };

void ps() {
  int tasks = uxTaskGetNumberOfTasks();
  TaskStatus_t *pxTaskStatusArray = new TaskStatus_t[tasks];
  unsigned long runtime;
  tasks = uxTaskGetSystemState( pxTaskStatusArray, tasks, &runtime );
  //Serial.printf("# Tasks: %d\n", tasks);
  //Serial.println("ID, NAME, STATE, PRIO, CYCLES");
  //for (int i=0; i < tasks; i++) {
    //Serial.printf("%d: %-16s %-10s %d %lu\n", i, pxTaskStatusArray[i].pcTaskName, eTaskStateName[pxTaskStatusArray[i].eCurrentState], (int)pxTaskStatusArray[i].uxCurrentPriority, pxTaskStatusArray[i].ulRunTimeCounter);
  //}
  delete[] pxTaskStatusArray;
}


void blink(void *param) {
  (void) param;
  Serial.printf("Running blink \n");
  
  pinMode(LED_BUILTIN, OUTPUT);
  while (true) {
    Serial.println("BLINK!");
    digitalWrite(LED_BUILTIN, LOW);
    delay(750);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    Serial.println("Loop - test");
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

void pir(void *param) {
  (void) param;
  Serial.printf("Running pir \n");

  while (true) {
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

  } // End of while loop

}

void weatherCheck(void *param){
  (void) param;
  while (true) {
      Serial.println("-------- Checking weather");
      delay(10000);
  }
}

void setup() {

  delay(1000); 
    
  Serial.begin(9600);
  Serial.print("test - start");

  // Serial.begin(115200);

  xTaskCreate(weatherCheck, "weatherCheck", 128, nullptr, 1, nullptr);
  xTaskCreate(pir, "PIR", 128, nullptr, 1, nullptr);
  //RxTaskCreate(weatherAPI, "TEST", 128, nullptr, 1, nullptr);
  //xTaskCreate(blink, "BLINK", 128, nullptr, 3, nullptr);
  //xTaskCreate(weatherAPI, "WEATHERAPI", 512, nullptr, 4, nullptr);

}

int i = 0;
volatile int val= 0;
void loop() {
  ps();
  //delay(500);
  //Serial.printf("Loop passed");
}