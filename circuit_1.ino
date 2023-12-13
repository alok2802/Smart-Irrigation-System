#include <LiquidCrystal.h>
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

const int trig_Pin = 6;
const int echo_Pin = 7;
const int temp_Sensor_pin = A1;
const int Ph_Sensor_Pin = A0;

float rad = 100;    //cm
float len = 300;

void setup() {
  lcd.begin(16, 4);
  pinMode(echo_Pin, INPUT);
  pinMode(trig_Pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float water_level = get_level();
  float water_temp = get_temp();
  float phValue = get_ph();
  float volume = (22/7)*rad*(len-water_level);

  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.print(water_level);

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(water_temp);

  lcd.setCursor(0, 2);
  lcd.print("pH: ");
  lcd.print(phValue);

  lcd.setCursor(0, 3);
  lcd.print("Volume: ");
  lcd.print(volume);
}


float get_level() {
  digitalWrite(trig_Pin, LOW);
  delay(2);
  digitalWrite(trig_Pin, HIGH);
  delay(10);
  digitalWrite(trig_Pin, LOW);  
  float duration = pulseIn(echo_Pin, HIGH);
  float distance = duration*0.034/2;
  return distance;  
}

float get_ph(){  
  int buf[10],temp;
  for(int i=0;i<10;i++) {
    buf[i]=analogRead(Ph_Sensor_Pin);
    delay(10);
  }
  for(int i=0;i<9;i++) {
    for(int j=i+1;j<10;j++) {
      if(buf[i]>buf[j]) {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  unsigned long int avgValue=0;
  for(int i=2;i<8;i++)
    avgValue+=buf[i];
  float voltage=(float)avgValue*5.0/1024/6;
  float phValue=3.5*voltage;
  return phValue;
}


float get_temp(){
  float Equ_volt = analogRead(temp_Sensor_pin)*5.0/1023;
  float SensorTemp = 100.0*Equ_volt-50.0;
  return SensorTemp;
}
