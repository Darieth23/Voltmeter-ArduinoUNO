#include <Adafruit_PCD8544.h>
#include <math.h>
#include <SoftwareSerial.h>

//Pines analógicos de entradas de tensión
int volt1 = A0;

//leds
int led_one = 13;

//Variables de almacenar tensiones:
float v1 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Pines de tensión
  pinMode(volt1, INPUT);
  // Pines de los leds
  pinMode(led_one, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  v1 = 0;
  v1 = analogRead(volt1);
  //if (v1 > 0){
  //  digitalWrite(led_one, HIGH);
  //  delay(5000);
  //}
  //else{
  //  digitalWrite(led_one, LOW);
  //  delay(5000);
  //}
  int brightness = map(v1, 0, 1023, 0, 255);
  digitalWrite(led_one, brightness);
  // Print the sensor value and LED brightness to the serial monitor
  Serial.print("Sensor Value: ");
  Serial.print(v1);
  Serial.print(" | LED Brightness: ");
  Serial.println(brightness);

  delay(100);
}



