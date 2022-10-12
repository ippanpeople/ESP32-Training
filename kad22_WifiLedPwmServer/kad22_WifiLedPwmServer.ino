#include <WiFi.h>

// 接続先のSSIDとpassword
const char ssid[] = "CampusIoT-WiFi";
const char passwd[] = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

const int ledPin = 4;      // red LED
const int pwmPin = 16;
WiFiServer server(80);

void setup()
{
    ledcSetup(0, 12800, 8);
    ledcAttachPin(pwmPin, 0);
    delay(1000);
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);

    // WiFi接続シーケンス
    Serial.print("Connecting...");
    WiFi.begin(ssid, passwd);
    while(WiFi.status() != WL_CONNECTED){
        delay(100);
        Serial.print(".");
    }
    Serial.println("connected");
    Serial.println(WiFi.localIP());

    server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("new client");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            //ヘッダー
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            //本体部分
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<meta name='viewport' content='initial-scale=1.5'>");
            client.println("</head>");
            client.println("<body>");
            client.println("<form method='get'>");
            client.println("<h1>ESP32</h1>");
            client.println("<h2>Wi-Fi LED PWM Changer</h2>");
            client.println("<input type='radio' name=pwm value='0'>0%<br>");
            client.println("<input type='radio' name=pwm value='25'>25%<br>");
            client.println("<input type='radio' name=pwm value='50'>50%<br>");
            client.println("<input type='radio' name=pwm value='75'>75%<br>");
            client.println("<input type='radio' name=pwm value='100'>100%<br>");
            client.println("<input type='submit' name=btn value='Sent' style='background-color:green; color:blue;'>");
            client.println("</form>");
            client.println("</body>");
            client.println("</html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /?pwm=0&btn=Sent")) {
          ledcWrite(0,0);
        }
        if (currentLine.endsWith("GET /?pwm=25&btn=Sent")) {
          ledcWrite(0,63);
        }
        if (currentLine.endsWith("GET /?pwm=50&btn=Sent")) {
          ledcWrite(0,127);
        }
        if (currentLine.endsWith("GET /?pwm=75&btn=Sent")) {
          ledcWrite(0,191);
        }
        if (currentLine.endsWith("GET /?pwm=100&btn=Sent")) {
          ledcWrite(0,255);
        }

      }
    }

    client.stop();
    Serial.println("client disonnected");
  }
}
