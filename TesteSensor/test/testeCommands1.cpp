#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

//Arduino Ports config
#define BUT 2
#define LED 8
#define POT A0

//Serial port config
#define pinRX 0
#define pinTX 1

//TEST sending to Serial port in JSON format
//TEST receiving JSON data from serial

// Allocate the JSON document
const int commV = JSON_OBJECT_SIZE(2);
StaticJsonDocument<commV> doc;

const int commC = JSON_OBJECT_SIZE(2);
StaticJsonDocument<commC> comm;

SoftwareSerial serialBT(pinRX, pinTX);
String comando="";

void setup() {
  
//PIN SET
  pinMode(BUT, INPUT);
  pinMode(POT, INPUT);
  pinMode(LED, OUTPUT);
  
  Serial.begin(115200);
  serialBT.begin(115200);

Serial.print("OKAY!!");
}

bool valorBUT;
int valorPOT;
double calcPOT;
double valorVEL;
bool valorLED;
bool enabledLED;


void getValores();
void setValores();
void printValores();

void readSerial();
void readComando(String textComando);

void blink();

unsigned long millis1 = millis();


void loop() {

  readSerial();

  
blink();

  if(millis()-millis1 > 10+valorVEL*10){    
    
    // setValores();
    
    // blink();

    millis1 = millis();
  }
}

void blink(){
  // if(enabledLED) digitalWrite(LED, valorLED);
  // else digitalWrite(LED, LOW);
  // valorLED = !valorLED;
  if(enabledLED) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
}


void getValores(){
  
  //Read values from pins
  valorBUT = digitalRead(BUT);
  valorPOT = analogRead(POT);
  calcPOT = ((double)valorPOT)*100/1023;

  // Add values in the document
  doc["pot"] = valorPOT;
  doc["vel"] = valorVEL;
  doc["but"] = valorBUT;
  doc["led"] = valorLED;

  printValores();
}

void readSerial(){
  if (serialBT.available() > 0) {
    char c =  serialBT.read();
    comando += c;
    if(c == 10 || c == 11 || c=='}'){
      readComando(comando);
      comando = "";
    }
  }
}

void readComando(String comandoText){
  DeserializationError err = deserializeJson(comm, comandoText);

  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    
    Serial.println(err.f_str());
  }
  else setValores();
  Serial.print("ok!!");
}

void setValores(){
  if(comm["led"].is<bool>()) {
    enabledLED = comm["led"].as<bool>();
    Serial.print(comm["led"].as<String>());
    Serial.print("ok!!");
  }
  else{Serial.print("N BOOL!!");

  }
  // enabledLED = comm["led"];
  if(comm["vel"].is<double>()) valorVEL = comm["vel"].as<double>();
}

void printValores(){
  serializeJson(doc, Serial);
  Serial.println();
}