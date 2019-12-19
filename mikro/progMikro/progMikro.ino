#define BLYNK_USE_DIRECT_CONNECT
#include <BlynkSimpleSerialBLE.h>
char auth[] = "3kxKgOMtJLVV4yn6uC2aze4i_mAiuw52";
BlynkTimer timer;
int setMin,setMax ;

BLYNK_WRITE(V1){
  setMin = param.asInt(); // membaca variabel V1
}
BLYNK_WRITE(V2){
  setMax = param.asInt(); // membaca variabel V2
}
void updateSuhu(){
  unsigned long temptot = 0;
  for(byte x = 0; x < 64; x++) {    
    temptot += analogRead(A5);
  }
  unsigned int temp = temptot >> 6; // bagi hasil dengan 64
  float suhu= temp * 0.48828125;    // 2.0479;
  Blynk.virtualWrite(V0, suhu);
  
  if(suhu<=setMin){
    digitalWrite(A4,HIGH);  //jika suhu kurang dari samadengan setMax relay hidup
    Blynk.virtualWrite(V3, 1023); //hidupkan led
  }
  if(suhu>=setMax){
    digitalWrite(A4,LOW);   //jika suhu lebih besar samadengan setMax relay mati
    Blynk.virtualWrite(V3, 0);  //matikan led
  }
}

void setup(){
  Serial.begin(38400);
  Blynk.begin(Serial, auth);
  timer.setInterval(1000L, updateSuhu);   //update suhu setiap 1000 mili detik
  pinMode(A4,OUTPUT);  //jadikan A4 sebagai output             
}

void loop(){
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
