#include "Servo.h"
#include <LiquidCrystal.h>

#define SERVO_PIN 3 // Digital pin connected to the DHT sensor

#define SAMPLE_TIME 200 // PID interval in miliseconds

#define SET_POINT 50 //
#define START_TEMPERATURE 30

#define VALVE_OFFSET 90
#define WARMUP_RATE 0.05
#define COOLDOWN_RATE 0.01

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

Servo valveServo; // Servo controller

int currentPos = 0; // Servo position 0 = midpoint

float kp = 5, ki = 2.5, kd = 0.01;

long time, startTime;
long et;

float dt, error = 0, pError = 0, integralError = 0, derivativeError = 0;
float currentTemp = START_TEMPERATURE, pid;


void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("SP, PV");

  valveServo.attach(SERVO_PIN);
  valveServo.write(VALVE_OFFSET + currentPos);

  lcd.begin(16, 2);

  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("CONTROLE P.I.D.");
  lcd.setCursor(0, 1);
  lcd.print("TEMPERATURA:00.0");

  for ( int i=0; i < 3; ++i)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

  }

  startTime = millis();
  randomSeed(startTime);
}
 

void loop() 
{
  
  et = millis() - startTime;

  if ( et > SAMPLE_TIME)
  {
    startTime = millis();

    dt = (float)et/1000;
    error = SET_POINT - currentTemp;

    integralError = integralError + (float)error * dt;
    derivativeError = (float)(error - pError)/dt;

    pError = error;

    pid = kp*error + ki * integralError + kd * derivativeError;

    currentPos = VALVE_OFFSET - (int)(pid);
    currentPos = constrain(currentPos,0,180);

    valveServo.write(currentPos);

    currentTemp += (pid * WARMUP_RATE) - (currentTemp - START_TEMPERATURE) * COOLDOWN_RATE;

  }

  if ( random(100) > 85 && (int)(millis()/1000) % 15 == 0 )
  {
    currentTemp += random(20);
    currentTemp -= random(10);
  }

  Serial.print(SET_POINT);
  Serial.print(" ");
  Serial.println(currentTemp);

  lcd.setCursor(12, 1);
  lcd.print(currentTemp);

  
}
