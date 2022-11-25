#include <Arduino.h>
#include <ArduinoJson.h>

#define BUT 2
#define LED LED_BUILTIN
#define POT A0

//TEST sending to Serial port in JSON format

// Allocate the JSON document
const int capacity = JSON_OBJECT_SIZE(2);
StaticJsonDocument<capacity> doc;

void setup() {
  
//PIN SET
  pinMode(BUT, INPUT);
  pinMode(POT, INPUT);
  pinMode(LED, OUTPUT);
  
  Serial.begin(115200);
}

bool valorBUT;
int valorPOT;
double calcPOT;
bool valorLED;

void getValores();
void printValores();

unsigned long millis1 = millis();


void loop() {
  if(millis()-millis1 > 10+calcPOT*10){
    getValores();
    printValores();

    valorLED = !valorLED;  
    digitalWrite(LED,valorLED);

    millis1 = millis();
  }
}

void getValores(){
  //Read values from pins
  valorBUT = digitalRead(BUT);
  valorPOT = analogRead(POT);
  calcPOT = ((double)valorPOT)*100/1023;

  // Add values in the document
  doc["pot"] = calcPOT;
  doc["but"] = valorBUT;
}

void printValores(){
  serializeJson(doc, Serial);
  Serial.println();
}