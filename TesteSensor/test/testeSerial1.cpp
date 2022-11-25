#include <Arduino.h>
#include <SoftwareSerial.h>

//Pin set
#define BUT 2
#define LED LED_BUILTIN
#define POT A0

//Serial port config
#define pinRX 0
#define pinTX 1

SoftwareSerial serialBT(pinRX, pinTX);

void readSerial();
void print(String text);

int incomingByte = 0; // variável para o dado recebido
String comando = "";


void setup() {
  
//PIN SET
  pinMode(BUT, INPUT);
  pinMode(POT, INPUT);
  pinMode(LED, OUTPUT);
  
  Serial.begin(115200);  
  serialBT.begin(115200);  
}

void loop() {
  
  readSerial();
  delay(100);
}


void readSerial(){
  if (serialBT.available() > 0) {
    char c =  serialBT.read();
    comando += c;
    if(c == 10 || c == 11){
      print(comando);
      comando = "";
    }
  }
}

void print(String text){
    Serial.print("I received: ");
    Serial.println(text);
}