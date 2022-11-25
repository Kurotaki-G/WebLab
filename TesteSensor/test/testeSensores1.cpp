#include <Arduino.h>

#define BUT 2
#define LED LED_BUILTIN
#define POT A0

//TEST sending to Serial port in text

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

void loop() {
 
  getValores();
  
  printValores();

  valorLED = !valorLED;  
  digitalWrite(LED,valorLED);
  
  delay(10*calcPOT+10);
  
}

void getValores(){
  valorBUT = digitalRead(BUT);
  valorPOT = analogRead(POT);
  
  
  calcPOT = ((double)valorPOT)*100/1023;
}

void printValores(){
  Serial.print("BUT: ");
  Serial.print(valorBUT);
  Serial.print(" POT: ");
  Serial.print(calcPOT);
  Serial.println();
}