const int analogPin = A17;
const int pwmPin1 = 4; //GPIO IO4ping
const int pwmPin2 = 16; //GPIO IO16ping


void setup(){
    Serial.begin(115200);
    ledcSetup(0, 12899, 8);
    ledcSetup(1, 12899, 8);
    ledcAttachPin(pwmPin1, 0);
    ledcAttachPin(pwmPin2, 1);

}

void loop(){
    int a = analogRead(analogPin);
    float b = a * 3.3 / 4095;
    int darkLevel = 1000;
    int blue = map(a, 4095, 0, 0, 255);
    int red = map(a, 4095, 0, 0, 255);
    
    if(blue < 0){
        blue = 0;
        red = 0;
    }else if(blue > 255){
        blue = 255;
        red = 255;
    }
    ledcWrite(0, blue);
    ledcWrite(1, red);


    Serial.printf("%3d=%3.2f[V][blue : %3d][red : %3d]\n", a, b, blue, red);
    delay(100);
}
