#include "max6675.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial

char auth[] = "E7Y-LD7XyeXdtyNxYSGbiiHT-6OJuhq-";   //masukan token anda
char ssid[] = "Redmi";            //nama wifi
char pass[] = "1234567890";       //password wifi

int thermoDO = D6;
int thermoCS = D7;
int thermoCLK = D5;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

BlynkTimer timer;
void myTimerEvent(){
  Blynk.virtualWrite(V0,thermocouple.readCelsius());
}

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop(){
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
