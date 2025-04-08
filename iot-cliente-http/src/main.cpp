#include <Arduino.h>
#include "libwifi.h"
#include <WiFi.h>
#include "Adafruit_SHT31.h"

#define LED 2

const char * ssid = "MIRED";
const char * password = "a1b2c3d4";
const char * host = "codelab.denkitronik.com";
const int port = 8080;
int temperatura;
int humedad;
Adafruit_SHT31 sht31 = Adafruit_SHT31();//creamos un objeto de la clase Adafruit_SHT31


void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Iniciando cliente HTTP ");
  conectarWifi(ssid, password);
  if (!sht31.begin(0x44)) {  // Dirección I2C del sensor (0x44 o 0x45)
    Serial.println("¡Error! No se encontró el SHT31");
    while (1); // Detener ejecución
  }
}

void loop() {
  temperatura = sht31.readTemperature();
  humedad = sht31.readHumidity();
  Serial.println("Enviando datos a FreeBoard...");
  WiFiClient cliente;

  if(!cliente.connect(host, port)){
    delay(2000);
    return;
  }

  //thingname/steven01?presion=1000&altitud=120&temperatura=45
  cliente.println("GET /thingname/steven02?temperatura=" + String(temperatura) + "&humedad=" + String(humedad) + " HTTP/1.1\r\nHost: " + String(host) + "\r\nConnection: close\r\n\r\n");

  // Agregamos un tiempo de espera para recibir los primeros caracteres del servidor
  unsigned long tiempo = millis();
  while(cliente.available() == 0){
    if(millis()-tiempo > 5000){
      Serial.println("Se agoto el tiempo de espera");
      cliente.stop();
    }
  }
  while(cliente.available()){
    String linea = cliente.readStringUntil('\r');
    Serial.println(linea);
  }

  Serial.println("Finalizando Conexion");
  cliente.stop();
  delay(3000);
}