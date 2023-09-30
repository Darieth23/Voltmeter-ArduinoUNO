#include <Adafruit_PCD8544.h>
#include <SoftwareSerial.h>
//Pines analógicos de entradas de tensión
int volt1 = A0;
int volt2 = A1;
int volt3 = A2;
int volt4 = A3;
int switchDC_AC = A5;
int switchCOM = A4;//falta
//Signos de las señales DC
int sign1 = 5;
int sign2 = 6;
int sign3 = 7;
int sign4 = 8;
//leds
int led_one = 1;
int led_two = 2;
int led_three = 3;
int led_four = 4;
//Variables de almacenar tensiones:
float v1 = 0;
float v2 = 0;
float v3 = 0;
float v4 = 0;
float valSign1 = 0;
float valSign2 = 0;
float valSign3 = 0;
float valSign4 = 0;
float valSwitchDC_AC = 0;
float valSwitchCOM = 0;
float temp1 = 0;
float temp2 = 0;
float temp3 = 0;
float temp4 = 0;
// Conexiones del PCD8544
#define CLK 13
#define DIN 12
#define DC 11
#define CS 10
#define RST 9
//Configuración de la pantalla
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CS, RST);
SoftwareSerial mySerial(0,1);//RX, TX
void setup() {
  Serial.begin(9600);
  //Pines de tensión
  pinMode(volt1, INPUT);
  pinMode(volt2, INPUT);
  pinMode(volt3, INPUT);
  pinMode(volt4, INPUT);
  pinMode(sign1, INPUT);
  pinMode(sign2, INPUT);
  pinMode(sign3, INPUT);
  pinMode(sign4, INPUT);
  pinMode(switchDC_AC, INPUT);
  pinMode(switchCOM, INPUT); 
  // Pines de los leds
  pinMode(led_one, OUTPUT);
  pinMode(led_two, OUTPUT);
  pinMode(led_three, OUTPUT);
  pinMode(led_four, OUTPUT);
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
    for(i = 0; i<10000; i++){
      v1 = analogRead(volt1);
      v2 = analogRead(volt2);
      v3 = analogRead(volt3);
      v4 = analogRead(volt4);
    }
    v1 = v1 * (5.0 / 1023.0);
    v2 = v2 * (5.0 / 1023.0);
    v3 = v3 * (5.0 / 1023.0);
    v4 = v4 * (5.0 / 1023.0);
    valSign1 = digitalRead(sign1);
    valSign2 = digitalRead(sign2);
    valSign3 = digitalRead(sign3);
    valSign4 = digitalRead(sign4);
    if(valSign1 == 0){//valor negativo
      v1 = -4.8*v1;//Esto xq se tiene una ganancia 4.8
    }
    else{//valor positivo
      v1 = v1 + (v1/1000.0)*3800.0;
    }
    if(valSign2 == 0){//valor negativo
      v2 = -4.8*v2;//Esto xq se tiene una ganancia de 24000
    }
    else{//valor positivo
      v2 = v2 + (v2/1000.0)*3800.0;
    }
    if(valSign3 == 0){//valor negativo
      v3 = -4.8*v3;//Esto xq se tiene una ganancia de 24000
    }
    else{//valor positivo
      v3 = v3 + (v3/1000.0)*3800.0;
    }
    if(valSign1 == 0){//valor negativo
      v4 = -4.8*v4;//Esto xq se tiene una ganancia de 24000
    }
    else{//valor positivo
      v4 = v4 + (v4/1000.0)*3800.0;
    }
  }
  else if(valSwitchDC_AC == 0){//lectura en AC y comunicacion deshabilitada
    for(i = 0; i<15000; i++){
      temp1 = analogRead(volt1);
      if(temp1 > v1){
        v1 = temp1;
      }
      temp2 = analogRead(volt2);
      if(temp2 > v2){
        v2 = temp2;
      }
      temp3 = analogRead(volt3);
      if(temp3 > v3){
        v3 = temp3;
      }
      temp4 = analogRead(volt4);
      if(temp4 > v4){
        v4 = temp4;
      } 
    }
    v1 = v1 * (5.0 / 1023.0);
    v1 = v1 + (v1/1000.0)*3800.0;
    v1 = v1 * 0.7071;
    v2 = v2 * (5.0 / 1023.0);
    v2 = v2 + (v2/1000.0)*3800.0;
    v2 = v2 * 0.7071;  
    v3 = v3 * (5.0 / 1023.0);
    v3 = v3 + (v3/1000.0)*3800.0;
    v3 = v3 * 0.7071; 
    v4 = v4 * (5.0 / 1023.0);
    v4 = v4 + (v4/1000.0)*3800.0;
    v4 = v4 * 0.7071; 
  }
  if((v1 > 20 || v1 < -20) && valSwitchDC_AC == 1){
    digitalWrite(led_one, 1);
  }
  else if(v1 > 14.1 && valSwitchDC_AC == 0){
    digitalWrite(led_one, 1);
  }
  else{
    display.print("hola");
    digitalWrite(led_one, 0);
  }
  if((v2 > 20 || v2 < -20) && valSwitchDC_AC == 1){
    digitalWrite(led_two, 1);
  }
  else if(v2 > 14.1 && valSwitchDC_AC == 0){
    digitalWrite(led_two, 1);
  }
  else{
    digitalWrite(led_two, 0);
  }
  if((v3 > 20 || v3 < -20) && valSwitchDC_AC == 1){
    digitalWrite(led_three, 1);
  }
  else if(v3 > 14.1 && valSwitchDC_AC == 0){
    digitalWrite(led_three, 1);
  }
  else{
    digitalWrite(led_three, 0);
  }
  if((v4 > 20 || v4 < -20) && valSwitchDC_AC == 1){
    digitalWrite(led_four, 1);
  }
  else if(v4 > 14.1 && valSwitchDC_AC == 0){
    digitalWrite(led_four, 1);
  }
  else{
    digitalWrite(led_four, 0);
  }
  if(valSwitchCOM == 1){
    mySerial.listen();
    Serial.println(v1);
    Serial.println(v2);
    Serial.println(v3);
    Serial.println(v4);
    mySerial.stopListening();
  }
  display.print("V1: ");
  display.print(v1);
  display.println("V");
  display.print("V2: ");
  display.print(v2);
  display.println("V");
  display.print("V3: ");
  display.print(v3);
  display.println("V");
  display.print("V4: ");
  display.print(v4);
  display.println("V");  
  display.display(); // Actualizar la pantalla
  display.clearDisplay();
}