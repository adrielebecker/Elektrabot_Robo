#include "Stepper.h" 
#include <WiFi.h>

const char * ssid = "elektrabot";
const char* password = "elektrabot1416";

IPAddress local_IP(10, 0, 0, 99);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

WiFiServer server(80);

// int PassosPorVolta = 200; // Passos para dar uma volta 

//Eixo X
// #define IN1 15 //d15 
// #define IN2 2 //d2
// #define IN3 4 //d4
// #define IN4 16 //rx2  

//Parafusadeira
int motorPinPA = 5 ;//D5
int motorPinPB = 18 ; //D18

int posicaoX = 0;
int posicaoZ = 0;
int posicaoP = 0;

// Stepper myStepper(PassosPorVolta, IN1, IN2, IN3, IN4); 	// Instância motor e pinos de comando
 
void setup() {  
  Serial.begin(115200);

  // myStepper.setSpeed(300); // Configura a velocidade por rpm;

  //parafusadeira
  pinMode(motorPinPA, OUTPUT);
  pinMode(motorPinPB, OUTPUT);

  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop(){
   WiFiClient client = server.available();

  if(client){
    Serial.println("Cliente Conectado");
    String request = client.readStringUntil('\n');
    Serial.println(request);
    client.flush();

    // if(request.indexOf("DIREITA") != -1){
    //   moverDireita();
    // } 
    
    // if(request.indexOf("ESQUERDA") != -1){
    //   moverEsquerda();
    // } 

    if(request.indexOf("PARAFUSAR") != -1){
      parafusar();
    }
    
    if(request.indexOf("DESPARAFUSAR") != -1){
      desparafusar();
    }

    if(request.indexOf("PARAR") != -1){
      parar();
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Access-Control-Allow-Origin: *");
    client.println("Access-Control-Allow-Methods: GET");
    client.println("Access-Control-Allow-Headers: Content-Type");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>Comando recebido</html>");

    // client.println("HTTP/1.1 200 OK");
    // client.println("Access-Control-Allow-Origin: *");
    // client.println("Content-Type: text/html");
    // client.println();
    // client.println("<!DOCTYPE HTML");
    // client.println("<html>Comando recebido</html>");
  }
}

// void moverDireita(){
//     myStepper.step(PassosPorVolta);  
//     delay(1000);
//     posicaoX += 1;
//   }

  // void moverEsquerda(){
  //   myStepper.step(-PassosPorVolta);  
  //   delay(1000);
  //   posicaoX -= 1;
  // }

  void parafusar(){ 
    Serial.print("Movendo para a esquerda");
    digitalWrite(motorPinPA, HIGH);
    digitalWrite(motorPinPB, LOW);
    delay(10);

    posicaoX += 1;
  }

  void desparafusar(){  
   Serial.print("Movendo para a esquerda");
    digitalWrite(motorPinPA, LOW);
    digitalWrite(motorPinPB, HIGH);
    delay(10);

    posicaoX -= 1;
  }

  void parar(){
    digitalWrite(motorPinPA, LOW);
    digitalWrite(motorPinPB, LOW);
  }