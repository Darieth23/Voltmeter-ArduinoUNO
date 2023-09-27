#include <Adafruit_PCD8544.h>
//#include <math.h>
#include <SoftwareSerial.h>
//Pines analógicos de entradas de tensión
int volt1 = A0;
int switchDC_AC = A5;
int switchCOM = A4;//falta
//Signos de las señales DC
int sign1 = 2;
//leds
int led_one = 1;
//Variables de almacenar tensiones:
float v1 = 0;
float valSign1 = 0;
float valSwitchDC_AC = 0;
float valSwitchCOM = 0;
float temp1 = 0;
float v1rms = 0;
// Conexiones del PCD8544
#define CLK 12
#define DIN 11
#define DC 10
#define CS 9
#define RST 8
//Configuración de la pantalla
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CS, RST);
SoftwareSerial mySerial(0,1);//RX, TX
void setup() {
  Serial.begin(9600);
  //Pines de tensión
  pinMode(volt1, INPUT);
  pinMode(sign1, INPUT);
  pinMode(switchDC_AC, INPUT);
  pinMode(switchCOM, INPUT);
  // Pines de los leds
  pinMode(led_one, OUTPUT);
  display.begin();//pantalla
  display.setContrast(50); // Ajustar el contraste de la pantalla (0-127)
  // Limpiar la pantalla
  display.clearDisplay();

}
void loop() {
  int i = 0;
  valSwitchDC_AC = digitalRead(switchDC_AC);//Leer si se quiere AC o DC
  valSwitchCOM = digitalRead(switchCOM);//Com
  if(valSwitchDC_AC == 1){//lectura en DC y comunicacion deshabilitada
    digitalWrite(led_one, valSwitchDC_AC);
    for(i = 0; i<10000; i++){
      v1 = analogRead(volt1);
    }
    v1 = v1 * (5.0 / 1023.0);
    valSign1 = digitalRead(sign1);
    if(valSign1 == 0){//valor negativo
      v1 = -4.8*v1;//Esto xq se tiene una ganancia de 24000
      //Serial.print("Valor senal DC: ");
      //Serial.print(v1);
      //Serial.println("V");


      display.print("V1: ");
      display.print(v1);
      display.println("V"); 
    }
    else{//valor positivo
      v1 = v1 + (v1/1000.0)*3800.0;
      //Serial.print("Valor senal DC: ");
      //Serial.print(v1);
      //Serial.println("V");

      display.print("V1: ");
      display.print(v1);
      display.println("V"); 


    }
  }
  else if(valSwitchDC_AC == 0){//lectura en AC y comunicacion deshabilitada
    digitalWrite(led_one, valSwitchDC_AC);
    for(i = 0; i<10000; i++){
      temp1 = analogRead(volt1);
      if(temp1 > v1){
        v1 = temp1;
      } 
    }
    v1 = v1 * (5.0 / 1023.0);
    v1 = v1 + (v1/1000.0)*3800.0;
    v1 = v1 * 2; 
    v1rms = v1 * 0.07071;
    //Serial.print("Valor senal AC: ");
    //Serial.print(v1);
    //Serial.println("V");


    display.print("V1: ");
    display.print(v1);
    display.println("V");    
  
  
  }
  if(valSwitchCOM == 1){
    //mySerial.listen();
    Serial.print("Valor senal: ");
    Serial.print(v1);
    Serial.println("V");
    //mySerial.stopListening();
  }

  display.display(); // Actualizar la pantalla
  display.clearDisplay();

}