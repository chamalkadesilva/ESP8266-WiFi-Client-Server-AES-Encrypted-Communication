#include <AESLib.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "SSIDNAME";
const char* password = "PASSWORD";
const char* serverName = "http://server_address/api"; //replace with your server address

AESLib aesLib;

uint8_t key[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; // 128 bit key
uint8_t iv[N_BLOCK] = {0};  // initialization vector
char data[] = "MESSAGE";
uint8_t encryptedData[32]; // Stores the encrypted data

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  aesLib.gen_iv(iv);
}

void loop() {
  int encryptedLength = aesLib.encrypt((uint8_t*)data, sizeof(data), encryptedData, key, sizeof(key), iv);
  String encryptedString = "";
  for (int i = 0; i < encryptedLength; i++) {
    encryptedString += String(encryptedData[i]);
    if(i < encryptedLength - 1) {
      encryptedString += ",";  // add comma as separator
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST("data=" + encryptedString);
    http.end();
  }
  delay(5000);
}
