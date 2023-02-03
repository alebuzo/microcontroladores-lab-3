//
// Voltimetro_dc.ino
// hispavila.com
// Construcción de un voltímetro DC con Arduino
// 20.09.2015
// Utiliza el monitor Serial para mostrar los valores.
//
 

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#define LED1 0
#define LED2 1
#define LED3 8
#define LED4 9
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 2);
float v0 = 4.98; // valor real de la alimentacion de Arduino, Vcc
float r1 = 100000; // 100k
float r2 = 10000; // 10K
float v_1 = 0;
float v_2 = 0;
float v_3 = 0;
float v_4 = 0;
 
void setup() {
pinMode(13, INPUT);
pinMode(12, INPUT); 
pinMode(11, INPUT);
pinMode(10, INPUT);
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT); 
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);

Serial.begin(9600);
display.begin();
display.setContrast(57);
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(BLACK);
display.setCursor(0,0);
display.clearDisplay();
Serial.println("--------------------");
Serial.println("DC VOLTMETER");
Serial.print("Maximum Voltage: ");
Serial.print((int)(v0 / (r2 / (r1 + r2))));
Serial.println("V");
Serial.println("--------------------");
Serial.println(""); 
delay(2000);
}

void loop() {


  uint16_t max_v1 = 0;
    for(uint8_t i = 0; i < 100; i++) {
    uint16_t r = analogRead(5);  // read from analog channel 3 (A3)
    if(max_v1 < r) max_v1 = r;
    delayMicroseconds(200);
  }

  uint16_t max_v2 = 0;
    for(uint8_t i = 0; i < 100; i++) {
    uint16_t r = analogRead(4);  // read from analog channel 3 (A3)
    if(max_v2 < r) max_v2 = r;
    delayMicroseconds(200);
  }

  uint16_t max_v3 = 0;
    for(uint8_t i = 0; i < 100; i++) {
    uint16_t r = analogRead(3);  // read from analog channel 3 (A3)
    if(max_v3 < r) max_v3 = r;
    delayMicroseconds(200);
  }

  uint16_t max_v4 = 0;
    for(uint8_t i = 0; i < 100; i++) {
    uint16_t r = analogRead(2);  // read from analog channel 3 (A3)
    if(max_v4 < r) max_v4 = r;
    delayMicroseconds(200);
  }
  int interruptor1 = digitalRead(10);   //lee el estado del botón
  int interruptor2 = digitalRead(11);   //lee el estado del botón
  int interruptor3 = digitalRead(12);   //lee el estado del botón
  int interruptor4 = digitalRead(13);   //lee el estado del botón

  if(interruptor1==HIGH) {          //si el estado es pulsado

    float v_00 = max_v1*0.00488*(1+r1/r2);
     v_1 = v_00 *0.7071+0.7; 

  }

  else{                                   //si el estado es no pulsado

     float v = analogRead(5) *0.00488;
      v_1 = v / (r2 / (r1 + r2));   

  }

  if(interruptor2==HIGH) {          //si el estado es pulsado

     float v_00 = max_v2*0.00488*(1+r1/r2);
     v_2 = v_00 *0.7071+0.7;  

  }

  else{                                   //si el estado es no pulsado

     float v = analogRead(4) *0.00488;
      v_2 = v / (r2 / (r1 + r2));    

  }


  if(interruptor3==HIGH) {          //si el estado es pulsado

     float v_00 = max_v3*0.00488*(1+r1/r2);
     v_3 = v_00 *0.7071+0.7;  

  }

  else{                                   //si el estado es no pulsado

     float v = analogRead(3) *0.00488;
      v_3 = v / (r2 / (r1 + r2));    

  }


  if(interruptor4==HIGH) {          //si el estado es pulsado

    float v_00 = max_v4*0.00488*(1+r1/r2);
      v_4 = v_00 *0.7071+0.7; 

  }

  else{                                   //si el estado es no pulsado

   

      float v = analogRead(2) *0.00488;
      v_4 = v / (r2 / (r1 + r2));    

  }

// ENCENDIDO DE LEDs DE EMERGENCIA POR LIMITE DE TENSION 

  if (20 < v_1 || v_1 < -20) {
    digitalWrite(LED1, HIGH);
  }
  else {
    digitalWrite(LED1, LOW);
  }

    if (20 < v_2 || v_2 < -20) {
    digitalWrite(LED2, HIGH);
  }
  else {
    digitalWrite(LED2, LOW);
  }

  if (20 < v_3 || v_3 < -20) {
    digitalWrite(LED3, HIGH);
  }
  else {
    digitalWrite(LED3, LOW);
  }

  if (20 < v_4 || 4 < -20) {
    digitalWrite(LED4, HIGH);
  }
  else {
    digitalWrite(LED4, LOW);
  }






 
Serial.print("V1: ");
Serial.println(interruptor1);
Serial.print("V2: ");
Serial.println(interruptor2);
Serial.print("V3: ");
Serial.println(interruptor3);
Serial.print("V4: ");
Serial.println(interruptor4);
display.print("V1: ");
display.setCursor(18,0);
display.print(v_1);
display.setCursor(0,8);
display.println("V2: ");
display.setCursor(18,8);
display.println(v_2);
display.setCursor(0,16);
display.println("V3: ");
display.setCursor(18,16);
display.println(v_3);
display.setCursor(0,24);
display.println("V4: ");
display.setCursor(18,24);
display.println(v_4);
display.display();
delay(1000);
display.clearDisplay();

}
