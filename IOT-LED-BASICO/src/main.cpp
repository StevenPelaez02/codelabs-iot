#include <Arduino.h>

#define LED 2

/*
* Funcion que se ejecuta una vez al inicio del programa
*/
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT); // Configuramos el pin numero 2 como salida
  digitalWrite(LED, LOW);
}

/*
* Esta funcion es similar al main de C
* Con la excepcion de que es un loop es un bucle infinito
*/
void loop() {
  Serial.println("Hola Mundo!");
  delay(3000); // Retardo bloqueante
  digitalWrite(LED, HIGH);
  delay(3000);
  digitalWrite(LED, LOW);
}

