#include <ESP8266WiFi.h>

 
const char* ssid = "Nome da rede";

const char* password = "senha";


IPAddress ip(192, 168, 1, 56);//ip navegador

IPAddress gateway(192, 168, 1, 1);//ip do roteador

IPAddress subnet(255, 255, 255, 0);//mascara

WiFiServer server(80);//incio na porta 80


const int pin = 0; 
const int pin2 = 16; 

void setup() {


  Serial.begin(74880);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);

  pinMode(pin2, OUTPUT);
  digitalWrite(pin2, HIGH);

  
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

Serial.println("Conectou");
Serial.println(WiFi.localIP());

  server.begin();

}
 void reconectar() {
  Serial.println("Reconect");
      if(WiFi.status() != WL_CONNECTED){
      Serial.println(" no IFFF do reconetar");
      WiFi.config(ip, gateway, subnet);
      WiFi.begin(ssid, password);
     }
  }
void loop() {
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("IF do Loop");
      WiFi.config(ip, gateway, subnet);
      WiFi.begin(ssid, password);
     }
  
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  
  
  client.flush();

  String buf = "";

  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  buf += "<head> ";
  buf += "<meta charset='UTF-8'> ";
  buf += "<meta http-equiv='cache-control' content='max-age=0' /> ";
  buf += "<meta http-equiv='cache-control' content='no-cache' /> ";
  buf += "<meta http-equiv='expires' content='0' /> ";
  buf += "<meta http-equiv='pragma' content='no-cache' /> ";
  buf += "<title>Automa&ccedil;&atilde;o Residencial</title> ";
  buf += "<style> ";
  buf += "body{font-family:Open Sans; color:#555555;} ";
  buf += "h1{font-size:24px; font-weight:normal; margin:0.4em 0;} ";
  buf += ".container { width: 100%; margin: 0 auto; } ";
  buf += ".container .row { float: left; clear: both; width: 100%; } ";
  buf += ".container .col { float: left; margin: 0 0 1.2em; padding-right: 1.2em; padding-left: 1.2em; } ";
  buf += ".container .col.four, .container .col.twelve { width: 100%; } ";
  buf += "@media screen and (min-width: 767px) { ";
  buf += ".container{width: 100%; max-width: 1080px; margin: 0 auto;} ";
  buf += ".container .row{width:100%; float:left; clear:both;} ";
  buf += ".container .col{float: left; margin: 0 0 1em; padding-right: .5em; padding-left: .5em;} ";
  buf += ".container .col.four { width: 50%; } ";
  buf += ".container .col.tweleve { width: 100%; } ";
  buf += "} ";
  buf += "* {-moz-box-sizing: border-box; -webkit-box-sizing: border-box; box-sizing: border-box;} ";
  buf += "a{text-decoration:none;} ";
  buf += ".btn {font-size: 18px; white-space:nowrap; width:100%; padding:.8em 1.5em; font-family: Open Sans, Helvetica,Arial,sans-serif; ";
  buf += "line-height:18px; display: inline-block;zoom: 1; color: #fff; text-align: center; position:relative; ";
  buf += "-webkit-transition: border .25s linear, color .25s linear, background-color .25s linear; ";
  buf += "transition: border .25s linear, color .25s linear, background-color .25s linear;} ";
  buf += ".btn.btn-sea{background-color: #08bc9a; border-color: #08bc9a; -webkit-box-shadow: 0 3px 0 #088d74; box-shadow: 0 3px 0 #088d74;} ";
  buf += ".btn.btn-sea:hover{background-color:#01a183;} ";
  buf += ".btn.btn-sea:active{ top: 3px; outline: none; -webkit-box-shadow: none; box-shadow: none;} ";
  buf += "</style> ";
  buf += "</head> ";
  buf += "<body> ";
  buf += "<div class='container'> ";
  buf += "<div class='row'> ";
  buf += "<div class='col twelve'> ";
  buf += "<p align='center'><font size='10'>Quarto</font></p> ";
  buf += "</div> ";
  buf += "</div> ";
  buf += "<div class='row'> ";
  buf += "<div class='col four'> ";
  buf += "<a href='?f=on' class='btn btn-sea'>Ligar</a> ";
  buf += "</div> ";
  buf += "<div class='col four'> ";
  buf += "<a href='?f=off' class='btn btn-sea'>Desligar</a> ";
  buf += "</div> ";
  buf += "</div> ";
  buf += "<div class='col twelve'> ";
  buf += "</div> ";
  buf += "<div class='row'> ";
  buf += "<div class='col twelve'> ";
  buf += "<p align='center'><font size='10'>Cozinha</font></p> ";
  buf += "</div> ";
  buf += "</div> ";
  buf += "<div class='row'> ";
  buf += "<div class='col four'> ";
  buf += "<a href='?f=lig' class='btn btn-sea'>Ligar</a> ";
  buf += "</div> ";
  buf += "<div class='col four'> ";
  buf += "<a href='?f=del' class='btn btn-sea'>Desligar</a> ";
  buf += "</div> ";
  buf += "</div> ";
  buf += "<div class='col twelve'> ";
  buf += "</div> ";
  buf += "</div> ";
  buf += "</body> ";
  buf += "</html> ";

  
  client.print(buf);
  client.flush();

  if (req.indexOf("on") != -1)
  {
    digitalWrite(pin, LOW);
  }
   if (req.indexOf("off") != -1)
  {
    digitalWrite(pin, HIGH);
  }
   if (req.indexOf("lig") != -1)
  {
    digitalWrite(pin2, LOW);
  }
   if (req.indexOf("del") != -1)
  {
    digitalWrite(pin2, HIGH);
  }
  else
  {
    
    client.stop();
  }
  reconectar();
}

  
