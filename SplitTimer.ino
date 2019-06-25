#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define LASER 8

unsigned long startTime;
unsigned long endTime;
bool isTiming = false;
bool stonePassed = false;
double splitTime;

void setup() {
  Serial.begin(9600);
  pinMode(LASER, INPUT);
  lcd.begin(16,2);
  
}

void loop() {
  int detected = digitalRead(LASER);

  if (detected == LOW && !isTiming) {
    Serial.println("Time starts!");
    startTime = millis();
    isTiming = true;
    lcd.clear();
  }

  else if (detected == HIGH && isTiming && !stonePassed) {
    stonePassed = true;
    Serial.println("Stone passed");
  }

  else if (detected == LOW && isTiming && stonePassed) {
    Serial.println("Time ends!");
    endTime = millis();
    isTiming = false;

  
    splitTime = (endTime - startTime) / 1000.0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(splitTime);
    lcd.print(" seconds");
    lcd.setCursor(0,1);
    lcd.print("Nice Shot! ;)");

    Serial.println(splitTime);

    delay(1000);

    stonePassed = false;
  }
}
