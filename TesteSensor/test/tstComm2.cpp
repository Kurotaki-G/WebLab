#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>


//Based on ReadSerial.cpp
// USING JSON.....

//SEND JSON data to Arduino, 
//RECEIVING JSON data from NODE.JS

//Serial port config
#define pinRX 0
#define pinTX 1

//Arduino ports config
#define LED LED_BUILTIN

// Set up a new SoftwareSerial object
SoftwareSerial mySerial =  SoftwareSerial(pinRX, pinTX);


// Allocate the JSON document for commands
const int commC = JSON_OBJECT_SIZE(3);
StaticJsonDocument<commC> comm;


void setup()  {
    // Define pin modes for TX and RX
    pinMode(pinRX, INPUT);
    pinMode(pinTX, OUTPUT);

    //Define Arduino pins 
    pinMode(LED, OUTPUT);
    
    // Set the baud rate for the SoftwareSerial object
    mySerial.begin(9600);

    Serial.begin(9600); 
}

String textFrom = "";
void received(String text);
void printSerial(String text);
void setValores();
void readComando(String txt);

bool enableLED = false;

void loop() {
    if (mySerial.available() > 0) {
        char c = mySerial.read();
        textFrom += String(c);
        if(c == 10 || c== 11 || c=='}'){
            printSerial(textFrom);
            received(textFrom);
            textFrom = "";
        };
    }

    delay(10);
}


void received(String text){
    if(text.indexOf("GetStatus") > -1){

    }
    else readComando(text);
}

void printSerial(String text){
    Serial.print("I received: ");
    Serial.print(text);
}



void readComando(String comandoText){
  DeserializationError err = deserializeJson(comm, comandoText);

  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    
    Serial.println(err.f_str());
  }
  else setValores();
//   Serial.print("ok!!");
}

void setValores(){
    if(comm["led"].is<bool>()) {
        enableLED = comm["led"].as<bool>();
  }
  digitalWrite(LED, enableLED);
}