#include <WiFi.h>


const char* ssid = "****";
const char* password = "***";


WiFiServer server(80);


const int ledPin = 2;  

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  

  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  
  server.begin();
}

void loop() {
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("New Client Connected!");
  String request = client.readStringUntil('\r');  
  Serial.println(request);
  client.flush();

  
  if (request.indexOf("/on") != -1) {
    digitalWrite(ledPin, HIGH);
  }
  if (request.indexOf("/off") != -1) {
    digitalWrite(ledPin, LOW);
  }

  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  
  client.println("<!DOCTYPE html>");
  client.println("<html><head><title>ESP32 LED Control</title></head>");
  client.println("<body><h2>ESP32 LED Control</h2>");
  
  client.println("<p><a href=\"/on\"><button>Turn ON</button></a></p>");
  client.println("<p><a href=\"/off\"><button>Turn OFF</button></a></p>");
  
  client.println("</body></html>");
  client.println();
  client.stop();  
}
