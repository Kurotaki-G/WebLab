#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include <WiFiServer.h>

#define PORT 3000

String SSID = "LAPTOP";
String PASSWORD = "12345678";

WiFiServer server(PORT);//Cria o objeto servidor na porta PORT
WiFiClient  client;



bool countEnabled = false;
int count = 0;
bool countSend = false;
long lastCount = millis();
long lastSend = millis();

void startCount() {countEnabled = true;}
void endCount() {countEnabled = false;}
void resetCount() {count = 0;}
void startSend() {countSend = true;}
void endSend() {countSend = false;}

void setup() {
  // put your setup code here, to run once:

// inicializa Serial
  Serial.begin(115200);
  Serial.println();

// inicializa ESP WIFI
  WiFi.begin(SSID, PASSWORD);
  
// Espera por conexão com rede Wifi
  Serial.print("Connecting");
  // while (WiFi.status() != WL_CONNECTED){
  //   delay(500);
  //   Serial.print(".");
  // }

//Confirma a conexão
  Serial.println("Connected");

//Exibe IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


// Inicializa servidor TCP
  server.begin();

  // Serial.println(client.remoteIP());

  Serial.print("Port number: ");
  Serial.println(server.port());

  client = server.available();

}

void TCP();
void handleClient();
void sendToClient();
bool clientIsConnected();
bool clientIsAvailable();


void handleCount();


void loop() {
  // put your main code here, to run repeatedly:
  TCP();
  delay(100);

  handleCount();
}

void TCP(){
// client = server.available();

  if(!clientIsConnected()) return; 

  if(clientIsAvailable()) {
    handleClient();
  }

}

bool clientIsConnected(){
  if(client.connected()){// confere se há algum cliente conectado
  Serial.print("Client connected!!");
  client.println("From ESP: CLIENT CONNECTED!!");
    return true;
  } 
  else{//caso não haja, retorna.
    return false;
  }
}

bool clientIsAvailable(){
  if(client.available() > 0) {// confere se há alguma mensagem do cliente.
    Serial.print("Client available!!");
    return true;
  }
  else{//caso não haja, disponabiliza o servidor para o cliente se conectar.
    Serial.println("CNA");
    client = server.available();
    return false;
  }
}

void sendMessageConfirmation(String msg);
void readMessage(String msg);

void handleClient(){

    //  Leitura da mensagem, char por char
      String msg = "";

      bool lastLine = true;
      while(client.available() > 0 ){
        char c = client.read();
        msg += c;

        if (c == '}' || (c == '\n' && lastLine)) {       
          Serial.println("END MESSAGE!!");

          break;
        }

        if (c == '\n') {
            lastLine = true;
        } 
        else if (c != '\r') {
            lastLine = false;
        }
      }

    sendMessageConfirmation(msg);

    readMessage(msg);

    client.stop();
}

void sendMessageConfirmation(String msg){
  //  Escreve no serial a mensagem
  Serial.println("Nova mensagem: "); 

  Serial.print("IP do Cliente: ");
  Serial.println(client.remoteIP());

  Serial.print("IP do Servidor: ");
  Serial.println(WiFi.localIP());

  Serial.print("Mensagem: ");
  Serial.println(msg);

  client.print("From ESP : Message Received!!: ");
  client.print(msg);


}


void handleCount(){
  if(countEnabled){
    if(millis()- lastCount > 1000){
      count++;
      lastCount = millis();
    }
  }
  if(countSend){
    if(millis()- lastSend > 1000){
      sendToClient();
      lastSend = millis();
    }
  }
}

void sendToClient(){

  Serial.print("{ time: ");
  Serial.print(count);
  Serial.print("}");

  client.print("{ time: ");
  client.print(count);
  client.print("}");

}