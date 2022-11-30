#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> //JasonParserExampleからコピー

// 接続先のSSIDとパスワード 学内CampusIOT
const char ssid[] = "CampusIoT-WiFi";
const char passwd[] = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

const int pwmPin1 = 16;
const int pwmPin2 = 4;

void setup()
{
    Serial.begin(115200);
    pinMode(16, OUTPUT); //灯
    pinMode(4, OUTPUT); //灯

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
}

void loop()
{
    // wait for WiFi connection
    //書き換え
    //  if ((wifiMulti.run() == WL_CONNECTED)) {
    if ((WiFi.status() == WL_CONNECTED))
    {
        HTTPClient http;
        Serial.print("[HTTP] begin...\n");
        // configure traged server and url

        String api_key = "067ee38f902d8e46f6992266944c6ad3";
        String base_url = "http://api.openweathermap.org/data/2.5/weather";
        String url = base_url + "?zip=530-0015,JP&units=metric&APPID=" + api_key;
        //        String url = base_url + "?q=Osaka,jp&units=metric&APPID="+ api_key;

        Serial.println(url);
        http.begin(url); // HTTP
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
                // Serial.println(payload);
                // JasonParserExampleからコピー
                StaticJsonDocument<2000> doc;
                // Deserialize the JSON document
                DeserializationError error = deserializeJson(doc, payload);
                // Test if parsing succeeds.
                if (error)
                {
                    Serial.print(F("deserializeJson() failed: "));
                    Serial.println(error.c_str());
                    return;
                }
                // Get the root object in the document
                JsonObject root = doc.as<JsonObject>();

                // Fetch values.
                // Most of the time, you can rely on the implicit casts.
                // In other case, you can do root["time"].as<long>();
                const char *cityName = root["name"];
                const char *icon = root["weather"][0]["icon"];
                float temp = root["main"]["temp"];
                int pres = root["main"]["pressure"];
                int hum = root["main"]["humidity"];
                // Print values.
                Serial.printf("都市名:%s 天気アイコン:%s\n", cityName, icon);
                Serial.printf("温度:%.1f℃ 気圧:%dhPa 湿度%d%%\n", temp, pres, hum);
                //        String r1 = "01d";
                //        String r2 = "01n";
                //        String rb1 = "02d";
                //        String rb2 = "02n";
                String iconStr = icon;
                iconStr = "01d";
                if (iconStr.equals("01d") || iconStr.equals("01n"))
                {
                    digitalWrite(4, HIGH);
                }
                else if (iconStr.equals("02d") || iconStr.equals("02n"))
                {
                    digitalWrite(16, HIGH);
                    digitalWrite(4, HIGH);
                }
                else
                {
                    digitalWrite(16, HIGH);
                }
            }
        }
        else
        {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }
    delay(5000);
}

