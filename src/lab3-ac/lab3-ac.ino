//     Universidad de Costa Rica
// Laboratorio de Microcontroladores
// Laboratorio 3 - Voltimetro 4 canales 
// Estudiantes;  Raquel Corrales Marín B92378
//               Alexa Carmona Buzo B91643        
// Febrero 2022.

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
int serialPin = A0;
int buttonState = 0;

void setup() {
pinMode(serialPin, INPUT);
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
display.clearDisplay();


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

  //--------------------------------------------------------------------
  // Calculos e impresion en pantalla
  //--------------------------------------------------------------------
  int interruptor1 = digitalRead(10);   //lee el estado del botón
  int interruptor2 = digitalRead(11);   //lee el estado del botón
  int interruptor3 = digitalRead(12);   //lee el estado del botón
  int interruptor4 = digitalRead(13);   //lee el estado del botón

  if(interruptor1==HIGH) {          //si el estado es pulsado

    float v_00 = max_v1*0.00488*(1+r1/r2);
     v_1 = v_00 *0.7071+0.7; 
    
    display.print("V1 AC: ");
    display.print(v_1);
    display.print("V");
  }
  else{                                   //si el estado es no pulsado

     float v = analogRead(5) *0.00488;
      v_1 = v*9.6-24;
      display.print("V1 DC: ");
      display.print(v_1);
      display.print("V");   
  }

  if(interruptor2==HIGH) {          //si el estado es pulsado
    
     float v_00 = max_v2*0.00488*(1+r1/r2);
     v_2 = v_00 *0.7071+0.7;  
    display.print("\n");
    display.print("V2 AC: ");
    display.print(v_2);
    display.print("V");
  }
  else{                                   //si el estado es no pulsado
      float v = analogRead(4) *0.00488;
      v_2 = v*9.6 -24;
      display.print("\n");
      display.print("V2 DC: ");
      display.print(v_2);
      display.print("V");
  }


  if(interruptor3==HIGH) {          //si el estado es pulsado

     float v_00 = max_v3*0.00488*(1+r1/r2);
     v_3 = v_00 *0.7071+0.7;  
    display.print("\n");
    display.print("V3 AC: ");
    display.print(v_3);
    display.print("V");
  }
  else{                                   //si el estado es no pulsado
    float v = analogRead(3) *0.00488;
      v_3 = v *9.6 -24;
      display.print("\n");
      display.print("V3 DC: ");
      display.print(v_3);
      display.print("V"); 
  }


  if(interruptor4==HIGH) {          //si el estado es pulsado

    float v_00 = max_v4*0.00488*(1+r1/r2);
      v_4 = v_00 *0.7071+0.7; 
      display.print("\n");
      display.print("V4 AC: ");
      display.print(v_4);
      display.print("V");
  }

  else{                                   //si el estado es no pulsado
    float v = analogRead(2) *0.00488;
      v_4 = v *9.6-24;     
    display.print("\n");
    display.print("V4 DC: ");
    display.print(v_4);
    display.print("V");
  }


//--------------------------------------------------------------------
// IMPRIMIR EN PANTALLA Y DATOS SERIALES AC/DC
  //--------------------------------------------------------------------
buttonState = digitalRead(serialPin);

  if(buttonState==HIGH) {          //si el estado es pulsado

    if(interruptor1==HIGH) {          //si el estado es pulsado

      Serial.print("V1_AC: ");
      Serial.println(v_1);

    }

    else{                                   //si el estado es no pulsado
          Serial.print("V1_DC: ");
          Serial.println(v_1);    
    }
    
    if(interruptor2==HIGH) {          //si el estado es pulsado

      Serial.print("V2_AC: ");
      Serial.println(v_2);

    }

    else{                                   //si el estado es no pulsado
          Serial.print("V2_DC: ");
          Serial.println(v_2);    
    }

    if(interruptor3==HIGH) {          //si el estado es pulsado

      Serial.print("V3_AC: ");
      Serial.println(v_3);

    }

    else{                                   //si el estado es no pulsado
          Serial.print("V3_DC: ");
          Serial.println(v_3);    
    }  
    if(interruptor4==HIGH) {          //si el estado es pulsado

      Serial.print("V4_AC: ");
      Serial.println(v_4);

    }

    else{                                   //si el estado es no pulsado
          Serial.print("V4_DC: ");
          Serial.println(v_4);    
    }

  }

  else{                                   //si el estado es no pulsado

      Serial.print("La trasmision de datos seriales esta deshabilitada.");   

  }
delay(500);
display.display();
display.clearDisplay();

}
