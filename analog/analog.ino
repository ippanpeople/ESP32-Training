const int analogPin = A17;

void setup(){
    Serial.begin(115200);
}

void loop(){
    int a = analogRead(analogPin);
    Serial.println(a);
    delay(100);
}