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

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 2);
float v0 = 4.98; // valor real de la alimentacion de Arduino, Vcc
float v1 = 18; // valor real de la alimentacion de Arduino, Vcc
float v2 = 10.5; // valor real de la alimentacion de Arduino, Vcc
float v3 = 3; // valor real de la alimentacion de Arduino, Vcc
float r1 = 1000000; // 1M
float r2 = 100000; // 100K
 
void setup() {
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
Serial.print((int)(v1 / (r2 / (r1 + r2))));
Serial.println("V");
Serial.println("--------------------");
Serial.println(""); 
delay(2000);
}
 
void loop() {
float v_00 = (analogRead(0) * v0) / 1024.0;
float v_1 = v_00 / (r2 / (r1 + r2));

float v_11 = (analogRead(1) * v1) / 1024.0;
float v_2 = v_11 / (r2 / (r1 + r2));

float v_22 = (analogRead(2) * v2) / 1024.0;
float v_3 = v_22 / (r2 / (r1 + r2));

float v_33 = (analogRead(3) * v3) / 1024.0;
float v_4 = v_33 / (r2 / (r1 + r2));
 
Serial.print("V: ");
Serial.println(v_2);
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
