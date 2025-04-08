#include <WiFi.h>
#include "libwifi.h"

void conectarWifi(const char * ssid, const char * password)
{
  WiFi.begin(ssid, password);
  Serial.print("Estableciendo conexion WiFi..");
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\r\nConexion Establecida");
  Serial.println("\nNumero IP asignado");
  Serial.println(WiFi.localIP()); // Imprime el numero IP
}