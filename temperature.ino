#include <DHT.h>
#include <LiquidCrystal.h>

// temperature setup
int tempPin = 2;
DHT HT(tempPin, DHT11);
float tempF;
float tempC;
// LCD setup
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// DC motor setup
int speedPin = A4;
int dir1 = 4;
int dir2 = A5;
int mSpeed = 1251;

float setTemp;
float finalTemp = 85.0;

bool isCel = false;
void setup() {
  // setting up motor pins
  pinMode(speedPin, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);

  lcd.begin(16, 2);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  Serial.begin(19200); // begins serial monitor
  HT.begin(); // starts up temperature sensor
  
 
  // initial starting screen
  tempF = HT.readTemperature(true);
  tempC = HT.readTemperature();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp (F): ");
  lcd.print(tempF);
  lcd.setCursor(0, 1);

}

void loop() {
  
  // gets temperature in fahrenheit and celcius
  
  setTemp = Serial.readString().toFloat();
   
   lcd.clear();
   if(setTemp != 0)
   {
    finalTemp = setTemp; 
   }
   if(isCel == true)
   {
    lcd.setCursor(0, 0);
    lcd.print("Temp (C): ");
    lcd.print(tempC);    
    
   }
   else if(isCel == false)
   {
     lcd.setCursor(0, 0);
     lcd.print("Temp (F): ");
     lcd.print(tempF);
 
   }
 
  
  lcd.setCursor(0, 1);
  lcd.print(finalTemp);
  tempF = HT.readTemperature(true);
  tempC = HT.readTemperature();
  
  // configures direction of the fan
  digitalWrite(dir1, HIGH);
  digitalWrite(dir2, LOW);

  // powers fan based on temperature
  if (tempF > finalTemp) {
    analogWrite(speedPin, mSpeed);
  }
  else if (tempF < finalTemp) {
    analogWrite(speedPin, 0);
  }

  // buttons
  if(analogRead(A0) > 1000) {
    lcd.clear();
    isCel = false;
  }
  if(analogRead(A1) > 1000) {
    lcd.clear();
    isCel = true;  
  }

  delay(100);

}