#include "DHT.h"

#define role 2
#define led0 8 // green
#define led1 7 // red
#define led2 9 // blue

#define DHTPIN 3
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
 Serial.begin(9600);
 dht.begin();
 pinMode(role,OUTPUT);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(7,OUTPUT);


}

void loop() {
  delay(5000);


  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("%  Temperature: "));
  Serial.print(t);

  if(t<35.00){
      digitalWrite(led2,HIGH);
      digitalWrite(led0,LOW);
      digitalWrite(led1,LOW);
      
      digitalWrite(role,HIGH);
      Serial.print(" - Light is On \n");
    }
  if(t>=36.00){
      digitalWrite(led1,HIGH);
      digitalWrite(led2,LOW);
      digitalWrite(led0,LOW);

    }
  if (t>=35.00){
    digitalWrite(role,LOW);
    if(t<36.00){
      digitalWrite(led0,HIGH);
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
    }
    Serial.print(" - Light is Off \n");
  }

}
