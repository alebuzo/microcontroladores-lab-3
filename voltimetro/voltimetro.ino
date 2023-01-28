//
// Voltimetro_dc.ino
// hispavila.com
// Construcción de un voltímetro DC con Arduino
// 20.09.2015
// Utiliza el monitor Serial para mostrar los valores.
//
 
float v1 = 4.98; // valor real de la alimentacion de Arduino, Vcc
float r1 = 1000000; // 1M
float r2 = 100000; // 100K
 
void setup() {
Serial.begin(9600);
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
delay(10);
}
