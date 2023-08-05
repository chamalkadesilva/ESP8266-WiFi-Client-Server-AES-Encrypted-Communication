#include <AESLib.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "SSIDNAME";
const char* password = "PASSWORD";

ESP8266WebServer server(80); //Server on port 80

AESLib aesLib;

uint8_t key[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; // 128 bit key
uint8_t iv[N_BLOCK] = {0};  // initialization vector
uint8_t decryptedData[32]; // Stores the decrypted data

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/api", HTTP_POST, []() {
    if(server.hasArg("data")) {
      String encryptedString = server.arg("data");
      int index = 0;
      int pos = 0, prevPos = 0;
      while((pos = encryptedString.indexOf(',', prevPos)) != -1) {
        decryptedData[index++] = (uint8_t)encryptedString.substring(prevPos, pos).toInt();
        prevPos = pos + 1;
      }
      decryptedData[index++] = (uint8_t)encryptedString.substring(prevPos).toInt(); // last byte
      int decryptedLength = aesLib.decrypt(decryptedData, index, decryptedData, key, sizeof(key), iv);
      decryptedData[decryptedLength] = '\0'; // Add null character at the end of the string
      Serial.println((char*)decryptedData);
      server.send(200, "text/plain", "Data received");
    } else {
      server.send(400, "text/plain", "No data received");
    }
  });
  
  server.begin();
}

void loop() {
  server.handleClient();
}
