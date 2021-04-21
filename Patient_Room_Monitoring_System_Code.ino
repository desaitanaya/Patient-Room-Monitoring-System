
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>


char auth[] = "nWkGl0pKD2ACBZaJuWbNEH9yyZwkrx9f"; //Enter the Auth code which was send by Blynk

char ssid[] = "Redmi";  //Enter your WIFI Name
char pass[] = "abcd1234";  //Enter your WIFI Password

#define DHTPIN 2 // Digital pin 4

const int ldrpin =5;    //D1 pin

#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

 
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  float q = analogRead(A0);
  int l = digitalRead(ldrpin);
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  

  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);    //V5 is for Humidity
  Blynk.virtualWrite(V6, t);    //V6 is for Temperature
  Blynk.virtualWrite(V0, q);    //V0 is for Air quality
  Blynk.virtualWrite(V1, l);    //V1 is for Light

  

}


void setup()
{
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
