//LDC init
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
int interval=1000,buzzFlag=0,flag=0;
void setup() {
 //Setup Serial Monitor
 Serial.begin(9600);

 //LCD init
 lcd.begin(16,2);
 lcd.init();
 lcd.backlight();
 
 //Setup and Connect to WIFI
 WiFi.begin("Suny Samsung","12344567");
 lcd.print("Connecting");
 while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
 }
 lcd.clear();
 lcd.print("Connected!");
 
 //Setup Two Sonar Sensors
 pinMode(D3,OUTPUT);//tringPin 1
 pinMode(D4,INPUT);//echoPin 2

 //setup button
 pinMode(D5,OUTPUT);
  
 //Buzzer Setup
 pinMode(D0,OUTPUT);
 delay(1000);
 lcd.clear();

 HTTPClient http4;
 http4.begin("http://192.168.43.199:8000/changeStatus/0");
 http4.GET();
}

void loop() {
 //mesure data from sonars
 int sonarValue = sonarData();
 //Serial.println(sonarValue);
 if(sonarValue<=20 && sonarValue!=0){
    alarm(1);
    lcd.setCursor(0,0);
    lcd.print("Path: Obstacle");
  }else{
    alarm(0);
    lcd.setCursor(0,0);
    lcd.print("Path:Clear!   ");
  }
 //setting up api connection to parse data and show to LCD
  HTTPClient http,http2,http3;
  //the api will hit if user want to know what is in the front
  if(digitalRead(D5) == 1){
    lcd.setCursor(0,1);
    lcd.print("              ");
    delay(500);
    if(flag == 1){flag=0;http.begin("http://192.168.43.199:8000/changeStatus/0");
      http.GET();}else{flag=1;}
  }

  if(flag == 1){
        if(WiFi.status() == WL_CONNECTED){
        Serial.println("conn established");
        http2.begin("http://192.168.43.199:8000/changeStatus/1");
        http2.GET();
        delay(10);
        http3.begin("http://192.168.43.199:8000/getObject");
        int httpCode = http3.GET();
        if (httpCode > 0) {
          String payload = http3.getString();
          lcd.setCursor(0,1);
          Serial.println(payload);
          lcd.print(payload);
          delay(500);
          }
        }
            
    }else{
      lcd.setCursor(0,1);
      lcd.print("              ");
    }
  
}

int sonarData()
{
  digitalWrite(D3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(D3, HIGH);
  delayMicroseconds(10);
  digitalWrite(D3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(D4, HIGH);
  // Calculating the distance
  int distance= duration*0.034/2;
  return distance;
}

void alarm(int warning)
{
  int a = millis();
  if(a>interval && warning==1){
    interval = interval + 1000;
    if(buzzFlag == 0){
        buzzFlag = 1;
        digitalWrite(D0,HIGH);
      }else{
        buzzFlag = 0;
        digitalWrite(D0,LOW);  
      }
  }else{
    digitalWrite(D0,LOW);
  }
}
