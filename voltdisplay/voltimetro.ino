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
float v1 = 4.98; // valor real de la alimentacion de Arduino, Vcc
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
float v = (analogRead(0) * v1) / 1024.0;
float v2 = v / (r2 / (r1 + r2));
 
Serial.print("V: ");
Serial.println(v2);
display.print("V1: ");
display.setCursor(18,0);
display.print(v2);
display.setCursor(0,8);
display.println("V2: ");
display.setCursor(18,8);
display.println(v2);
display.setCursor(0,16);
display.println("V3: ");
display.setCursor(18,16);
display.println(v2);
display.setCursor(0,24);
display.println("V4: ");
display.setCursor(18,24);
display.println(v2);
display.display();
delay(1000);
display.clearDisplay();
delay(1000);
}
