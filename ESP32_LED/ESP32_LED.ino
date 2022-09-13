const int pwmPin = A10; //GPIO IO4ping

void setup() {
    ledcSetup(0, 12899, 8);
    ledcAttachPin(pwmPin, 0);
}

void loop() {
    ledcWrite(0, 255);
    delay(100);
    ledcWrite(0, 127);
    delay(100);
    ledcWrite(0, 0);
    delay(100);
}