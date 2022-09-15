const int analogPin = A17;

void setup(){
    Serial.begin(115200);
}

void loop(){
    int a = analogRead(analogPin);
    float b = a * 3.3 / 4095;

    Serial.printf("%3d=%3.2f[V]\n", a, b);
    delay(100);
}
