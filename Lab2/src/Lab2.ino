#include<esp_sleep.h>
#include <WiFi.h>

int led = 4;

void activateLed() {
  Serial.println("Paljenje LED");

  digitalWrite(led, HIGH);

  int startTime = millis();
  while(millis() - startTimme < 3000) {}
  
  digitalWrite(led, LOW);

  Serial.println("Gasenje LED");
}

void handleWakeup() {
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();

    if (cause == ESP_SLEEP_WAKEUP_TIMER) {
        Serial.println("Timer wakeup");
    } else {
        Serial.println("Prvo pokretanje");
    }
}

void sleep() {
  esp_sleep_enable_timer_wakeup(10 * 1000000);
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_OFF);
  btStop();
  
  pinMode(led, OUTPUT);

  handleWakeup();
  activateLed();

  Serial.flush();
  delay(100);

  sleep();
}

void loop() {}
