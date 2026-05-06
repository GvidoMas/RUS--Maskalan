#include<esp_sleep.h>
#include <WiFi.h>

int led = 4;
int btn = 2;

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

    if (cause == ESP_SLEEP_WAKEUP_EXT0) {
        Serial.println("Buđenje tipkalom");

        delay(50);
        if (digitalRead(btn) == LOW) {
          Serial.println("Validan događaj!");
        }
    } else {
        Serial.println("Prvo pokretanje");
    }
}

void sleep() {
  Serial.println("Sleep start");
  Serial.flush();
  delay(100);

  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_OFF);
  btStop();
  
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP);

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 1);

  handleWakeup();
  activateLed();
  sleep();
}

void loop() {}
