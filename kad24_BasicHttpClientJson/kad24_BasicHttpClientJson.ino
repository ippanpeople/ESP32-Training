#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>
//接続先のSSIDとバスワード学内CampusIOI4
const char ssid[] = "CampusIoT-WiFi";
const char passwd[] = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

#include <HTTPClient.h>
#include <ArduinoJson.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

void setup()
{
    // Initialize serial port
    Serial.begin(115200);
    while (!Serial)
        continue;

    // Allocate the JSON document
    //
    // Inside the brackets, 200 is the capacity of the memory pool in bytes.
    // Don't forget to change this value to match your JSON document.
    // Use https://arduinojson.org/v6/assistant to compute the capacity.
    // StaticJsonDocument<200> doc;

    // StaticJsonDocument<N> allocates memory on the stack, it can be
    // replaced by DynamicJsonDocument which allocates in the heap.
    //
    // DynamicJsonDocument doc(200);

    // JSON input string.
    //
    // Using a char[], as shown here, enables the "zero-copy" mode. This mode uses
    // the minimal amount of memory because the JsonDocument stores pointers to
    // the input buffer.
    // If you use another type of input, ArduinoJson must copy the strings from
    // the input to the JsonDocument, so you need to increase the capacity of the
    // JsonDocument.
    // char json[] =
    //     "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

    // Deserialize the JSON document
    // DeserializationError error = deserializeJson(doc, json);

    // Test if parsing succeeds.
    // if (error)
    // {
    //     Serial.print(F("deserializeJson() failed: "));
    //     Serial.println(error.f_str());
    //     return;
    // }

    // Fetch values.
    //
    // Most of the time, you can rely on the implicit casts.
    // In other case, you can do doc["time"].as<long>();
    // const char *sensor = doc["sensor"];
    // long time = doc["time"];
    // double latitude = doc["data"][0];
    // double longitude = doc["data"][1];

    // WiFi接続シーケンス
    Serial.print("Connecting...");
    WiFi.begin(ssid, passwd);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println("connected");
    Serial.println(WiFi.localIP());

    // Print values.
    // Serial.println(sensor);
    // Serial.println(time);
    // Serial.println(latitude, 6);
    // Serial.println(longitude, 6);
}

void loop()
{
    // not used in this example
    // wait for WiFi connection
    if ((WiFi.status() == WL_CONNECTED))
    {

        HTTPClient http;
        StaticJsonDocument<200> doc;
        char json[] =
            "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

        DeserializationError error = deserializeJson(doc, json);
        
        const char *sensor = doc["sensor"];
        long time = doc["time"];
        double latitude = doc["data"][0];
        double longitude = doc["data"][1];

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        // http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        // http.begin("http://example.com/index.html"); //HTTP
        http.begin("http://arduinojson.org/example.json"); // HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0)
        {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK)
            {
                String payload = http.getString();
                Serial.println(payload);
            }
        }
        else
        {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        Serial.println(sensor);
        Serial.println(time);
        Serial.println(latitude, 6);
        Serial.println(longitude, 6);

        http.end();
    }

    delay(5000);
}

// See also
// --------
//
// https://arduinojson.org/ contains the documentation for all the functions
// used above. It also includes an FAQ that will help you solve any
// deserialization problem.
//
// The book "Mastering ArduinoJson" contains a tutorial on deserialization.
// It begins with a simple example, like the one above, and then adds more
// features like deserializing directly from a file or an HTTP request.
// Learn more at https://arduinojson.org/book/
// Use the coupon code TWENTY for a 20% discount ❤❤❤❤❤