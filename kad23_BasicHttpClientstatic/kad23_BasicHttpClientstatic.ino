#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>
//接続先のSSIDとバスワード学内CampusIOI4
const char ssid[] = "CampusIoT-WiFi";
const char passwd[] =  "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;


void setup() {

    USE_SERIAL.begin(115200);
/*
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("SSID", "PASSWORD");
*/
    //WiFi接続シーケンス
    Serial.print("Connecting...");
    WiFi.begin(ssid, passwd);
    while (WiFi.status() != WL_CONNECTED){
      delay(100);
      Serial.print(".");
    }
    Serial.println("connected");
    Serial.println(WiFi.localIP());

}

void loop() {
    // wait for WiFi connection
    if((WiFi.status() == WL_CONNECTED)) {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        // http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        // http.begin("http://example.com/index.html"); //HTTP
        http.begin("http://arduinojson.org/example.json"); //HTTP
         
        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(5000);
}
