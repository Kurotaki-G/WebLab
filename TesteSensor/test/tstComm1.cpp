#include <Arduino.h>
#include <SoftwareSerial.h>

//Based on ReadSerial.cpp
//Still without using JSON.....
// need to write "on" or "off",

//Serial port config
#define pinRX 0
#define pinTX 1

//Arduino ports config
#define LED LED_BUILTIN

// Set up a new SoftwareSerial object
SoftwareSerial mySerial =  SoftwareSerial(pinRX, pinTX);

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

void loop() {
    if (mySerial.available() > 0) {
        char c = mySerial.read();
        if(c == 10 || c== 11 || c=='}'){
            printSerial(textFrom);
            received(textFrom);
            textFrom = "";
        };
        textFrom += String(c);
    }
    delay(10);
}


void received(String text){
    if(text.indexOf("on") > -1) digitalWrite(LED, HIGH);
    else if(text.indexOf("off") > -1) digitalWrite(LED, LOW);
}

void printSerial(String text){
    Serial.print("I received: ");
    Serial.print(text);
}