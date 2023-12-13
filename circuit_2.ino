#include <LiquidCrystal.h>
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

#include <dht11.h>
#define DHT11PIN 8
dht11 DHT11;

const int moisture_Sensor_Pin = A0;

void setup() {
  lcd.begin(16, 4);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float moisture_level = get_moisture();
  
  int chk = DHT11.read(DHT11PIN);
  float temp = DHT.temperature;
  float humidity = DHT.humidity;

  float threshold_moisture = 12;  // depends on crop
  if(moisture_level<threshold_moisture){
    digitalWrite(6,1);
  }
  else{
    digitalWrite(6,0);
  }
  
  
  lcd.setCursor(0, 0);
  lcd.print("moisture_level: ");
  lcd.print(moisture_level);

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temp);

  lcd.setCursor(0, 2);
  lcd.print("humidity: ");
  lcd.print(humidity);

  lcd.setCursor(0, 3);
  lcd.print("Motor: ");
  if (digitalRead(motorPin) == HIGH) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }
}


float get_moisture() {
  float moisture_percentage;
  int sensor_analog = analogRead(moisture_Sensor_Pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  return moisture_percentage;
}
