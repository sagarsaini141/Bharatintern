#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MQ135.h>

#define BUZZER_PIN 2      // Pin connected to the buzzer for high pollution alert

Adafruit_MQ135 gasSensor(A0);  // Create an Adafruit_MQ135 object for gas sensor

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address and display size (adjust according to your LCD)

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging

  lcd.begin(16, 2);    // Initialize LCD display
  lcd.print("Air Quality");   // Display initial message
  lcd.setCursor(0, 1);
  lcd.print("Monitoring");

  pinMode(BUZZER_PIN, OUTPUT);  // Set the buzzer pin as output
}

void loop() {
  float gasResistance = gasSensor.readResistance();  // Read gas resistance value
  float airQuality = gasSensor.readAirQuality(gasResistance);  // Calculate air quality index

  Serial.print("Air Quality: ");
  Serial.println(airQuality);

  lcd.clear();
  lcd.print("Air Quality:");
  lcd.setCursor(0, 1);
  lcd.print(airQuality);

  if (airQuality > 100) {
    // If air quality index crosses a threshold, trigger the buzzer or LED
    digitalWrite(BUZZER_PIN, HIGH);  // Turn on the buzzer or LED
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // Turn off the buzzer or LED
  }

  delay(2000);  // Delay between readings (adjust as per your requirement)
}
