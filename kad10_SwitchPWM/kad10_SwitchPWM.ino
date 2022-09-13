const int pwmPin = A10; //GPIO IO4ping
const int btnPin = 17;
bool flag = false;
static uint8_t duty[5] = {63, 127, 191, 255, 0}; //アナログ出力のデューティ値 
static int diff = 0;


void setup() {
    Serial.begin(115200);
    ledcSetup(0, 12899, 8);
    ledcAttachPin(pwmPin, 0);
}

void loop() {
    int b = digitalRead(btnPin);

    if(b == 1 && flag == false){
        flag = true;
        if(diff == 4){
            diff = 0;
        }else{
            diff ++;
        }
        Serial.printf("duty=%3d\n", duty[diff]);// デューティの表示
    }else if(b == 0){
        flag = false;
    }
    ledcWrite(0, duty[diff]);
    delay(100);
}