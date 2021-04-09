#include <DHT.h>
#include <LiquidCrystal.h>

// temperature setup
int tempPin = 2;
DHT HT(tempPin, DHT11);
float tempF;
// LCD setup
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// DC motor setup
int speedPin=A4;
int dir1 = 4;
int dir2 = A5;
int mSpeed = 255;

String input;

void setup() {
  // setting up motor pins
  pinMode(speedPin, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);

  lcd.begin(16, 2);
  
  Serial.begin(9600); // begins serial monitor
  HT.begin(); // starts up temperature sensor
  
}

void loop() {
  // gets temperature in fahrenheit
  tempF = HT.readTemperature(true);

  // configures direction of the fan
  digitalWrite(dir1, HIGH);
  digitalWrite(dir2, LOW);

  // prints temperature to LCD screen
  lcd.setCursor(0, 0);
  lcd.print("Temp (F): ");
  lcd.print(tempF);

  if(tempF > 82.5) {
    analogWrite(speedPin, mSpeed);
  }
  else if(tempF < 82.5) {
    analogWrite(speedPin, 0);
  }
  delay(500);
  

}