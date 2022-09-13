const int pwmPin = 4; //GPIO IO4ping

void setup() {
    Serial.begin(115200);
    ledcSetup(0, 12899, 8);
    ledcAttachPin(pwmPin, 0);
}

void loop() {
    static uint8_t duty = 0; //アナログ出力のデューティ値 
    static int diff = 1; //増分・減分(使わなくても可) 
    Serial.printf("%3d\n", duty);// デューティの表示

    if(duty == 0){
        diff = 1;
    }else if(duty == 255){
        diff = -1;
    }
    duty += diff;

    ledcWrite(0, duty);
    delay(100);
}