#include <Adafruit_PCD8544.h>
#include <math.h>
#include <SoftwareSerial.h>

//Pines analógicos de entradas de tensión
int volt1 = A0;
int switchDC_AC = A5;

//Signos de las señales DC
int sign1 = 2;

//leds
int led_one = 13;

//Variables de almacenar tensiones:
float v1 = 0;
float valSign1 = 0;
float valSwitchDC_AC = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Pines de tensión
  pinMode(volt1, INPUT);
  pinMode(sign1, INPUT);
  pinMode(switchDC_AC, INPUT);
  // Pines de los leds
  pinMode(led_one, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  v1 = analogRead(volt1)* (5.0 / 1023.0);
  valSign1 = digitalRead(sign1);
  valSwitchDC_AC = digitalRead(switchDC_AC);
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
  Serial.print("Valor del switch: ");
  Serial.print(valSwitchDC_AC);
  

  if(valSwitchDC_AC == 1){
    Serial.print("Signo positivo de la señal DC: ");
    Serial.print(valSign1);
  }
  else{
    Serial.print("Signo negativo de la señal DC: ");
    Serial.print(valSign1);

  }
  // Print the sensor value and LED brightness to the serial monitor
  Serial.print("Sensor Value: ");
  Serial.print(v1);
  //Serial.print(" | LED Brightness: ");
  //Serial.println(brightness);

  delay(100);
}



