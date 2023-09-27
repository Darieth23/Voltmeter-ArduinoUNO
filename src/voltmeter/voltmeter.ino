#include <Adafruit_PCD8544.h>
#include <math.h>
#include <SoftwareSerial.h>
//Pines analógicos de entradas de tensión
int volt1 = A0;
int switchDC_AC = A5;
int switchCOM = 0;//falta
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
  valSwitchDC_AC = digitalRead(switchDC_AC);//Leer si se quiere AC o DC
  if(valSwitchDC_AC == 1 && switchCOM == 0){//lectura en DC y comunicacion deshabilitada
    digitalWrite(led_one, valSwitchDC_AC);
    v1 = analogRead(volt1) * (5.0 / 1023.0);
    Serial.println(v1);
    valSign1 = digitalRead(sign1);
    if(valSign1 == 0){//valor negativo
      v1 = -4.8*v1;//Esto xq se tiene una ganancia de 24000
      Serial.print("Valor negativo de la señal DC: ");
      Serial.println(v1);
    }
    else{//valor positivo
      v1 = v1 + (v1/1000.0)*3800.0;
      Serial.print("Valor positivo de la señal DC: ");
      Serial.println(v1);
    }
  }
  else if(valSwitchDC_AC == 0){//lectura AC
    digitalWrite(led_one, valSwitchDC_AC);
  }
  delay(100);
}
