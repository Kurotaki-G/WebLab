#include <Arduino.h>
#include <ESP8266WiFi.h> 

String SSID = "1";
String PASSWORD = "abcd1234";

void setup() {
  // put your setup code here, to run once:

// inicializa Serial
  Serial.begin(115200);
  Serial.println();

// inicializa ESP WIFI
  WiFi.begin(SSID, PASSWORD);
  
// Espera por conexão com rede Wifi
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();


  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
}