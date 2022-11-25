#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>


///Comunicação serial do ESP com PC n ta funcionando.....


//Based on tstComm2.cpp
// USING JSON.....

//SEND JSON data to Arduino, 
//RECEIVING JSON data from NODE.JS

//SEND AND RECEIVE data between Arduino and NODE.JS 
//Send Commands to Arduino
//Receive status from arduino and send it to Client

//Serial port config
// #define pinRX 4
// #define pinTX 8
#define pinRX 7
#define pinTX 2

//Arduino Output ports config
#define LED LED_BUILTIN


// Set up a new SoftwareSerial object
SoftwareSerial mySerial =  SoftwareSerial(pinRX, pinTX);


// Allocate the JSON document for commands
const int commC = JSON_OBJECT_SIZE(5);
StaticJsonDocument<commC> comm;


// Allocate the JSON document
const int sttC = JSON_OBJECT_SIZE(5);
StaticJsonDocument<sttC> stt;


void setup()  {
    // Define pin modes for TX and RX
    // pinMode(pinRX, INPUT);
    // pinMode(pinTX, OUTPUT);

    // Set the baud rate for the SoftwareSerial object
    mySerial.begin(9600);

    Serial.begin(9600); 
}

String textFrom = "";
void received(String text);
void printSerial(String text);
void setValores();
void readComando(String txt);

void statusToJson();
void statusJsonToServer();

void detectChange();

bool enableLED = false;
bool blink = false;
bool LEDstatus = false;

double speed = 1000;

unsigned long lastMillis = millis();

void loop() {
    // if (mySerial.available() > 0) {
    //     char c = mySerial.read();
    //     textFrom += String(c);
    //     Serial.print(c);
    //     if(c == 10 || c== 11 || c=='}'){
    //         printSerial(textFrom);
    //         // received(textFrom);
    //         textFrom = "";
    //     };
    // }

    // if(millis() - lastMillis > 1000 ) {
    //     if (mySerial.available() > 0) Serial.print("A");
    //     else Serial.print(".");
    //     lastMillis = millis();

    // }

if (mySerial.available() > 0) Serial.print("A");
        else Serial.print(".");


}


void received(String text){
    if(text.indexOf("getStatus") > -1){
        statusToJson();
        statusJsonToServer();
    }
    else readComando(text);
}

void printSerial(String text){
    Serial.print("ESP - received from Server: ");
    Serial.print(text);
}



// void readComando(String comandoText){
//   DeserializationError err = deserializeJson(comm, comandoText);

//   if (err) {
//     Serial.print(F("deserializeJson() failed with code "));
    
//     Serial.println(err.f_str());
//   }
//   else setValores();
// //   Serial.print("ok!!");
// }

// void setValores(){
//     if(comm["led"].is<bool>()) {
//         enableLED = comm["led"].as<bool>();
//   }
//   if(comm["blink"].is<bool>()) {
//         blink = comm["blink"].as<bool>();
//   }
//   if(comm["speed"].is<double>()) {
//         speed = comm["speed"].as<double>();
//   }
// }



void statusToJson(){
  //Read values from pins

  // Add values in the document
    stt["led"] = enableLED;
    stt["blink"] = blink;
    stt["speed"] = speed;
   
}


void statusJsonToServer(){
    String txt;
  serializeJson(stt, txt);
  Serial.println(txt);
}