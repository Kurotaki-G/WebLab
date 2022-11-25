#include <Arduino.h>
#include <SoftwareSerial.h>

//Serial port config
#define pinRX 0
#define pinTX 1

// Set up a new SoftwareSerial object
SoftwareSerial mySerial =  SoftwareSerial(pinRX, pinTX);

void setup()  {
    // Define pin modes for TX and RX
    pinMode(pinRX, INPUT);
    pinMode(pinTX, OUTPUT);
    
    // Set the baud rate for the SoftwareSerial object
    mySerial.begin(9600);

    Serial.begin(9600); 
}

String textFrom = "";

void loop() {
    if (mySerial.available() > 0) {
        char c = mySerial.read();
        textFrom += String(c);
        if(c == 10 || c== 11 || c=='}'){
            Serial.print("I received: ");
            Serial.print(textFrom);
            textFrom = "";
        };
    }
    delay(10);
}