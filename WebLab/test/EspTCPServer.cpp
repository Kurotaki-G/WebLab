#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include <WiFiServer.h>

#define PORT 80

String SSID = "LAPTOP";
String PASSWORD = "12345678";

WiFiServer server(PORT);//Cria o objeto servidor na porta PORT
// WiFiClient client;

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


}

void TCP();

void loop() {
  // put your main code here, to run repeatedly:
  TCP();
  delay(100);
}

WiFiClient  client;


void handleClient();


void TCP(){


  client = server.available();



  if(!client.connected()) return; // confere se há algum cliente conectado

  Serial.print("Client connected!!");

  client.println("From ESP: CLIENT CONNECTED!!");

  // while (client.connected()) {

    if(!(client.available() > 0)){// confere se há alguma mensagem do cliente.
      Serial.print(".");
      client = server.available();//caso não haja, disponabiliza o servidor para o cliente se conectar.
    } 

    else{
      Serial.print("Client available!!");
      handleClient();
    }
  // }
}


void handleClient(){

    //  Leitura da mensagem, char por char
      String msg = "";

      bool lastLine = true;
      while(client.available() > 0 ){
        char c = client.read();
        msg += c;

        // if (c == 'A' || (c == '\n' && lastLine)) {       
        // if ((c == '\n' && lastLine)) {       
        //   Serial.print("END MESSAGE!!");

        //   break;
        // }

        if (c == '\n') {
            lastLine = true;
        } 
        else if (c != '\r') {
            lastLine = false;
        }
      }

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

      client.stop();
}