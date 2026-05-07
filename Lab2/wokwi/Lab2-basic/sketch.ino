#include<esp_sleep.h>
#include <WiFi.h>

int led = 4;

void activateLed() {
  Serial.println("Paljenje LED");

  digitalWrite(led, HIGH);

  int startTime = millis();
  while(millis() - startTime < 3000) {}
  
  digitalWrite(led, LOW);

  Serial.println("Gasenje LED");
}

void handleWakeup() {
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();

    if (cause == ESP_SLEEP_WAKEUP_TIMER) {
        Serial.println("Timer wakeup");
    } else {
        Serial.println("Prvo paljenje");
    }
}

void sleep() {
  Serial.println("Sleep start");
  Serial.flush();
  delay(500);
  yield();

  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_OFF);
  btStop();
  
  pinMode(led, OUTPUT);

  esp_sleep_enable_timer_wakeup(10 * 1000000);

  handleWakeup();
  activateLed();
  sleep();
}

void loop() {}