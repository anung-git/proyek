#include "max6675.h"
#include <ESP8266WiFi.h>

int thermoDO = D5;
int thermoCLK = D6;
int thermoCS = D7;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup(){
  Serial.begin(9600);
}

void loop(){
  delay(1000);
  Serial.println(thermocouple.readCelsius());
}
