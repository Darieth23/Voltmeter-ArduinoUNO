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
  v1 = analogRead(volt1)* (5.0 / 1023.0);
  valSign1 = digitalRead(sign1);
  valSwitchDC_AC = digitalRead(switchDC_AC);
  Serial.print("Valor del switch: ");
  Serial.println(valSwitchDC_AC);
  if(valSwitchDC_AC == 1){//Lectura en DC
    if(valSign1 == 1){//es una señal positiva
      Serial.print("Valor positivo de la señal DC: ");
      Serial.println(v1);
      digitalWrite(led_one, v1);//solo para testear el led, falta logica
    }
    else{//es una señal negativa
      Serial.print("Valor negativo de la señal DC: ");
      Serial.println(-v1);
    }
  }
  else{
    //Serial.print("Signo negativo de la señal DC: ");
    //Serial.print(valSign1);
  }
  delay(100);
}