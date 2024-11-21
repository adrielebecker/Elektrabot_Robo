#include <WiFi.h>

const char * ssid = "elektrabot";
const char* password = "elektrabot1416";

IPAddress local_IP(10, 0, 0, 99);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

WiFiServer server(80);

//Eixo X
int motorPinXA = 19; //D19
int motorPinXB = 21; //D21

//Eixo Z
int motorPinZA = 2; //D2
int motorPinZB = 4; //D4

//Parafusadeira
int motorPinPA = 5 ;//D5
int motorPinPB = 18 ; //D18

int posicaoX = 0;
int posicaoZ = 0;
int posicaoP = 0;

void setup() {
  Serial.begin(115200);

  //eixo X
  pinMode(motorPinXA, OUTPUT);
  pinMode(motorPinXB, OUTPUT);
  
  //eixo Z
  pinMode(motorPinZA, OUTPUT);
  pinMode(motorPinZB, OUTPUT);
  
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

void loop() {
  WiFiClient client = server.available();

  if(client){
    Serial.println("Cliente Conectado");
    String request = client.readStringUntil('\n');
    Serial.println(request);
    client.flush();

    if(request.indexOf("DIREITA") != -1){
      moverDireita();
    } 
    
    if(request.indexOf("ESQUERDA") != -1){
      moverEsquerda();
    } 

    if(request.indexOf("FRENTE") != -1){
      moverFrente();
    } 

    if(request.indexOf("TRAS") != -1){
      moverTras();
    }  

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
    client.println("Content-Type: text/html");
    client.println();
    client.println("<!DOCTYPE HTML");
    client.println("<html>Comando recebido</html>");
  }
}

void moverDireita(){
    Serial.print("Movendo para a direita");
    digitalWrite(motorPinXA, HIGH);
    digitalWrite(motorPinXB, LOW);
    delay(110);

    digitalWrite(motorPinXA, LOW);
    digitalWrite(motorPinXB, LOW);

    posicaoX += 1;
  }

  void moverEsquerda(){
    Serial.print("Movendo para a esquerda");
    digitalWrite(motorPinXA, LOW);
    digitalWrite(motorPinXB, HIGH);
    delay(110);

    digitalWrite(motorPinXA, LOW);
    digitalWrite(motorPinXB, LOW);

    posicaoX -= 1;
  }

  void moverFrente(){
    Serial.print("Movendo para a frente");
    digitalWrite(motorPinZA, HIGH);
    digitalWrite(motorPinZB, LOW);
    delay(200);

    digitalWrite(motorPinZA, LOW);
    digitalWrite(motorPinZB, LOW);

    posicaoZ += 1;
  }

  void moverTras(){
    Serial.print("Movendo para a trás");
    digitalWrite(motorPinZA, LOW);
    digitalWrite(motorPinZB, HIGH);
    delay(200);

    digitalWrite(motorPinZA, LOW);
    digitalWrite(motorPinZB, LOW);

    posicaoZ -= 1;
  }

  void parafusar(){ 
    Serial.print("Movendo para a esquerda");
    digitalWrite(motorPinPA, HIGH);
    digitalWrite(motorPinPB, LOW);
    delay(10);

    digitalWrite(motorPinXA, LOW);
    digitalWrite(motorPinXB, LOW);

    posicaoX += 1;
  }

  void desparafusar(){  
   Serial.print("Movendo para a esquerda");
    digitalWrite(motorPinPA, LOW);
    digitalWrite(motorPinPB, HIGH);
    delay(10);

    digitalWrite(motorPinXA, LOW);
    digitalWrite(motorPinXB, LOW);

    posicaoX -= 1;
  }

  void parar(){
    digitalWrite(motorPinPA, LOW);
    digitalWrite(motorPinPB, LOW);
  }