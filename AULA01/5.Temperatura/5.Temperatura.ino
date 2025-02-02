#include "DHT.h"
 
#define DHTPIN A1 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 
 
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
DHT dht(DHTPIN, DHTTYPE);

float h;
float t;

void setup() 
{
  Serial.begin(9600);
  while(!Serial);

  Serial.println("T, H");

  dht.begin();

  pinMode(LED_BUILTIN, OUTPUT);


  for( int i = 0; i < 3; ++i)
  {    
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
  }


}
 
void loop() 
{

  // Reading temperature or humidity takes about 250 milliseconds!
  h = dht.readHumidity();
  t = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else
  {
    Serial.print(t);
    Serial.print(" ");
    Serial.println(h);
  }
}

