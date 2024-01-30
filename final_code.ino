#define BLYNK_TEMPLATE_ID "TMPL3nUqaVFtx"
#define BLYNK_TEMPLATE_NAME "plant watering"
#define BLYNK_AUTH_TOKEN "9Ssy_6I1kA-yKSsuVKgYh4ZVxcHugsBE"
#define BLYNK_PRINT Serial
#define relayPin 2
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int soilMoisturePin = 32;
const int soilMoisturePin2 = 33;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Python";
char pass[] = "Umang9876";
BlynkTimer timer;
bool relayState = false; // Variable to track relay state
LiquidCrystal_I2C lcd(0x27, 20, 4);

void lcd_disc(float v1, float v2) {
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("A1 : ");
  lcd.print(v1);
  lcd.setCursor(2, 1);
  lcd.print("A2 : ");
  lcd.print(v2);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(relayPin, OUTPUT);
}

BLYNK_WRITE(V3) {
  relayState = param.asInt(); // Update relay state based on Blynk app input
  digitalWrite(relayPin, relayState ? HIGH : LOW); // Set relay state
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin);
  int soilMoistureValue2 = analogRead(soilMoisturePin2);
  soilMoistureValue -= 1100;
  soilMoistureValue2 -= 1100;
  float val1 = 0.033 * soilMoistureValue;
  val1 = 100 - val1;
  float val2 = 0.033 * soilMoistureValue2;
  val2 = 100 - val2;

  Serial.print("M Value1 ");
  Serial.println(soilMoistureValue);
  Serial.print("M Value2 ");
  Serial.println(soilMoistureValue2);

  lcd_disc(val1, val2);
  Blynk.run();

  Blynk.virtualWrite(V0, val1);
  Blynk.virtualWrite(V1, val2);

  delay(2000); // Add a delay to avoid flooding the serial monitor
}
