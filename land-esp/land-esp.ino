#include <WiFi.h>
#include <HTTPClient.h>

#include <Wire.h>

//network credentials
const char* ssid     = "[WLAN_SSID]";
const char* password = "[WLAN_PASSWORD]";

//Domain name and URL path or IP address with path
const char* serverName = "[IP]/land-esp-write-db";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";

void setup() {
  Serial.begin(9600);
  
  // Connect to WiFi Network
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    //content-type header specification
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue 
      + "&latitude=-15.449553"
      + "&longitude=79.675276"
      + "&ph=5.71"
      + "&temp=34.5";
      
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(30000);  
}