//     Universidad de Costa Rica
// Laboratorio de Microcontroladores
// Laboratorio 3 - Voltímetro 4 canales
// Estudiantes;  Raquel Corrales Marín B92378
//               Alexa Carmona Buzo B91643        
// Febrero 2022.

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 2);
float v0 = 4.98; // valor real de la alimentacion de Arduino, Vcc
float r1 = 1000000; // 1M
float r2 = 100000; // 100K
int LED = 8; 
 
void setup() {
pinMode(LED, OUTPUT);
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
uint16_t max_v = 0;
  for(uint8_t i = 0; i < 100; i++) {
    uint16_t r = analogRead(3);  // read from analog channel 3 (A3)
    if(max_v < r) max_v = r;
    delayMicroseconds(200);
  }



// A3 * 5
float v_00 = (analogRead(3) * v0) / 1024.0;
float v_1 = v_00 / (r2 / (r1 + r2));

// A2 * 18
float v_11 = (analogRead(2) * v0) / 1024.0;
float v_2 = v_11 / (r2 / (r1 + r2));
// A1 * 10.5
float v_22 = (analogRead(1) * v0) / 1024.0;
float v_3 = v_22 / (r2 / (r1 + r2));
// A0 * 3
float v_33 = (analogRead(0) * v0) / 1024.0;
float v_4 = v_33 / (r2 / (r1 + r2));


// Encender LED LÍMITE DE TENSIÓN
if (v_1 < 20 &&  v_2 < 20  &&  v_3 < 20 && v_4 < 20)   
  {  
    digitalWrite(LED, LOW);  
    delay(500);  
  }  
    
  else   
  {  
    digitalWrite(LED, HIGH);  
    delay(500);  
  }  
 
Serial.print("V1: ");
Serial.println(v_1);
Serial.print("V2: ");
Serial.println(v_2);
Serial.print("V3: ");
Serial.println(v_3);
Serial.print("V4: ");
Serial.println(v_4);
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
delay(1000);
}
