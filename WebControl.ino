#include <WiFi.h>
#include <WebServer.h>

#define ledPin 13

const char* ssid = "";
const char* password = "";

WebServer server(80);

void handleRoot() {
  String html = "<h1>Controle LED</h1>";
  html += "<a href='/on'>Ligar</a><br>";
  html += "<a href='/off'>Desligar</a><br>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", "LED Ligado <br><a href='/'>Voltar</a>");
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", "LED Desligado <br><a href='/'>Voltar</a>");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando...");
  }

  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
}

void loop() {
  server.handleClient();
}
